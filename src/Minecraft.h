#ifndef MINI_MINECRAFT_WINDOW_H
#define MINI_MINECRAFT_WINDOW_H
#include <memory>
#include <string>
#include <unordered_set>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"

class Minecraft {
private:
    std::string m_title;
    int m_width;
    int m_height;

    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<VertexArray> m_vao;
    std::unique_ptr<VertexBuffer> m_vbo;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<ShaderProgram> m_program;
    std::unique_ptr<Texture> m_texture;
    glm::vec3 m_translation;

    glm::mat4 m_projection;

    std::unique_ptr<Camera> m_camera;

    std::unordered_set<unsigned char> m_pressedKeys;

    void setup();

public:
    Minecraft();
    ~Minecraft();

    void run();

    // just some wrapping so we can work with glut :)
    inline static std::unique_ptr<Minecraft> instance;
    static void create(int argc, char** argv);
    static void onUpdateWrapper();
    static void onDisplayWrapper();
    static void onReshapeWrapper(int w, int h);
    static void onMouseWrapper(int button, int state, int x, int y);
    static void onMotionWrapper(int x, int y);
    static void onPassiveMotionWrapper(int x, int y);
    static void onKeyboardWrapper(unsigned char key, int x, int y);
    static void onKeyboardUpWrapper(unsigned char key, int x, int y);

    // callbacks
    void onUpdate();
    void onDisplay();
    void onReshape(int w, int h);
    void onMouse(int button, int state, int x, int y);
    void onMotion(int x, int y);
    void onPassiveMotion(int x, int y);
    void onKeyboard(unsigned char key, int x, int y);
    void onKeyboardUp(unsigned char key, int x, int y);
};

#endif //MINI_MINECRAFT_WINDOW_H
