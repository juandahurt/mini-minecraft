//
// Created by aureliano on 28/10/26.
//

#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(int width, int height): m_width(width), m_height(height) {}

void WorldGenerator::generate() {
    addBlock({0, 0, 0}, Material::EARTH);
    addBlock({3, 0, 0}, Material::EARTH);
    addBlock({0, 2, 0}, Material::EARTH);
    addBlock({0, 0, 1}, Material::EARTH);
    addBlock({1, 0, 0}, Material::EARTH);
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
