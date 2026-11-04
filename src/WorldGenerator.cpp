#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() {
    m_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    m_noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    apply();
}

WorldGenerator::Params& WorldGenerator::params() {
    return m_params;
}

void WorldGenerator::apply() {
    m_noise.SetSeed(m_params.seed);
    m_noise.SetFrequency(m_params.frequency);
    m_noise.SetFractalOctaves(m_params.octaves);
}

int WorldGenerator::heightAt(int worldX, int worldZ) const {
    float n = m_noise.GetNoise((float)worldX, (float)worldZ);
    return m_params.baseHeight + static_cast<int>(n * m_params.amplitude);
}
