cmake_minimum_required(VERSION 4.3)
project(mini_minecraft)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

add_compile_definitions(GL_SILENCE_DEPRECATION)

set(CMAKE_CXX_STANDARD 20)
set(IMGUI_DIR vendor/imgui)
set(STB_DIR vendor/stb)

add_executable(mini_minecraft main.cpp
        src/Minecraft.cpp
        src/Minecraft.h
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertexArray.cpp
        src/VertexArray.h
        src/VertexBufferLayout.cpp
        src/VertexBufferLayout.h
        src/Shader.cpp
        src/Shader.h
        src/ShaderProgram.cpp
        src/ShaderProgram.h
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glut.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        src/Texture.cpp
        src/Texture.h
        src/Camera.cpp
        src/Camera.h
        src/WorldGenerator.cpp
        src/WorldGenerator.h)

target_include_directories(mini_minecraft PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${STB_DIR}
)

target_link_libraries(mini_minecraft PRIVATE "-framework OpenGL -framework GLUT" glm::glm)