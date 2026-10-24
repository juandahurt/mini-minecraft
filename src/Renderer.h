//
// Created by aureliano on 24/10/26.
//

#ifndef MINI_MINECRAFT_RENDERER_H
#define MINI_MINECRAFT_RENDERER_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif
#include <iostream>

#define GLCall(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__);

void GLClearError();
void GLLogCall(const char* function, const char* file, const int line);

class Renderer {
};


#endif //MINI_MINECRAFT_RENDERER_H
