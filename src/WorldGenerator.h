//
// Created by aureliano on 28/10/26.
//

#ifndef MINI_MINECRAFT_WORLDGENERATOR_H
#define MINI_MINECRAFT_WORLDGENERATOR_H
#include <vector>

#define World std::vector<Material>

enum Material: unsigned int {
    EARTH = 1,
    STONE
};

class WorldGenerator {
private:
    int m_width;
    int m_height;
public:
    WorldGenerator(int width, int height);

    World generate() const;
};


#endif //MINI_MINECRAFT_WORLDGENERATOR_H
