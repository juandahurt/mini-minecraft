//
// Created by aureliano on 2/11/26.
//

#ifndef MINI_MINECRAFT_WORLD_H
#define MINI_MINECRAFT_WORLD_H
#include "Chunk.h"
#include <glm/glm.hpp>


class World {
private:
    glm::ivec2 m_chunkSize;
    std::vector<Chunk> m_chunks;
    FaceInstances m_faceInstances;
public:
    World(glm::ivec2 chunkSize);

    void load();

    std::vector<Chunk> getChunks() const;
    FaceInstances getFaceInstances() const;
};


#endif //MINI_MINECRAFT_WORLD_H
