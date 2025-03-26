#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f;  // Posisi awal kamera
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, h, w;

// Fungsi untuk menangani perubahan ukuran jendela
void Reshape(int w1, int h1) {
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk memutar kamera (melihat kiri/kanan)
void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk maju/mundur kamera
void moveMeFlat(int i) {
    x = x + i * (lx) * 0.1;
    z = z + i * (lz) * 0.1;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk menggambar grid di lantai
void Grid() {
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for (i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

// Fungsi untuk menggambar kubus kayu
void KotakKayu() {
    glPushMatrix();
    glTranslatef(0, 0, 3);
    glBegin(GL_QUADS);
    glVertex3f(-3.0f, -3.0f, 0.0f);
    glVertex3f(3.0f, -3.0f, 0.0f);
    glVertex3f(3.0f, 3.0f, 0.0f);
    glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

// Fungsi display untuk menggambar objek dan grid
void display() {
    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    KotakKayu();
    glutSwapBuffers();
    glFlush();
}

// Fungsi menangani input keyboard untuk pergerakan kamera
void pressKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        deltaAngle = -0.01f;
        break;
    case GLUT_KEY_RIGHT:
        deltaAngle = 0.01f;
        break;
    case GLUT_KEY_UP:
        deltaMove = 1;
        break;
    case GLUT_KEY_DOWN:
        deltaMove = -1;
        break;
    }
}

// Fungsi menangani saat tombol dilepas
void releaseKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        if (deltaAngle < 0.0f)
            deltaAngle = 0.0f;
        break;
    case GLUT_KEY_RIGHT:
        if (deltaAngle > 0.0f)
            deltaAngle = 0.0f;
        break;
    case GLUT_KEY_UP:
        if (deltaMove > 0)
            deltaMove = 0;
        break;
    case GLUT_KEY_DOWN:
        if (deltaMove < 0)
            deltaMove = 0;
        break;
    }
}

// Variabel pencahayaan
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };

// Fungsi mengaktifkan pencahayaan
void lighting() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

// Inisialisasi OpenGL
void init(void) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("3D Lighting");
    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return (0);
}

