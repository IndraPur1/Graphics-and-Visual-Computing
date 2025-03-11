#include <GL/glut.h>

// Fungsi untuk menampilkan berbagai primitif OpenGL
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan layar sebelum menggambar

    // GL_POINTS (Titik-titik)
    glColor3f(1.0, 0.0, 0.0); // Warna merah
    glPointSize(5.0); // Ukuran titik
    glBegin(GL_POINTS);
        glVertex2f(-0.85, 0.0);
        glVertex2f(-0.83, 0.0);
        glVertex2f(-0.81, 0.0);
    glEnd();

    // GL_LINES (Garis-garis lurus)
    glColor3f(0.0, 1.0, 0.0); // Warna hijau
    glBegin(GL_LINES);
        glVertex2f(-0.75, 0.05);
        glVertex2f(-0.7, -0.05);
        glVertex2f(-0.7, 0.05);
        glVertex2f(-0.65, -0.05);
    glEnd();

    // GL_LINE_STRIP (Garis bersambung)
    glColor3f(0.0, 0.0, 1.0); // Warna biru
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.6, 0.05);
        glVertex2f(-0.55, -0.05);
        glVertex2f(-0.5, 0.05);
        glVertex2f(-0.45, -0.05);
    glEnd();

    // GL_LINE_LOOP (Garis loop tertutup)
    glColor3f(1.0, 1.0, 0.0); // Warna kuning
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.4, 0.05);
        glVertex2f(-0.35, -0.05);
        glVertex2f(-0.3, 0.05);
        glVertex2f(-0.35, 0.15);
    glEnd();

    // GL_TRIANGLE_FAN (Kipas segitiga)
    glColor3f(1.0, 0.0, 1.0); // Warna magenta
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.15, 0.0); // Titik pusat kipas
        glVertex2f(-0.2, -0.05);
        glVertex2f(-0.1, -0.05);
        glVertex2f(-0.05, 0.0);
        glVertex2f(-0.1, 0.05);
        glVertex2f(-0.2, 0.05);
        glVertex2f(-0.25, 0.0);
    glEnd();

    // GL_TRIANGLE_STRIP (Strip segitiga)
    glColor3f(0.0, 1.0, 1.0); // Warna biru
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.0, -0.05);
        glVertex2f(0.05, 0.05);
        glVertex2f(0.1, -0.05);
        glVertex2f(0.15, 0.05);
        glVertex2f(0.2, -0.05);
    glEnd();

    // GL_QUADS (Kotak-kotak)
    glColor3f(0.6, 0.4, 1.0); // Warna ungu muda
    glBegin(GL_QUADS);
        glVertex2f(0.25, -0.05);
        glVertex2f(0.35, -0.05);
        glVertex2f(0.35, 0.05);
        glVertex2f(0.25, 0.05);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.37, -0.05);
        glVertex2f(0.47, -0.05);
        glVertex2f(0.47, 0.05);
        glVertex2f(0.37, 0.05);
    glEnd();

    // GL_QUAD_STRIP (Strip persegi panjang)
    glColor3f(1.0, 0.5, 0.2); // Warna oranye
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.52, -0.05);
        glVertex2f(0.52, 0.05);
        glVertex2f(0.6, -0.05);
        glVertex2f(0.6, 0.05);
        glVertex2f(0.68, -0.05);
        glVertex2f(0.68, 0.05);
    glEnd();

    glFlush(); // Menampilkan hasil ke layar
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600); // Ukuran window 800x600 px
    
    // Area tampilan 2D dengan koordinat -1 sampai 1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 0.80, -1.0, 1.0);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Primitif OpenGL"); // Nama window
    glutDisplayFunc(display);
    glClearColor(1.0, 1.0, 1.0, 1.0); // Warna latar belakang putih
    glutMainLoop(); // Memulai loop utama
    return 0;
}

