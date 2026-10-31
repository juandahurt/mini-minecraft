//
// Created by aureliano on 28/10/26.
//

#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(int width, int height): m_width(width), m_height(height) {}

void WorldGenerator::generate() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            addBlock({i, 0, j}, Material::EARTH);
        }
    }
}

void WorldGenerator::addBlock(glm::vec3 position, Material material) {
    // TODO: use material
    m_instances[Y_UP].push_back(position);
    m_instances[Y_DOWN].push_back(position);
    m_instances[X_UP].push_back(position);
    m_instances[X_DOWN].push_back(position);
    m_instances[Z_UP].push_back(position);
    m_instances[Z_DOWN].push_back(position);
}

const FaceInstances &WorldGenerator::getInstances() const {
    return m_instances;
}
