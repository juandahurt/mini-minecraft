#include "Minecraft.h"

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <ApplicationServices/ApplicationServices.h>
#else
#include <GL/freeglut.h>
#endif

#include "Face.h"
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#include "Ray.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "VertexBufferLayout.h"

Minecraft::Minecraft()
    : m_title("Example :)")
    , m_width(1080)
    , m_height(720)
    , m_translation(0.0f, 0.0f, 0.0f) {
    m_camera = std::make_unique<Camera>();
    m_world = std::make_unique<World>(glm::ivec2(10, 10));
    m_player = std::make_unique<Player>(glm::vec3(10, 30, 10), glm::vec3(0.7, 2, 0.7));
    m_showPlayerBox = false;
    m_debugMode = false;
    m_showSelectedBlock = true;
    m_showCurrentChunk = false;
    m_showPosToBeAdded = false;
    m_physicsEnabled = false;
    m_selectedMaterial = STONE;
}

Minecraft::~Minecraft() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
}

void Minecraft::run() {
    glutMainLoop();
}

void Minecraft::create(int argc, char** argv) {
    instance = std::make_unique<Minecraft>();

    glutInit(&argc, argv);
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#else
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutInitWindowSize(instance->m_width, instance->m_height);
    glutCreateWindow(instance->m_title.c_str());

    glutFullScreen();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init("#version 330");

    instance->setup();

    glutIdleFunc(onUpdateWrapper);
    glutDisplayFunc(onDisplayWrapper);
    glutReshapeFunc(onReshapeWrapper);
    glutMouseFunc(onMouseWrapper);
    glutMotionFunc(onMotionWrapper);
    glutPassiveMotionFunc(onPassiveMotionWrapper);
    glutKeyboardFunc(onKeyboardWrapper);
    glutKeyboardUpFunc(onKeyboardUpWrapper);
}

void Minecraft::setup() {
    m_renderer = std::make_unique<Renderer>();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    m_world->load();
    rebuildBatches();

    unsigned int indices[] = { 2, 0, 1, 3, 2, 1 };
    m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    auto vertexS = Shader("../res/shaders/shader.vert", ShaderType::VERTEX);
    auto fragS = Shader("../res/shaders/shader.frag", ShaderType::FRAGMENT);
    m_program = std::make_unique<ShaderProgram>(vertexS, fragS);

    m_texture = std::make_unique<Texture>("../res/textures/atlas.png");
    m_texture->bind(0);

    setupPlayerWireframe();

    if (!m_debugMode) {
        hideMousePointer();
    }
}

void Minecraft::setupPlayerWireframe() {
    // 8 corners of a unit cube [0,1]^3
    glm::vec3 corners[8] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {0.0f, 1.0f, 1.0f},
    };

    // 12 edges, 2 indices each
    unsigned int edges[24] = {
        0, 1,  1, 2,  2, 3,  3, 0, // bottom
        4, 5,  5, 6,  6, 7,  7, 4, // top
        0, 4,  1, 5,  2, 6,  3, 7, // vertical
    };

    m_playerVBO = std::make_unique<VertexBuffer>(corners, sizeof(corners));
    m_playerIBO = std::make_unique<IndexBuffer>(edges, 24);

    auto layout = VertexBufferLayout();
    layout.push<float>(3);

    m_playerVAO = std::make_unique<VertexArray>();
    m_playerVAO->addBuffer(*m_playerVBO, layout);

    auto vertS = Shader("../res/shaders/wireframe.vert", ShaderType::VERTEX);
    auto fragS = Shader("../res/shaders/wireframe.frag", ShaderType::FRAGMENT);
    m_playerProgram = std::make_unique<ShaderProgram>(vertS, fragS);
}

