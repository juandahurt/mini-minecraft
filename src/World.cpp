//
// Created by aureliano on 2/11/26.
//

#include "World.h"

#include <iostream>
#include <ostream>

World::World(glm::ivec2 chunkSize): m_chunkSize(chunkSize) {}

void World::load() {
    for (int n = 0; n < CHUNK_SIZE; n++) {auto chunk = Chunk({n, 0});
        for (int i = 0; i < m_chunkSize.x; i++) {
            for (int j = 0; j < m_chunkSize.y; j++) {
                auto height = rand() % 4 + 1;
                // for (int y = 0; y < height; y++) {
                    chunk.addBlock(glm::ivec3(i, 0, j));
                // }
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