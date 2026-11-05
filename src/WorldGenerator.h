#ifndef MINI_MINECRAFT_WORLDGENERATOR_H
#define MINI_MINECRAFT_WORLDGENERATOR_H

#include "FastNoiseLite.h"

class WorldGenerator {
public:
    struct Params {
        float frequency = 0.02f;
        int octaves = 4;
        int seed = 1337;
        int baseHeight = 8;
        int amplitude = 8;
    };

private:
    FastNoiseLite m_noise;
    Params m_params;

public:
    WorldGenerator();

    Params& params();
    void apply();

    int heightAt(int worldX, int worldZ) const;
};

#endif //MINI_MINECRAFT_WORLDGENERATOR_H
