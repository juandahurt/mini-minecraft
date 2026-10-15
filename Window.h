#ifndef MINI_MINECRAFT_WINDOW_H
#define MINI_MINECRAFT_WINDOW_H

class Window {
public:
    Window();
    ~Window();

    // just some wrapping so we can work with glut :)
    inline static Window* instance;
    static void create(int argc, char** argv);
    static void onUpdateWrapper();
    static void onDisplayWrapper();

    // callbacks
    void onUpdate();
    void onDisplay();
private:
    const char* m_title;
    int m_width;
    int m_height;
};

#endif //MINI_MINECRAFT_WINDOW_H
