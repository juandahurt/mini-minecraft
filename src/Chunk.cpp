//
// Created by aureliano on 2/11/26.
//

#include "Chunk.h"

#include "World.h"

Chunk::Chunk(glm::ivec2 position) : m_position(position) {}

void Chunk::addBlock(glm::ivec3 position, Material material) {
    m_blockPositions[position] = material;
}

bool Chunk::hasBlockAt(glm::ivec3 localPos) const {
    return m_blockPositions.contains(localPos);
}

void Chunk::buildFaceInstances(const Chunk* xPos, const Chunk* xNeg,
                               const Chunk* zPos, const Chunk* zNeg) {
    const std::pair<FaceDirection, glm::ivec3> neighbours[] = {
        {Y_UP,   { 0,  1,  0}},
        {Y_DOWN, { 0, -1,  0}},
        {X_UP,   { 1,  0,  0}},
        {X_DOWN, {-1,  0,  0}},
        {Z_UP,   { 0,  0,  1}},
        {Z_DOWN, { 0,  0, -1}},
    };
    const glm::ivec3 worldOffset = CHUNK_SIZE * glm::ivec3(m_position.x, 0, m_position.y);
    for (auto& [pos, material]: m_blockPositions) {
        for (auto& [dir, offset]: neighbours) {
            glm::ivec3 np = pos + offset;
            bool occluded;
            if (np.x < 0) {
                occluded = xNeg && xNeg->hasBlockAt({CHUNK_SIZE - 1, np.y, np.z});
            } else if (np.x >= CHUNK_SIZE) {
                occluded = xPos && xPos->hasBlockAt({0, np.y, np.z});
            } else if (np.z < 0) {
                occluded = zNeg && zNeg->hasBlockAt({np.x, np.y, CHUNK_SIZE - 1});
            } else if (np.z >= CHUNK_SIZE) {
                occluded = zPos && zPos->hasBlockAt({np.x, np.y, 0});
            } else {
                occluded = m_blockPositions.contains(np);
            }
            if (!occluded) {
                m_instances[{dir, material}].push_back(glm::vec3(pos + worldOffset));
            }
        }
    }
}

const FaceInstances& Chunk::getFaceInstances() const {
    return m_instances;
}
