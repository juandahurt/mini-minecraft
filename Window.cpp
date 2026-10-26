#include "Window.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#endif

#include "src/Renderer.h"
#include "src/Shader.h"
#include "src/ShaderProgram.h"
#include "src/VertexArray.h"
#include "src/VertexBuffer.h"
#include "src/VertexBufferLayout.h"

Window::Window() {
    this->m_width = 640;
    this->m_height = 480;
    this->m_title = "Example :)";
}

Window::~Window() = default;

void Window::create(int argc, char** argv) {
    instance = new Window();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    glutCreateWindow(instance->m_title);

    std::cout << "OpenGL: "
          << glGetString(GL_VERSION) << '\n';

    std::cout << "GLSL: "
          << glGetString(GL_SHADING_LANGUAGE_VERSION)
          << std::endl;

    glutIdleFunc(onUpdateWrapper);
    glutDisplayFunc(onDisplayWrapper);
    glutMainLoop();
}

// Wrappers
void Window::onDisplayWrapper() {
    instance->onDisplay();
}

void Window::onUpdateWrapper() {
    instance->onUpdate();
}

// Callbacks
void Window::onUpdate() {
    // std::cout << "Window::onUpdate()" << std::endl;
}

void Window::onDisplay() {
    std::cout << "Window::onDisplay()" << std::endl;
    m_renderer->clear(1, 1, 1, 1);

    float vertices[6] = {
        50.0f, 100.0f,
        50.0f, 50.0f,
        100.0f, 150.0f,
    };

    auto vbo = VertexBuffer(&vertices, sizeof(vertices));
    auto vao = VertexArray();
    auto layout = VertexBufferLayout();
    layout.push<float>(2);
    vao.addBuffer(vbo, layout);

    unsigned int indices[3] = {
        0, 1, 2
    };
    auto indexBuffer = IndexBuffer(indices, 3);

    auto vertexS = Shader("../res/shaders/shader.vert", ShaderType::VERTEX);
    auto fragS = Shader("../res/shaders/shader.frag", ShaderType::FRAGMENT);
    auto program = ShaderProgram(vertexS, fragS);
    program.bind();

    auto proj = glm::ortho(-1.0f, (float)this->m_width, 0.0f, (float)this->m_height, -1.0f, 1.0f);
    auto view = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f));
    auto mvp = proj * view;

    program.setUniformMat4("u_mvp", mvp);

    m_renderer->draw(indexBuffer, vbo, program);

    glutSwapBuffers();
}