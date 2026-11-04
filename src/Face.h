//
// Created by aureliano on 2/11/26.
//

#ifndef MINI_MINECRAFT_FACE_H
#define MINI_MINECRAFT_FACE_H
#include <vector>

#include "Material.h"
#include "Vertex.h"
#include "WorldGenerator.h"

struct Face {
    std::vector<Vertex> vertices;

    Face(FaceDirection direction, Material material) {
        float tileSize = 1.0f / 16.f;
        auto textCoordPosition = textCoordNormPositionInAtlas(material, direction, tileSize);
        auto textCoordArray = textCoord(get<0>(textCoordPosition), get<1>(textCoordPosition), tileSize);
        switch (direction) {
            case Y_UP:
                vertices = {
                    Vertex({0.0f, 1.0f, 0.0f}, textCoordArray[0]),
                    Vertex({0.0f, 1.0f, 1.0f}, textCoordArray[1]),
                    Vertex({1.0f, 1.0f, 0.0f}, textCoordArray[2]),
                    Vertex({1.0f, 1.0f, 1.0f}, textCoordArray[3]),
                };
                break;
            case Y_DOWN:
                vertices = {
                    Vertex({0.0f, 0.0f, 0.0f}, textCoordArray[0]),
                    Vertex({1.0f, 0.0f, 0.0f}, textCoordArray[2]),
                    Vertex({0.0f, 0.0f, 1.0f}, textCoordArray[1]),
                    Vertex({1.0f, 0.0f, 1.0f}, textCoordArray[3]),
                };
                break;
            case X_UP:
                vertices = {
                    Vertex({1.0f, 0.0f, 1.0f}, textCoordArray[1]),
                    Vertex({1.0f, 0.0f, 0.0f}, textCoordArray[0]),
                    Vertex({1.0f, 1.0f, 1.0f}, textCoordArray[3]),
                    Vertex({1.0f, 1.0f, 0.0f}, textCoordArray[2]),
                };
                break;
            case X_DOWN:
                vertices = {
                    Vertex({0.0f, 0.0f, 0.0f}, textCoordArray[0]),
                    Vertex({0.0f, 0.0f, 1.0f}, textCoordArray[1]),
                    Vertex({0.0f, 1.0f, 0.0f}, textCoordArray[2]),
                    Vertex({0.0f, 1.0f, 1.0f}, textCoordArray[3]),
                };
                break;
            case Z_UP:
                vertices = {
                    Vertex({0.0f, 0.0f, 1.0f}, textCoordArray[0]),
                    Vertex({1.0f, 0.0f, 1.0f}, textCoordArray[1]),
                    Vertex({0.0f, 1.0f, 1.0f}, textCoordArray[2]),
                    Vertex({1.0f, 1.0f, 1.0f}, textCoordArray[3]),
                };
                break;
            case Z_DOWN:
                vertices = {
                    Vertex({1.0f, 0.0f, 0.0f}, textCoordArray[1]),
                    Vertex({0.0f, 0.0f, 0.0f}, textCoordArray[0]),
                    Vertex({1.0f, 1.0f, 0.0f}, textCoordArray[3]),
                    Vertex({0.0f, 1.0f, 0.0f}, textCoordArray[2]),
                };
                break;
        }
    }

    std::tuple<float, float> textCoordNormPositionInAtlas(Material material, FaceDirection direction, float tileSize) {
        // the position on the atlas
        float posInAtlas[2];
        if (material == GRASS) {
            if (direction == Y_UP) {
                posInAtlas[0] = 0;
                posInAtlas[1] = 0;
            }
            if (direction == Y_DOWN) {
                posInAtlas[0] = 2;
                posInAtlas[1] = 0;
            }
            if (direction == X_UP || direction == X_DOWN || direction == Z_UP || direction == Z_DOWN) {
                posInAtlas[0] = 3;
                posInAtlas[1] = 0;
            }
        }
        if (material == DIRT) {
            posInAtlas[0] = 2;
            posInAtlas[1] = 0;
        }
        if (material == STONE) {
            posInAtlas[0] = 1;
            posInAtlas[1] = 0;
        }
        return std::make_tuple(posInAtlas[0] * tileSize, posInAtlas[1] * tileSize);
    }

    std::array<glm::vec2, 4> textCoord(float posInAtlasX, float posInAtlasY, float tileSize) {
        return std::array{
            glm::vec2{ posInAtlasX + tileSize, posInAtlasY + tileSize },
            glm::vec2{ posInAtlasX,            posInAtlasY + tileSize },
            glm::vec2{ posInAtlasX + tileSize, posInAtlasY },
            glm::vec2{ posInAtlasX,            posInAtlasY },
        };
    }
};


#endif //MINI_MINECRAFT_FACE_H
