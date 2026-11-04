//
// Created by aureliano on 2/11/26.
//

#ifndef MINI_MINECRAFT_CHUNK_H
#define MINI_MINECRAFT_CHUNK_H
#include <map>
#include <unordered_set>
#include <glm/vec3.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "FaceDirection.h"
#include "WorldGenerator.h"

using FaceInstances = std::map<FaceDirection, std::vector<glm::vec3>>;

class Chunk {
private:
    FaceInstances m_instances;
    std::unordered_set<glm::ivec3> m_blockPositions;
    glm::ivec2 m_position;

public:
    Chunk(glm::ivec2 position);

    void addBlock(glm::ivec3 position);
    void buildFaceInstances();

    FaceInstances getFaceInstances();
};


#endif //MINI_MINECRAFT_CHUNK_H
