//
// Created by aureliano on 28/10/26.
//

#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(int width, int height): m_width(width), m_height(height) {}

FaceInstances WorldGenerator::generate() const {
    FaceInstances instances;
    instances[Y_UP]   = { {0, 0, 0} };
    instances[Y_DOWN] = { {0, 0, 0} };
    instances[X_UP] = { {0, 0, 0} };
    instances[X_DOWN] = { {0, 0, 0} };
    instances[Z_UP] = { {0, 0, 0} };
    instances[Z_DOWN] = { {0, 0, 0} };
    return instances;
}
