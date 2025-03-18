#include <GL/glut.h>

// Fungsi menampilkan segi empat
void tampilkanSegiEmpat(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan layar

    // Segi empat 1 (merah) - Kiri bawah
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(-0.80f, 0.00f, -0.40f, -0.40f);

    // Segi empat 2 (hijau) - Tengah bawah
    glColor3f(0.0f, 1.0f, 0.0f);
    glRectf(-0.30f, 0.00f, 0.10f, -0.40f);

    // Segi empat 3 (biru navy) - Kanan bawah
    glColor3f(0.0f, 0.0f, 1.0f);
    glRectf(0.20f, 0.00f, 0.60f, -0.40f);

    // Segi empat 4 (kuning) - Atas kiri
    glColor3f(1.0f, 1.0f, 0.0f);
    glRectf(-0.60f, 0.40f, -0.20f, 0.00f);

    // Segi empat 5 (biru cerah) - Atas kanan
    glColor3f(0.0f, 1.0f, 1.0f);
    glRectf(0.0f, 0.40f, 0.40f, 0.00f);
    
    // Segi empat 6 (hitam) - Atas kanan
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(-0.30f, 0.80f, 0.10f, 0.40f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inisialisasi GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mode tampilan: Single buffer + RGB
    glutInitWindowSize(640, 480); // Ukuran jendela
    glutInitWindowPosition(100, 100); // Posisi jendela di layar
    glutCreateWindow("Menara Segiempat"); // Judul jendela

    // Warna latar belakang (putih)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Area tampilan 2D dengan koordinat -1 sampai 1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 0.80, -1.0, 1.0);

    glutDisplayFunc(tampilkanSegiEmpat); // Panggil fungsi tampilan
    glutMainLoop(); // Masuk ke loop utama GLUT

    return 0;
}

