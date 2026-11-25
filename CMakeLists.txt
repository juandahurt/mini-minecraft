cmake_minimum_required(VERSION 3.20)
project(mini_minecraft)

include(FetchContent)

# --- OpenGL (lo provee el sistema / drivers) ---
find_package(OpenGL REQUIRED)

# --- imgui (submódulo de git): se inicializa automáticamente si falta ---
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp")
    find_package(Git REQUIRED)
    message(STATUS "Inicializando submódulo vendor/imgui...")
    execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMODULE_RESULT)
    if (NOT GIT_SUBMODULE_RESULT EQUAL 0)
        message(FATAL_ERROR "No se pudo inicializar el submódulo vendor/imgui")
    endif()
endif()

# --- glm: se usa la instalada en el sistema o se descarga ---
find_package(glm CONFIG QUIET)
if (NOT glm_FOUND)
    message(STATUS "glm no encontrado, descargándolo...")
    set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.1
            GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(glm)
endif()

# --- GLUT: en macOS viene con el sistema; en Linux/Windows se descarga freeglut si falta ---
if (APPLE)
    find_package(GLUT REQUIRED)
    set(GLUT_LIBS "-framework OpenGL -framework GLUT -framework ApplicationServices")
else()
    find_package(GLUT QUIET)
    if (GLUT_FOUND)
        set(GLUT_LIBS OpenGL::GL GLUT::GLUT)
    else()
        message(STATUS "GLUT no encontrado, descargando freeglut...")
        set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
        set(FREEGLUT_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
        set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
        FetchContent_Declare(freeglut
                GIT_REPOSITORY https://github.com/freeglut/freeglut.git
                GIT_TAG v3.6.0
                GIT_SHALLOW TRUE)
        FetchContent_MakeAvailable(freeglut)
        set(GLUT_INCLUDE_DIR ${freeglut_SOURCE_DIR}/include)
        set(GLUT_LIBS OpenGL::GL freeglut_static)
    endif()
endif()

add_compile_definitions(GL_SILENCE_DEPRECATION)

set(CMAKE_CXX_STANDARD 20)
set(IMGUI_DIR vendor/imgui)
set(STB_DIR vendor/stb)
set(FASTNOISE_DIR vendor/FastNoiseLite)

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
        src/WorldGenerator.h
        src/Vertex.cpp
        src/Vertex.h
        src/Chunk.cpp
        src/Chunk.h
        src/Face.h
        src/World.cpp
        src/World.h
        src/Material.h
        src/FaceDirection.h
        src/Player.cpp
        src/Player.h
        src/Ray.cpp
        src/Ray.h)

target_include_directories(mini_minecraft PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${STB_DIR}
        ${FASTNOISE_DIR}
)

target_link_libraries(mini_minecraft PRIVATE ${GLUT_LIBS} glm::glm)
