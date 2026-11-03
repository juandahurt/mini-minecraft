//
// Created by aureliano on 2/11/26.
//

#include "World.h"

#include <iostream>
#include <ostream>

World::World(glm::ivec2 chunkSize): m_chunkSize(chunkSize) {}

void World::load() {
    auto chunk = Chunk();
    for (int i = 0; i < m_chunkSize.x; i++) {
        for (int j = 0; j < m_chunkSize.y; j++) {
            for (int y = 0; y < 3; y++) {
                chunk.addBlock(glm::ivec3(i, y, j));
            }
        }
    }

    chunk.buildFaceInstances();
    for (auto& [dir, instances] : chunk.getFaceInstances()) {
        m_faceInstances[dir].insert(m_faceInstances[dir].end(), instances.begin(), instances.end());
    }
}

FaceInstances World::getFaceInstances() const {
    return m_faceInstances;
}

std::vector<Chunk> World::getChunks() const {
    return m_chunks;
}