void Minecraft::rebuildBatches() {
    m_chunkBatches.clear();
    const auto& chunks = m_world->getChunks();
    m_chunkBatches.resize(chunks.size());
    for (size_t i = 0; i < chunks.size(); ++i) {
        for (const auto& [key, positions] : chunks[i].getFaceInstances()) {
            auto [dir, material] = key;
            FaceBatch batch;
            auto face = Face(dir, material);

            auto geomLayout = VertexBufferLayout();
            geomLayout.push<float>(3);
            geomLayout.push<float>(2);
            batch.geometryVBO = std::make_unique<VertexBuffer>(face.vertices.data(), face.vertices.size() * sizeof(Vertex));

            auto instanceLayout = VertexBufferLayout();
            instanceLayout.push<float>(3);
            batch.instanceVBO = std::make_unique<VertexBuffer>(positions.data(), positions.size() * sizeof(glm::vec3));

            batch.vao = std::make_unique<VertexArray>();
            batch.vao->addBuffer(*batch.geometryVBO, geomLayout);
            batch.vao->addInstancedBuffer(*batch.instanceVBO, instanceLayout);
            batch.instanceCount = positions.size();

            m_chunkBatches[i].emplace(key, std::move(batch));
        }
    }
}

// Wrappers
void Minecraft::onDisplayWrapper() { instance->onDisplay(); }

void Minecraft::onUpdateWrapper() { instance->onUpdate(); }

void Minecraft::onReshapeWrapper(int w, int h) {
    ImGui_ImplGLUT_ReshapeFunc(w, h);
    instance->onReshape(w, h);
}

void Minecraft::onMouseWrapper(int button, int state, int x, int y) {
    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
    instance->onMouse(button, state, x, y);
}

void Minecraft::onMotionWrapper(int x, int y) {
    ImGui_ImplGLUT_MotionFunc(x, y);
    instance->onMotion(x, y);
}

void Minecraft::onPassiveMotionWrapper(int x, int y) {
    ImGui_ImplGLUT_MotionFunc(x, y);
    instance->onPassiveMotion(x, y);
}

void Minecraft::onKeyboardWrapper(unsigned char key, int x, int y) {
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
    instance->onKeyboard(key, x, y);
}

void Minecraft::onKeyboardUpWrapper(unsigned char key, int x, int y) {
    ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
    instance->onKeyboardUp(key, x, y);
}

void Minecraft::onReshape(int w, int h) {
    m_width = w;
    m_height = h;
    m_projection = glm::perspective(glm::radians(60.0f), (float)w / (float)h, 0.1f, 100.0f);
}

void Minecraft::onMouse(int button, int state, int x, int y) {
    if (m_debugMode) { return; }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        // add a new block
        if (m_posToBeAdded) {
            const glm::ivec3 worldPos = glm::ivec3(*m_posToBeAdded);
            const int cx = (int)std::floor((float)worldPos.x / CHUNK_SIZE);
            const int cz = (int)std::floor((float)worldPos.z / CHUNK_SIZE);
            auto chunk = m_world->chunkAt(cx, cz);
            if (!chunk) { return; } // outside the world
            auto newChunk = Chunk(chunk->getPosition());
            newChunk.setBlockPositions(chunk->getBlockPositions());
            // chunk blocks are stored in local coordinates
            const glm::ivec3 localPos = worldPos - CHUNK_SIZE * glm::ivec3(cx, 0, cz);
            newChunk.addBlock(localPos, m_selectedMaterial);
            m_world->setChunkAt(cx, cz, newChunk);
            m_world->buildFaceInstances();
            rebuildBatches();
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // remove selected block
        if (m_selectedCubePos) {
            const glm::ivec3 worldPos = glm::ivec3(*m_selectedCubePos);
            const int cx = (int)std::floor((float)worldPos.x / CHUNK_SIZE);
            const int cz = (int)std::floor((float)worldPos.z / CHUNK_SIZE);
            auto chunk = m_world->chunkAt(cx, cz);
            if (!chunk) { return; } // outside the world
            auto newChunk = Chunk(chunk->getPosition());
            newChunk.setBlockPositions(chunk->getBlockPositions());
            // chunk blocks are stored in local coordinates
            const glm::ivec3 localPos = worldPos - CHUNK_SIZE * glm::ivec3(cx, 0, cz);
            newChunk.removeBlockAt(localPos);
            m_world->setChunkAt(cx, cz, newChunk);
            m_world->buildFaceInstances();
            rebuildBatches();
        }
    }
}
void Minecraft::onMotion(int x, int y) {}
void Minecraft::onPassiveMotion(int x, int y) {
    if (m_debugMode) { return; } // camera movement disabled on debug mode
    int cx = m_width / 2;
    int cy = m_height / 2;
    int dx = x - cx;
    int dy = cy - y;
    if (dx == 0 && dy == 0) { return; } // ignore the event caused by the warp itself

    static float yaw = 90;
    static float pitch = 0;
    float sensibility = 0.1f;

    yaw += (float)dx * sensibility;
    pitch += (float)dy * sensibility;

    if (pitch > 89.0f) { pitch = 89.0f; }
    if (pitch < -89.0f) { pitch = -89.0f; }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_camera->setFront(glm::normalize(direction));

    moveMouseToWindowCenter();
}

