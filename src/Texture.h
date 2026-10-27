//
// Created by aureliano on 26/10/26.
//

#ifndef MINI_MINECRAFT_TEXTURE_H
#define MINI_MINECRAFT_TEXTURE_H
#include <string>


class Texture {
private:
    unsigned int m_id;
    std::string m_filePath;

    void load();
public:
    Texture(const std::string& filePath);
    ~Texture();

    void bind(int slot);
};


#endif //MINI_MINECRAFT_TEXTURE_H
