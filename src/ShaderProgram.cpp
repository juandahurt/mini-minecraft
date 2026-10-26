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