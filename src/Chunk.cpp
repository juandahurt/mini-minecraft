//
// Created by aureliano on 2/11/26.
//

#include "Chunk.h"

Chunk::Chunk() {}

void Chunk::addBlock(glm::ivec3 position) {
    m_blockPositions.insert(position);
}

void Chunk::buildFaceInstances() {
    const std::pair<FaceDirection, glm::vec3> neighbours[] = {
        {Y_UP, {0, 1, 0}},
        {Y_DOWN, {0, -1, 0}},
        {X_UP, {1, 0, 0}},
        {X_DOWN, {-1, 0, 0}},
        {Z_UP, {0, 0, 1}},
        {Z_DOWN, {0, 0, -1}},
    };
    for (auto& pos: m_blockPositions) {
        for (auto& [dir, offset]: neighbours) {
            if (!m_blockPositions.contains(pos + offset)) {
                m_instances[dir].push_back(pos);
            }
        }
    }
}

FaceInstances Chunk::getFaceInstances() {
    return m_instances;
}
