//
// Created by aureliano on 26/10/26.
//

#ifndef MINI_MINECRAFT_SHADERPROGRAM_H
#define MINI_MINECRAFT_SHADERPROGRAM_H
#include "Shader.h"


class ShaderProgram {
private:
    unsigned int m_id;
public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    ~ShaderProgram();

    void bind() const;
    void unbind();
};


#endif //MINI_MINECRAFT_SHADERPROGRAM_H
