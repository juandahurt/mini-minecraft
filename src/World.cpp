//
// Created by aureliano on 2/11/26.
//

#include "World.h"

#include <cmath>

World::World(glm::ivec2 worldSizeInChunks): m_worldSizeInChunks(worldSizeInChunks) {}

void World::load() {
    m_chunks.reserve(m_worldSizeInChunks.x * m_worldSizeInChunks.y);
    for (int cx = 0; cx < m_worldSizeInChunks.x; cx++) {
        for (int cz = 0; cz < m_worldSizeInChunks.y; cz++) {
            Chunk chunk({cx, cz});
            for (int i = 0; i < CHUNK_SIZE; i++) {
                for (int j = 0; j < CHUNK_SIZE; j++) {
                    int worldX = cx * CHUNK_SIZE + i;
                    int worldZ = cz * CHUNK_SIZE + j;
                    int height = m_generator.heightAt(worldX, worldZ);
                    for (int y = 0; y < height; y++) {
                        float alpha = (float)y / (float)height;
                        Material m = y == height - 1 ? Material::GRASS : Material::DIRT;
                        m = alpha < 0.3 ? Material::STONE : m;
                        chunk.addBlock(glm::ivec3(i, y, j), m);
                    }
                }
            }
            m_chunks.push_back(std::move(chunk));
        }
    }

    buildFaceInstances();
}

void World::buildFaceInstances() {
    for (int cx = 0; cx < m_worldSizeInChunks.x; cx++) {
        for (int cz = 0; cz < m_worldSizeInChunks.y; cz++) {
            const Chunk* xPos = chunkAt(cx + 1, cz);
            const Chunk* xNeg = chunkAt(cx - 1, cz);
            const Chunk* zPos = chunkAt(cx, cz + 1);
            const Chunk* zNeg = chunkAt(cx, cz - 1);
            m_chunks[cx * m_worldSizeInChunks.y + cz]
                .buildFaceInstances(xPos, xNeg, zPos, zNeg);
        }
    }
}

int World::chunkIndex(int cx, int cz) const {
    return cx * m_worldSizeInChunks.y + cz;
}

const Chunk* World::chunkAt(int cx, int cz) const {
    if (cx < 0 || cx >= m_worldSizeInChunks.x || cz < 0 || cz >= m_worldSizeInChunks.y) {
        return nullptr;
    }
    return &m_chunks[cx * m_worldSizeInChunks.y + cz];
}

void World::regenerate() {
    m_chunks.clear();
    load();
}

WorldGenerator& World::generator() {
    return m_generator;
}

const std::vector<Chunk>& World::getChunks() const {
    return m_chunks;
}

std::vector<const Chunk*> World::chunksOverlapping(const AABB& box) const {
    int minCx = (int)std::floor(box.min.x / (float)CHUNK_SIZE);
    int maxCx = (int)std::floor(box.max.x / (float)CHUNK_SIZE);
    int minCz = (int)std::floor(box.min.z / (float)CHUNK_SIZE);
    int maxCz = (int)std::floor(box.max.z / (float)CHUNK_SIZE);

    std::vector<const Chunk*> result;
    for (int cx = minCx; cx <= maxCx; cx++) {
        for (int cz = minCz; cz <= maxCz; cz++) {
            if (const Chunk* c = chunkAt(cx, cz)) {
                result.push_back(c);
            }
        }
    }
    return result;
}

void World::setChunkAt(int x, int z, const Chunk &chunk) {
    m_chunks[x * m_worldSizeInChunks.y + z] = chunk;
}
