//
// Created by aureliano on 2/11/26.
//

#include "World.h"

World::World(glm::ivec2 worldSizeInChunks): m_worldSizeInChunks(worldSizeInChunks) {}

void World::load() {
    m_chunks.reserve(m_worldSizeInChunks.x * m_worldSizeInChunks.y);
    for (int cx = 0; cx < m_worldSizeInChunks.x; cx++) {
        for (int cz = 0; cz < m_worldSizeInChunks.y; cz++) {
            Chunk chunk({cx, cz});
            for (int i = 0; i < CHUNK_SIZE; i++) {
                for (int j = 0; j < CHUNK_SIZE; j++) {
                    auto height = 10;
                    for (int y = 0; y < height; y++) {
                        float alpha = (float)y / (float)height;
                        Material m = y == height - 1 ? Material::GRASS : Material::DIRT;
                        m = alpha < 0.3 ? Material::STONE : m;
                        chunk.addBlock(glm::ivec3(i, y, j), m);
                    }
                }
            }
            chunk.buildFaceInstances();
            m_chunks.push_back(std::move(chunk));
        }
    }
}

const std::vector<Chunk>& World::getChunks() const {
    return m_chunks;
}