void Minecraft::onKeyboard(unsigned char key, int x, int y) {
    m_pressedKeys.insert(key);
    if (key == 32 && m_physicsEnabled) {
        auto s = m_player->getSpeed();
        m_player->setSpeed(s + glm::vec3(s.x, 3.0f, s.z));
    }
}

void Minecraft::onKeyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': case 'a': case 's': case 'd':
            m_player->setSpeed(glm::vec3(0.0f, 0.0f, 0.0f));
            break;
        case 27:
            m_debugMode = !m_debugMode;
            if (m_debugMode) { showMousePointer(); }
            else {
                hideMousePointer();
                moveMouseToWindowCenter();
            }
            break;
        default: printf(":)");
    }
    m_pressedKeys.erase(key);
}

void Minecraft::onUpdate() {
    glm::vec3 camFront = m_camera->getFront();
    glm::vec3 forward = m_physicsEnabled ? glm::vec3(camFront.x, 0.0f, camFront.z) : camFront;
    if (glm::length(forward) > 0.0f) forward = glm::normalize(forward);
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

    glm::vec3 move(0.0f);
    if (m_pressedKeys.contains('w')) move += forward;
    if (m_pressedKeys.contains('s')) move -= forward;
    if (m_pressedKeys.contains('a')) move -= right;
    if (m_pressedKeys.contains('d')) move += right;

    if (glm::length(move) > 0.0f) {
        move = glm::normalize(move);
        auto currSpeed = m_player->getSpeed();
        m_player->setSpeed(glm::vec3(move.x, currSpeed.y, move.z));
    }
    glm::vec3 prevPos = m_player->getPosition();
    m_player->update();
    glm::vec3 delta = m_player->getPosition() - prevPos;

    if (m_physicsEnabled) {
        m_player->setGravity({0, -1, 0});
        // axis-separated collision resolution. speed is never touched,
        // so gravity keeps accumulating even when standing on ground.
        m_player->setPosition(prevPos + glm::vec3(0.0f, delta.y, 0.0f));
        if (playerCollides()) {
            m_player->setPosition(prevPos);
            auto s = m_player->getSpeed();
            // m_player->setSpeed({s.x, 0, s.z});
        }
        glm::vec3 afterY = m_player->getPosition();

        m_player->setPosition(afterY + glm::vec3(delta.x, 0.0f, 0.0f));
        if (playerCollides()) m_player->setPosition(afterY);
        glm::vec3 afterX = m_player->getPosition();

        m_player->setPosition(afterX + glm::vec3(0.0f, 0.0f, delta.z));
        if (playerCollides()) m_player->setPosition(afterX);
    } else {
        m_player->setGravity(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    m_camera->setPosition(m_player->getPosition() + glm::vec3(0.0f, m_player->getBox().y * 0.9f, 0.0f));

    if (m_showSelectedBlock) {
        // check for ray collisions
        auto ray = Ray(m_camera->getPosition(), glm::normalize(m_camera->getFront()));
        const float step = 0.1f;
        const float reach = 10.0f;
        m_selectedCubePos.reset();
        m_posToBeAdded.reset();
        m_chunkToModify.reset();
        std::optional<glm::ivec3> lastPos;
        for (float t = 0.0f; t <= reach && !m_selectedCubePos; t += step) {
            const auto pos = ray.pointAt(t);
            const glm::ivec3 blockPos = glm::ivec3(glm::floor(pos));
            for (auto& chunk : m_world->getChunks()) {
                const auto chunkPos = chunk.getPosition();
                const glm::ivec3 worldOffset = CHUNK_SIZE * glm::ivec3(chunkPos.x, 0, chunkPos.y);
                if (chunk.hasBlockAt(blockPos - worldOffset)) {
                    m_selectedCubePos = glm::vec3(blockPos);
                    if (lastPos) {
                        m_posToBeAdded = glm::vec3(*lastPos);
                    }
                    break;
                }
            }
            if (!m_selectedCubePos) {
                lastPos = blockPos;
            }
        }
    }


    glutPostRedisplay();
}

void Minecraft::onDisplay() {
    m_renderer->clear(0.464, 0.63, 0.97, 1);

    m_program->bind();

    auto view = m_camera->getViewMatrix();
    auto mvp = m_projection * view;

    m_program->setUniformMat4("u_mvp", mvp);
    m_program->setUniformInt("u_texture", 0);

    auto collidingChunks = m_world->chunksOverlapping(m_player->getAABB());
    const auto& chunks = m_world->getChunks();
    for (size_t i = 0; i < m_chunkBatches.size(); ++i) {
        bool isColliding = std::ranges::find(collidingChunks, &chunks[i]) != collidingChunks.end();
        m_program->setUniformInt("debug", m_showCurrentChunk && isColliding ? 1 : 0);
        for (auto& [key, batch] : m_chunkBatches[i]) {
            batch.vao->bind();
            m_renderer->drawInstanced(*m_indexBuffer, *batch.geometryVBO, *m_program, batch.instanceCount);
        }
    }

    // player wireframe box
    if (m_showPlayerBox) {
        auto pos = m_player->getPosition();
        auto box = m_player->getBox();
        auto model = glm::translate(glm::mat4(1.0f), pos - glm::vec3(box.x * 0.5f, 0.0f, box.z * 0.5f));
        model = glm::scale(model, box);
        auto playerMvp = m_projection * view * model;

        m_playerProgram->bind();
        m_playerProgram->setUniformMat4("u_mvp", playerMvp);
        m_playerProgram->setUniformVec3("u_color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_playerVAO->bind();
        m_renderer->drawLines(*m_playerIBO, *m_playerVBO, *m_playerProgram);
    }

    if (m_showSelectedBlock && m_selectedCubePos) {
        m_playerProgram->bind();

        // slightly larger than the block to avoid z-fighting with its faces
        const float margin = 0.002f;
        auto model = glm::translate(glm::mat4(1.0f), *m_selectedCubePos - glm::vec3(margin));
        model = glm::scale(model, glm::vec3(1.0f + 2.0f * margin));
        auto mvp = m_projection * view * model;

        m_playerProgram->bind();
        m_playerProgram->setUniformMat4("u_mvp", mvp);
        m_playerProgram->setUniformVec3("u_color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_playerVAO->bind();
        m_renderer->drawLines(*m_playerIBO, *m_playerVBO, *m_playerProgram);
    }

    if (m_showPosToBeAdded && m_posToBeAdded) {
        m_playerProgram->bind();

        const float margin = 0.002f;
        auto model = glm::translate(glm::mat4(1.0f), *m_posToBeAdded - glm::vec3(margin));
        model = glm::scale(model, glm::vec3(1.0f + 2.0f * margin));
        auto mvp = m_projection * view * model;

        m_playerProgram->bind();
        m_playerProgram->setUniformMat4("u_mvp", mvp);
        m_playerProgram->setUniformVec3("u_color", glm::vec3(1.0f, 1.0f, 1.0f));
        m_playerVAO->bind();
        m_renderer->drawLines(*m_playerIBO, *m_playerVBO, *m_playerProgram);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    if (m_debugMode) {
        ImGui::Begin("Debug", &m_debugMode, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));
        ImGui::Text("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
        float speed = m_camera->getSpeed();
        if (ImGui::SliderFloat("Camera Speed", &speed, 0.1f, 0.6f))
            m_camera->setSpeed(speed);
        ImGui::Separator();
        unsigned int totalFaces = 0;
        for (const auto& chunkBatches : m_chunkBatches) {
            for (const auto& [key, batch] : chunkBatches) {
                totalFaces += batch.instanceCount;
            }
        }
        ImGui::Text("Chunks: %zu", m_chunkBatches.size());
        ImGui::Text("Total faces: %u", totalFaces);

        ImGui::Separator();
        ImGui::Checkbox("Show player box", &m_showPlayerBox);

        ImGui::Separator();
        ImGui::Checkbox("Show selected cube", &m_showSelectedBlock);

        ImGui::Separator();
        ImGui::Checkbox("Show cube to be added", &m_showPosToBeAdded);

        ImGui::Separator();
        ImGui::Checkbox("Show 'current' chunk", &m_showCurrentChunk);

        ImGui::Separator();
        ImGui::Checkbox("'Physics' enabled", &m_physicsEnabled);

        char* materials[] = {"Grass", "Dirt", "Stone", "Snow"};
        static int selectedMaterial = static_cast<int>(m_selectedMaterial);

        if (ImGui::BeginCombo("Material", materials[selectedMaterial])) {
            for (int i = 0; i < IM_ARRAYSIZE(materials); i++) {
                const bool isSelected = selectedMaterial == i;
                if (ImGui::Selectable(materials[i], isSelected)) {
                    selectedMaterial = i;
                    m_selectedMaterial = static_cast<Material>(i);
                }

                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::CollapsingHeader("Terrain", ImGuiTreeNodeFlags_DefaultOpen)) {
            auto& p = m_world->generator().params();
            bool dirty = false;
            dirty |= ImGui::SliderFloat("Frequency", &p.frequency, 0.001f, 0.1f, "%.4f");
            dirty |= ImGui::SliderInt("Octaves", &p.octaves, 1, 8);
            dirty |= ImGui::SliderInt("Base height", &p.baseHeight, 0, 32);
            dirty |= ImGui::SliderInt("Amplitude", &p.amplitude, 1, 32);
            dirty |= ImGui::InputInt("Seed", &p.seed);
            if (dirty) {
                m_world->generator().apply();
                m_world->regenerate();
                rebuildBatches();
            }
        }
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
}

bool Minecraft::playerCollides() const {
    auto aabb = m_player->getAABB();
    for (auto chunk : m_world->chunksOverlapping(aabb)) {
        if (!chunk->blocksOverlapping(aabb).empty()) return true;
    }
    return false;
}

void Minecraft::hideMousePointer() {
    glutSetCursor(GLUT_CURSOR_NONE);
}

void Minecraft::showMousePointer() {
    glutSetCursor(GLUT_CURSOR_INHERIT);
}

void Minecraft::moveMouseToWindowCenter() {
    #ifdef __APPLE__
    int wx = glutGet(GLUT_WINDOW_X);
    int wy = glutGet(GLUT_WINDOW_Y);
    int cx = m_width / 2;
    int cy = m_height / 2;
    CGWarpMouseCursorPosition(CGPointMake(wx + cx, wy + cy));
    CGAssociateMouseAndMouseCursorPosition(true);
    #else
    glutWarpPointer(m_width / 2, m_height / 2);
    #endif
}