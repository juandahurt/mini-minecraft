//
// Created by aureliano on 28/10/26.
//

#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(int width, int height): m_width(width), m_height(height) {}

World WorldGenerator::generate() const {
    return std::vector<Material>{ EARTH, EARTH, EARTH, STONE, EARTH, EARTH, STONE, EARTH };
}
