//
// Created by aureliano on 2/11/26.
//

#include "Chunk.h"

#include "World.h"

Chunk::Chunk(glm::ivec2 position) : m_position(position) {}

void Chunk::addBlock(glm::ivec3 position) {
    m_blockPositions.insert(position + CHUNK_SIZE * glm::ivec3(m_position.x, 0, m_position.y));
}

void Chunk::buildFaceInstances() {
    const std::pair<FaceDirection, glm::ivec3> neighbours[] = {
        {Y_UP,   { 0,  1,  0}},
        {Y_DOWN, { 0, -1,  0}},
        {X_UP,   { 1,  0,  0}},
        {X_DOWN, {-1,  0,  0}},
        {Z_UP,   { 0,  0,  1}},
        {Z_DOWN, { 0,  0, -1}},
    };
    for (auto& pos: m_blockPositions) {
        for (auto& [dir, offset]: neighbours) {
            if (!m_blockPositions.contains(pos + offset)) {
                m_instances[dir].push_back(glm::vec3(pos));
            }
        }
    }
}

FaceInstances Chunk::getFaceInstances() {
    return m_instances;
}
