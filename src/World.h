//
// Created by aureliano on 2/11/26.
//

#ifndef MINI_MINECRAFT_WORLD_H
#define MINI_MINECRAFT_WORLD_H
#include "Chunk.h"

#define CHUNK_SIZE 6


class World {
private:
    glm::ivec2 m_worldSizeInChunks;
    std::vector<Chunk> m_chunks;

    const Chunk* chunkAt(int cx, int cz) const;
public:
    World(glm::ivec2 worldSizeInChunks);

    void load();

    const std::vector<Chunk>& getChunks() const;
};


#endif //MINI_MINECRAFT_WORLD_H
