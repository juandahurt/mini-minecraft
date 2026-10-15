cmake_minimum_required(VERSION 4.3)
project(mini_minecraft)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_compile_definitions(GL_SILENCE_DEPRECATION)

set(CMAKE_CXX_STANDARD 20)

add_executable(mini_minecraft main.cpp)

target_include_directories(mini_minecraft PRIVATE
    ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR}
)

target_link_libraries(mini_minecraft PRIVATE "-framework OpenGL -framework GLUT")