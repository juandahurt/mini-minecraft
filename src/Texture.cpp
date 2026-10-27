//
// Created by aureliano on 26/10/26.
//

#include "Texture.h"
#include "Renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& filePath) : m_id(0), m_filePath(filePath) {
    GLCall(glGenTextures(1, &m_id));
    load();
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_id));
}

void Texture::load() {
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    int width, height, nrChannels;
    unsigned char* data = stbi_load(m_filePath.c_str(), &width, &height, &nrChannels, 4);
    if (data) {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    } else {
        std::cerr << "Failed to load texture: " << m_filePath << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bind(int slot) {
    // TODO: use the slot to pass the actual slot
    GLCall(glActiveTexture(GL_TEXTURE0));
}
