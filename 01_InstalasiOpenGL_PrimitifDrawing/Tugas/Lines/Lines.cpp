#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>

void Garis(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.00, 0.40, 0.0);
    glVertex3f(0.00, -0.40, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Green Line");
    glutDisplayFunc(Garis);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glutMainLoop();
    return 0;
}
