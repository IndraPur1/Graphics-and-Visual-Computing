#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265358979323846;

// Fungsi untuk menggambar lingkaran
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Titik pusat lingkaran
    for (int i = 0; i <= 360; i++) {
        float angle = i * PI / 180; // Konversi derajat ke radian
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Menggambar lingkaran di tengah layar
    glColor3f(1.0, 0.0, 0.0); // Warna merah
    drawCircle(0.0, 0.0, 0.5);

    glFlush();
}

// Fungsi inisialisasi
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Latar belakang putih
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Mengatur sistem koordinat
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lingkaran OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

