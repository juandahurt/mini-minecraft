//
// Created by aureliano on 2/11/26.
//

#include "World.h"

World::World(glm::ivec2 chunkSize): m_chunkSize(chunkSize) {}

void World::load() {
    for (int n = 0; n < CHUNK_SIZE; n++) {
        auto chunk = Chunk({n, 0});
        for (int i = 0; i < m_chunkSize.x; i++) {
            for (int j = 0; j < m_chunkSize.y; j++) {
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
        for (auto& [dir, instances] : chunk.getFaceInstances()) {
            m_faceInstances[dir].insert(m_faceInstances[dir].end(), instances.begin(), instances.end());
        }
    }
}

FaceInstances World::getFaceInstances() const {
    return m_faceInstances;
}

std::vector<Chunk> World::getChunks() const {
    return m_chunks;
}