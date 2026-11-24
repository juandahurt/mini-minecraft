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
    glm::ivec2 m_worldSizeInChunks;
    std::vector<Chunk> m_chunks;
    WorldGenerator m_generator;
public:
    World(glm::ivec2 worldSizeInChunks);

    void buildFaceInstances();
    void load();
    void regenerate();

    int chunkIndex(int cx, int cz)const;
    const Chunk *chunkAt(int cx, int cz) const;
    WorldGenerator& generator();
    const std::vector<Chunk>& getChunks() const;
    std::vector<const Chunk*> chunksOverlapping(const AABB& box) const;

    void setChunkAt(int x, int z, const Chunk & chunk);
};


#endif //MINI_MINECRAFT_WORLD_H
