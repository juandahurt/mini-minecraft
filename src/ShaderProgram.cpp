//
// Created by aureliano on 26/10/26.
//

#include "ShaderProgram.h"

#include "Renderer.h"

ShaderProgram::ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader) {
    GLCall(m_id = glCreateProgram());
    GLCall(glAttachShader(m_id, vertexShader.getId()));
    GLCall(glAttachShader(m_id, fragmentShader.getId()));
    GLCall(glLinkProgram(m_id));
    GLCall(glValidateProgram(m_id));
}

ShaderProgram::~ShaderProgram() {
    GLCall(glDeleteProgram(m_id));
}

void ShaderProgram::bind() const {
    GLCall(glUseProgram(m_id));
}

void ShaderProgram::unbind() {
    GLCall(glUseProgram(0));
}

void ShaderProgram::setUniformMat4(const std::string &name, const glm::mat4 &matrix) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void ShaderProgram::setUniformInt(const std::string &name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

int ShaderProgram::getUniformLocation(const std::string &name) const {
    GLCall(unsigned int location = glGetUniformLocation(m_id, name.c_str()));
    if (location == -1) {
        std::cerr << "Warning: uniform " << name << " does not exist!" << std::endl;
    }
    return location;
}
