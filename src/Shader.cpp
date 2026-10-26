//
// Created by aureliano on 25/10/26.
//

#include "Shader.h"

#include <cassert>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const std::string &filePath, ShaderType type)
    : m_id(0), m_filePath(filePath), m_type(type) {
    std::ifstream stream(filePath);
    assert(stream.is_open() && "Failed to open shader file.");
    std::stringstream ss;
    ss << stream.rdbuf();
    createShader(ss.str());
}

Shader::~Shader() {}

void Shader::createShader(const std::string& source) {
    GLCall(m_id = glCreateShader(mapShaderType()));
    if (!compile(m_id, source)) {
        GLCall(glDeleteShader(m_id));
        return;
    }

    // GLCall(glDeleteShader(shaderId));
}

bool Shader::compile(unsigned int shaderId, const std::string& source) {
    const char* src = source.c_str();
    GLCall(glShaderSource(shaderId, 1, &src, nullptr));
    GLCall(glCompileShader(shaderId));

    int result;
    GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));
        char* msg = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(shaderId, length, &length, msg));
        std::cout << "[Shader Error] " << m_filePath << ": " << msg << std::endl;
        return false;
    }
    return true;
}

unsigned int Shader::mapShaderType() const {
    switch (m_type) {
        case VERTEX:   return GL_VERTEX_SHADER;
        case FRAGMENT: return GL_FRAGMENT_SHADER;
    }
    assert(false && "Unknown ShaderType");
    return 0;
}

unsigned int Shader:: getId() const {
    return m_id;
}