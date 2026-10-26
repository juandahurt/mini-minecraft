//
// Created by aureliano on 26/10/26.
//

#ifndef MINI_MINECRAFT_SHADERPROGRAM_H
#define MINI_MINECRAFT_SHADERPROGRAM_H
#include "Shader.h"
#include <glm/matrix.hpp>

class ShaderProgram {
private:
    unsigned int m_id;
public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    ~ShaderProgram();

    void bind() const;
    void unbind();

    void setUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
    int getUniformLocation(const std::string& name) const;
};


#endif //MINI_MINECRAFT_SHADERPROGRAM_H
