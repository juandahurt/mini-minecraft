#include <iostream>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#endif

void display() {
    glClearColor(1, 0.2, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    std::cout << "program began." << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("mini minecraft");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
