#include "Window.h"

#include <iostream>

#include "src/Renderer.h"
#include "src/Shader.h"
#include "src/ShaderProgram.h"
#include "src/VertexArray.h"
#include "src/VertexBuffer.h"
#include "src/VertexBufferLayout.h"
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#endif

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

    float vertices[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f,
    };

    auto vbo = new VertexBuffer(&vertices, sizeof(vertices));
    auto vao = new VertexArray();
    auto layout = new VertexBufferLayout();
    layout->push<float>(2);
    vao->addBuffer(*vbo, *layout);

    vao->bind();
    vbo->bind();

    auto vertexS = new Shader("../res/shaders/shader.vert", ShaderType::VERTEX);
    auto fragS = new Shader("../res/shaders/shader.frag", ShaderType::FRAGMENT);
    auto program = new ShaderProgram(*vertexS, *fragS);
    program->bind();

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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();
}