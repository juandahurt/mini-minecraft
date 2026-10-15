#include "Window.h"

#include <iostream>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
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
    glutInitDisplayMode(GLUT_SINGLE);
    glutCreateWindow(instance->m_title);

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
    std::cout << "Window::onUpdate()" << std::endl;
}

void Window::onDisplay() {
    std::cout << "Window::onDisplay()" << std::endl;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
