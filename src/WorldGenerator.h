// //
// // Created by aureliano on 28/10/26.
// //
//
// #ifndef MINI_MINECRAFT_WORLDGENERATOR_H
// #define MINI_MINECRAFT_WORLDGENERATOR_H
//
// #include <map>
// #include <vector>
// #include <glm/vec3.hpp>
// #include "Vertex.h"
//

//
// // face direction: position
// using FaceInstances = std::map<FaceDirection, std::vector<glm::vec3>>;
//
// class WorldGenerator {
// private:
//     FaceInstances m_instances;
//
//     void addBlock(glm::vec3 position, Material material);
// public:
//     WorldGenerator(glm::vec2 chunkSize);
//
//     void generate();
//
//     const FaceInstances& getInstances() const;
// };
//
//
// #endif //MINI_MINECRAFT_WORLDGENERATOR_H
