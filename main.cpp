#include <iostream>
#include "src/Minecraft.h"

int main(int argc, char** argv) {
    Minecraft::create(argc, argv);
    Minecraft::instance->run();
    return 0;
}
