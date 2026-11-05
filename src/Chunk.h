//
// Created by aureliano on 2/11/26.
//

#ifndef MINI_MINECRAFT_CHUNK_H
#define MINI_MINECRAFT_CHUNK_H
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <glm/vec3.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "FaceDirection.h"
#include "Material.h"
#include "Player.h"
#include "WorldGenerator.h"

using FaceInstances = std::map<std::pair<FaceDirection, Material>, std::vector<glm::vec3>>;

class Chunk {
private:
    FaceInstances m_instances;
    std::unordered_map<glm::ivec3, Material> m_blockPositions;
    glm::ivec2 m_position;

public:
    Chunk(glm::ivec2 position);

    void addBlock(glm::ivec3 position, Material material);
    void buildFaceInstances(const Chunk* xPos, const Chunk* xNeg,
                            const Chunk* zPos, const Chunk* zNeg);

    bool hasBlockAt(glm::ivec3 localPos) const;
    const FaceInstances& getFaceInstances() const;
    std::vector<glm::ivec3> blocksOverlapping(const AABB& worldBox) const;

    const glm::ivec2& getPosition() const;
};


#endif //MINI_MINECRAFT_CHUNK_H
