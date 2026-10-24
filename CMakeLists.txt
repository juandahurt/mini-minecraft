cmake_minimum_required(VERSION 4.3)
project(mini_minecraft)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

add_compile_definitions(GL_SILENCE_DEPRECATION)

set(CMAKE_CXX_STANDARD 20)

add_executable(mini_minecraft main.cpp
        Window.cpp
        Window.h
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h)

target_include_directories(mini_minecraft PRIVATE
    ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR}
)

target_link_libraries(mini_minecraft PRIVATE "-framework OpenGL -framework GLUT" glm::glm)