#include <GL/glut.h>
#include <math.h>

float angle = 0.0f;

// Fungsi menggambar lingkaran
void drawCircle(float cx, float cy, float r, int segments, float rColor, float gColor, float bColor) {
    glColor3f(rColor, gColor, bColor);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Fungsi menggambar garis spoke velg
void drawSpokes(float cx, float cy, float r, int spokeCount) {
    glColor3f(0.3f, 0.3f, 0.3f); // Abu-abu tua
    glBegin(GL_LINES);
    for (int i = 0; i < spokeCount; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(spokeCount);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx, cy);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Fungsi menggambar roda dengan efek mendalam
void drawRealisticWheel() {
    // Ban luar (hitam)
    drawCircle(0.0f, 0.0f, 0.06f, 30, 0.1f, 0.1f, 0.1f);

    // Velg lebih dalam (abu gelap dan terang berlapis)
    drawCircle(0.0f, 0.0f, 0.045f, 30, 0.3f, 0.3f, 0.3f);
    drawCircle(0.0f, 0.0f, 0.035f, 30, 0.5f, 0.5f, 0.5f);
    drawCircle(0.0f, 0.0f, 0.025f, 30, 0.7f, 0.7f, 0.7f);

    // Spoke velg
    drawSpokes(0.0f, 0.0f, 0.03f, 6);
}

// Fungsi menggambar mobil
void drawCar() {
    // Body bawah
    glColor3f(0.0, 0.6, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.4f, -0.1f);
        glVertex2f(0.4f, -0.1f);
        glVertex2f(0.4f, 0.1f);
        glVertex2f(-0.4f, 0.1f);
    glEnd();

    // Atap mobil
    glColor3f(0.0, 0.3, 0.8);
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.1f, 0.2f);
        glVertex2f(0.2f, 0.1f);
    glEnd();

    // Jendela
    glColor3f(0.8, 0.9, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.11f);
        glVertex2f(-0.05f, 0.18f);
        glVertex2f(0.05f, 0.18f);
        glVertex2f(0.1f, 0.11f);
    glEnd();

    // Gagang pintu
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, 0.02f);
        glVertex2f(0.12f, 0.02f);
        glVertex2f(0.12f, 0.04f);
        glVertex2f(0.05f, 0.04f);
    glEnd();

    // Lampu depan
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(0.4f, 0.02f);
        glVertex2f(0.43f, 0.02f);
        glVertex2f(0.43f, 0.08f);
        glVertex2f(0.4f, 0.08f);
    glEnd();

    // Lampu belakang
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.43f, 0.02f);
        glVertex2f(-0.4f, 0.02f);
        glVertex2f(-0.4f, 0.08f);
        glVertex2f(-0.43f, 0.08f);
    glEnd();

        // Roda kiri
    glPushMatrix();
        glTranslatef(-0.25f, -0.1f, 0.0f);  // dari -0.15f menjadi -0.1f
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        drawRealisticWheel();
    glPopMatrix();

    // Roda kanan
    glPushMatrix();
        glTranslatef(0.25f, -0.1f, 0.0f);   // dari -0.15f menjadi -0.1f
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        drawRealisticWheel();
    glPopMatrix();

}

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCar();
    glFlush();
}

// Update animasi
void update(int value) {
    angle -= 5.0f;
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

// Main program
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 800)/2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - 600)/2);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Mobil 2D Realistis - OpenGL");
    glClearColor(0.5, 0.8, 1.0, 1.0); // Warna langit biru muda
    glutDisplayFunc(display);
    glutTimerFunc(30, update, 0);
    glutMainLoop();
    return 0;
}

