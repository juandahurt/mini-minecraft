//
// Created by aureliano on 2/11/26.
//

#ifndef MINI_MINECRAFT_WORLD_H
#define MINI_MINECRAFT_WORLD_H
#include "Chunk.h"
#include "Player.h"
#include "WorldGenerator.h"

#define CHUNK_SIZE 6


class World {
private:
    glm::ivec2 m_worldSizeInChunks;
    std::vector<Chunk> m_chunks;
    WorldGenerator m_generator;

    const Chunk* chunkAt(int cx, int cz) const;
public:
    World(glm::ivec2 worldSizeInChunks);

    void load();
    void regenerate();

    WorldGenerator& generator();
    const std::vector<Chunk>& getChunks() const;
    std::vector<const Chunk*> chunksOverlapping(const AABB& box) const;
};


#endif //MINI_MINECRAFT_WORLD_H
