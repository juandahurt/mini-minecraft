#include "Window.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#endif

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#include "src/Shader.h"
#include "src/VertexBufferLayout.h"

Window::Window()
    : m_title("Example :)")
    , m_width(1080)
    , m_height(720)
    , m_translation(0.0f, 0.0f, 0.0f) {}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
}

void Window::setup() {
    m_renderer = std::make_unique<Renderer>();

    float vertices[6] = {
        50.0f, 100.0f,
        50.0f, 50.0f,
        100.0f, 150.0f,
    };

    m_vbo = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
    m_vao = std::make_unique<VertexArray>();
    auto layout = VertexBufferLayout();
    layout.push<float>(2);
    m_vao->addBuffer(*m_vbo, layout);

    unsigned int indices[3] = { 0, 1, 2 };
    m_indexBuffer = std::make_unique<IndexBuffer>(indices, 3);

    auto vertexS = Shader("../res/shaders/shader.vert", ShaderType::VERTEX);
    auto fragS = Shader("../res/shaders/shader.frag", ShaderType::FRAGMENT);
    m_program = std::make_unique<ShaderProgram>(vertexS, fragS);
}

void Window::create(int argc, char** argv) {
    instance = std::make_unique<Window>();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize(instance->m_width, instance->m_height);
    glutInitWindowPosition(350, 450);
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
    glutMainLoop();
}

// Wrappers
void Window::onDisplayWrapper() { instance->onDisplay(); }
void Window::onUpdateWrapper() { instance->onUpdate(); }

// Callbacks
void Window::onReshapeWrapper(int w, int h) {
    ImGui_ImplGLUT_ReshapeFunc(w, h);
    instance->onReshape(w, h);
}

void Window::onMouseWrapper(int button, int state, int x, int y) {
    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
    instance->onMouse(button, state, x, y);
}

void Window::onMotionWrapper(int x, int y) {
    ImGui_ImplGLUT_MotionFunc(x, y);
    instance->onMotion(x, y);
}

void Window::onPassiveMotionWrapper(int x, int y) {
    ImGui_ImplGLUT_MotionFunc(x, y);
    instance->onPassiveMotion(x, y);
}

void Window::onKeyboardWrapper(unsigned char key, int x, int y) {
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
    instance->onKeyboard(key, x, y);
}

void Window::onReshape(int w, int h) {
    // TODO: update projection matrix
}

void Window::onMouse(int button, int state, int x, int y) {}
void Window::onMotion(int x, int y) {}
void Window::onPassiveMotion(int x, int y) {}
void Window::onKeyboard(unsigned char key, int x, int y) {}

void Window::onUpdate() {
    glutPostRedisplay();
}

void Window::onDisplay() {
    m_renderer->clear(1, 1, 1, 1);

    m_program->bind();

    auto proj = glm::ortho(-1.0f, (float)m_width, 0.0f, (float)m_height, -1.0f, 1.0f);
    auto view = glm::translate(glm::mat4(1), m_translation);
    auto mvp = proj * view;

    m_program->setUniformMat4("u_mvp", mvp);

    m_renderer->draw(*m_indexBuffer, *m_vbo, *m_program);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    static bool showDebug = true;
    if (showDebug) {
        ImGui::Begin("Debug", &showDebug, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));
        ImGui::Text("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
        ImGui::SliderFloat("Translation", &m_translation.x, 0.0f, 100.0f);
        ImGui::Separator();
        ImGui::Text("Vertices: 3");
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
}
