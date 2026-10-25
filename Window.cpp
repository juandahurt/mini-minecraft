#include "Window.h"

#include <iostream>

#include "src/VertexArray.h"
#include "src/VertexBuffer.h"
#include "src/VertexBufferLayout.h"
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#endif

static unsigned int compileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, msg);
        std::cout << msg << std::endl;
    }
    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    // create shaders
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // glDeleteShader(vs);
    // glDeleteShader(fs);

    return program;
}

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

    // unsigned int vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)nullptr);

    std::string vertexShaderSource =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec2 position;\n"
        "\n"
        "void main() {\n"
        "   gl_Position = vec4(position.xy, 0.0, 1.0);\n"
        "}\n";

    std::string fragmentShaderSource =
        "#version 330 core\n"
        "\n"
        "out vec4 color;\n"
        "\n"
        "void main() {\n"
        "   color = vec4(1.0, 0, 0, 1);\n"
        "}\n";
    unsigned int shader = createShader(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shader);

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