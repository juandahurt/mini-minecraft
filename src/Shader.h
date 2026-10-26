//
// Created by aureliano on 25/10/26.
//

#ifndef MINI_MINECRAFT_SHADER_H
#define MINI_MINECRAFT_SHADER_H
#include <string>

enum ShaderType {
    VERTEX, FRAGMENT
};

class Shader {
private:
    unsigned int m_id;
    std::string m_filePath;
    ShaderType m_type;
public:
    Shader(const std::string& filePath, ShaderType type);
    ~Shader();

    void setUniform4f(const std::string& name, int v0, int v1, int v2, int v3);
    unsigned int getId() const;

private:
    unsigned int getUniformLocation(const std::string& name);
    void createShader(const std::string& source);
    bool compile(unsigned int shaderId, const std::string& source);
    unsigned int mapShaderType() const;
};


#endif //MINI_MINECRAFT_SHADER_H
