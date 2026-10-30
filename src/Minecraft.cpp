#include "Minecraft.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#endif

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
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
    m_worldGenerator = std::make_unique<WorldGenerator>(4, 4);
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize(instance->m_width, instance->m_height);
    int screenW = glutGet(GLUT_SCREEN_WIDTH);
    int screenH = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((screenW - instance->m_width) / 2, (screenH - instance->m_height) / 2);
    glutCreateWindow(instance->m_title.c_str());

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

    m_worldGenerator->generate();
    for (auto& [dir, positions] : m_worldGenerator->getInstances()) {
        FaceBatch batch;
        auto face = Face(dir, Material::EARTH);

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

        m_batches.emplace(dir, std::move(batch));
    }

    unsigned int indices[] = { 2, 0, 1, 3, 2, 1 };
    m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    auto vertexS = Shader("../res/shaders/shader.vert", ShaderType::VERTEX);
    auto fragS = Shader("../res/shaders/shader.frag", ShaderType::FRAGMENT);
    m_program = std::make_unique<ShaderProgram>(vertexS, fragS);

    m_texture = std::make_unique<Texture>("../res/textures/atlas.png");
    m_texture->bind(0);
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
    m_projection = glm::perspective(glm::radians(60.0f), (float)w / (float)h, 0.1f, 100.0f);
}

void Minecraft::onMouse(int button, int state, int x, int y) {}
void Minecraft::onMotion(int x, int y) {}
void Minecraft::onPassiveMotion(int x, int y) {
    static float lastX = x;
    static float lastY = y;
    static float yaw = 90;
    static float pitch = 0;
    static float firstMove = true;

    if (firstMove == true) {
        firstMove = false;
        lastX = static_cast<float>(x);
        lastY = static_cast<float>(y);
        return;
    }

    float xOffset = static_cast<float>(x) - lastX;
    lastX = static_cast<float>(x);
    float yOffset = lastY - static_cast<float>(y);
    lastY = static_cast<float>(y);
    float sensibility = 0.1f;

    yaw += xOffset * sensibility;
    pitch += yOffset * sensibility;

    if (pitch > 89.0f) { pitch = 89.0f; }
    if (pitch < -89.0f) { pitch = -89.0f; }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_camera->setFront(glm::normalize(direction));
}

void Minecraft::onKeyboard(unsigned char key, int x, int y) {
    m_pressedKeys.insert(key);
}

void Minecraft::onKeyboardUp(unsigned char key, int x, int y) {
    m_pressedKeys.erase(key);
}

void Minecraft::onUpdate() {
    auto speed = m_camera->getSpeed();
    if (m_pressedKeys.contains('w')) {
        m_camera->setPosition(m_camera->getPosition() + m_camera->getFront() * speed);
    }
    if (m_pressedKeys.contains('s')) {
        m_camera->setPosition(m_camera->getPosition() - m_camera->getFront() * speed);
    }
    if (m_pressedKeys.contains('a')) {
        m_camera->setPosition(m_camera->getPosition() - glm::normalize(glm::cross(m_camera->getFront(), m_camera->getUp())) * speed);
    }
    if (m_pressedKeys.contains('d')) {
        m_camera->setPosition(m_camera->getPosition() + glm::normalize(glm::cross(m_camera->getFront(), m_camera->getUp())) * speed);
    }

    glutPostRedisplay();
}

void Minecraft::onDisplay() {
    m_renderer->clear(0.164, 0.53, 0.7, 1);

    m_program->bind();

    auto view = m_camera->getViewMatrix();
    auto mvp = m_projection * view;

    m_program->setUniformMat4("u_mvp", mvp);
    m_program->setUniformInt("u_texture", 0);

    for (auto& [dir, batch] : m_batches) {
        batch.vao->bind();
        m_renderer->drawInstanced(*m_indexBuffer, *batch.geometryVBO, *m_program, batch.instanceCount);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    static bool showDebug = true;
    if (showDebug) {
        ImGui::Begin("Debug", &showDebug, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));
        ImGui::Text("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
        float speed = m_camera->getSpeed();
        if (ImGui::SliderFloat("Camera Speed", &speed, 0.1f, 0.6f))
            m_camera->setSpeed(speed);
        ImGui::Separator();
        ImGui::Text("Vertices: 3");
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
}
