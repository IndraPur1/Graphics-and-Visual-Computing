#include <GL/glut.h>
#include <cmath>
#include <string>
#include <iostream>

// Konstanta
const float PI = 3.14159265359;
const int SLICES = 30;
const int STACKS = 30;

// Variabel untuk pilihan proyeksi
enum ProjectionType {
    ORTHO_PLAN,
    ORTHO_FRONT,
    ORTHO_SIDE,
    ORTHO_ISOMETRIC,
    ORTHO_DIMETRIC,
    ORTHO_TRIMETRIC,
    PERSP_ONE_POINT,
    PERSP_TWO_POINT,
    PERSP_THREE_POINT,
    PROJECTION_COUNT
};

ProjectionType currentProjection = ORTHO_PLAN;
std::string projectionNames[PROJECTION_COUNT] = {
    "Orthographic: Plan View (Top)",
    "Orthographic: Front View",
    "Orthographic: Side View",
    "Orthographic: Isometric (120° equal angles)",
    "Orthographic: Dimetric (two equal angles)",
    "Orthographic: Trimetric (three different angles)",
    "Perspective: 1 Point Vanishing",
    "Perspective: 2 Points Vanishing",
    "Perspective: 3 Points Vanishing"
};

// Fungsi untuk menggambar kerucut
void drawCone(float baseRadius, float height, int slices) {
    glPushMatrix();
    
    // Sisi kerucut
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height); // Puncak kerucut
    
    for (int i = 0; i <= slices; i++) {
        float theta = 2.0f * PI * i / slices;
        float x = baseRadius * cos(theta);
        float y = baseRadius * sin(theta);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
    
    // Alas kerucut
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Pusat alas
    
    for (int i = slices; i >= 0; i--) {
        float theta = 2.0f * PI * i / slices;
        float x = baseRadius * cos(theta);
        float y = baseRadius * sin(theta);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar tabung
void drawCylinder(float radius, float height, int slices) {
    float x, y, angle;
    
    // Sisi tabung
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        angle = 2.0f * PI * i / slices;
        x = radius * cos(angle);
        y = radius * sin(angle);
        
        glVertex3f(x, y, 0.0f);
        glVertex3f(x, y, height);
    }
    glEnd();
    
    // Alas bawah tabung
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Pusat alas bawah
    
    for (int i = slices; i >= 0; i--) {
        angle = 2.0f * PI * i / slices;
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
    
    // Alas atas tabung
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height); // Pusat alas atas
    
    for (int i = 0; i <= slices; i++) {
        angle = 2.0f * PI * i / slices;
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
    }
    glEnd();
}

// Fungsi untuk menggambar sayap segitiga
void drawWings() {
    // Panjang sayap
    float wingLength = 1.0f;
    float wingWidth = 0.5f;
    
    // Sayap pertama
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, 0.0f, 0.0f);     // Titik di body roket
    glVertex3f(0.5f + wingLength, 0.0f, 0.0f); // Titik ujung sayap
    glVertex3f(0.5f, 0.0f, wingWidth); // Titik di bagian atas sayap
    glEnd();
    glPopMatrix();
    
    // Sayap kedua (rotasi 120 derajat)
    glPushMatrix();
    glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f + wingLength, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, wingWidth);
    glEnd();
    glPopMatrix();
    
    // Sayap ketiga (rotasi 240 derajat)
    glPushMatrix();
    glRotatef(240.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f + wingLength, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, wingWidth);
    glEnd();
    glPopMatrix();
}

// Fungsi untuk menggambar roket secara utuh
void drawRocket() {
    // Warna untuk kerucut (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    
    // Menggambar kerucut di atas
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    drawCone(0.5f, 1.0f, SLICES);
    glPopMatrix();
    
    // Warna untuk body (abu-abu)
    glColor3f(0.7f, 0.7f, 0.7f);
    
    // Menggambar tabung sebagai body
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawCylinder(0.5f, 2.0f, SLICES);
    glPopMatrix();
    
    // Warna untuk sayap (biru)
    glColor3f(0.0f, 0.0f, 1.0f);
    
    // Menggambar sayap
    glPushMatrix();
    drawWings();
    glPopMatrix();
}

// Fungsi untuk menggambar sumbu koordinat dengan label
void drawAxis(float size) {
    glDisable(GL_LIGHTING);
    
    glBegin(GL_LINES);
    // Sumbu X (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    
    // Sumbu Y (hijau)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    
    // Sumbu Z (biru)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, size);
    glEnd();
    
    // Label sumbu
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f(size + 0.1f, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos3f(0.0f, size + 0.1f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos3f(0.0f, 0.0f, size + 0.1f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Z');
    
    glEnable(GL_LIGHTING);
}

// Fungsi untuk menerapkan proyeksi yang dipilih
void setProjection(int width, int height) {
    float aspect = (float)width / (float)height;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    switch (currentProjection) {
        case ORTHO_PLAN: // Top View (XY plane)
            glOrtho(-4.0 * aspect, 4.0 * aspect, -4.0, 4.0, -20.0, 20.0);
            break;
            
        case ORTHO_FRONT: // Front View (XZ plane)
            glOrtho(-4.0 * aspect, 4.0 * aspect, -4.0, 4.0, -20.0, 20.0);
            break;
            
        case ORTHO_SIDE: // Side View (YZ plane)
            glOrtho(-4.0 * aspect, 4.0 * aspect, -4.0, 4.0, -20.0, 20.0);
            break;
            
        case ORTHO_ISOMETRIC: // Isometric (equal angles)
            glOrtho(-6.0 * aspect, 6.0 * aspect, -6.0, 6.0, -20.0, 20.0);
            break;
            
        case ORTHO_DIMETRIC: // Dimetric (two equal angles)
            glOrtho(-6.0 * aspect, 6.0 * aspect, -6.0, 6.0, -20.0, 20.0);
            break;
            
        case ORTHO_TRIMETRIC: // Trimetric (three different angles)
            glOrtho(-6.0 * aspect, 6.0 * aspect, -6.0, 6.0, -20.0, 20.0);
            break;
            
        case PERSP_ONE_POINT: // One point perspective
            gluPerspective(35.0, aspect, 0.1, 100.0);
            break;
            
        case PERSP_TWO_POINT: // Two point perspective
            gluPerspective(45.0, aspect, 0.1, 100.0);
            break;
            
        case PERSP_THREE_POINT: // Three point perspective
            gluPerspective(60.0, aspect, 0.1, 100.0);
            break;
            
        default:
            gluPerspective(45.0, aspect, 0.1, 100.0);
            break;
    }
    
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk menerapkan transformasi kamera berdasarkan proyeksi
void positionCamera() {
    glLoadIdentity();
    
    switch (currentProjection) {
        case ORTHO_PLAN: // Plan View (XY plane, looking down from top)
            gluLookAt(0.0f, 0.0f, 10.0f,   // Posisi kamera
                      0.0f, 0.0f, 0.0f,    // Titik target
                      0.0f, 1.0f, 0.0f);   // Up vector
            break;
            
        case ORTHO_FRONT: // Front View (XZ plane)
            gluLookAt(0.0f, -10.0f, 1.5f,  // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        case ORTHO_SIDE: // Side View (YZ plane)
            gluLookAt(10.0f, 0.0f, 1.5f,   // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        case ORTHO_ISOMETRIC: // Isometric (equal angles)
            // Isometric: sudut yang sama (~ 35.264° = arctan(1/v2)) dari sumbu X, Y dan Z
            gluLookAt(7.0f, 7.0f, 7.0f,    // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        case ORTHO_DIMETRIC: // Dimetric (two equal angles)
            // Dimetric: dua sudut yang sama (unequal foreshortening)
            gluLookAt(8.5f, 4.0f, 7.0f,    // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        case ORTHO_TRIMETRIC: // Trimetric (three different angles)
            // Trimetric: tiga sudut berbeda (all axes have different foreshortening)
            gluLookAt(7.5f, 3.0f, 5.0f,    // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        case PERSP_ONE_POINT: // One point perspective (frontal view with depth)
            // Satu titik hilang: tampak depan dengan kedalaman
            gluLookAt(0.0f, -8.0f, 1.5f,   // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        case PERSP_TWO_POINT: // Two point perspective (corner view)
            // Dua titik hilang: tampak sudut dengan dua arah menghilang
            gluLookAt(7.0f, -7.0f, 1.5f,   // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        case PERSP_THREE_POINT: // Three point perspective (corner view with elevated eye)
            // Tiga titik hilang: tampak sudut dengan mata yang ditinggikan
            gluLookAt(7.0f, -7.0f, 5.0f,   // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
            
        default:
            gluLookAt(5.0f, 5.0f, 5.0f,    // Posisi kamera
                      0.0f, 0.0f, 1.5f,    // Titik target
                      0.0f, 0.0f, 1.0f);   // Up vector
            break;
    }
}

// Fungsi untuk menampilkan teks tentang proyeksi saat ini
void displayProjectionInfo() {
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Background hitam transparan untuk teks
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(5, 5);
    glVertex2f(795, 5);
    glVertex2f(795, 30);
    glVertex2f(5, 30);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(10, 15);
    
    std::string info = projectionNames[currentProjection] + 
                      " (Press Space to change projection)";
    
    for (size_t i = 0; i < info.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, info[i]);
    }
    
    // Tampilkan petunjuk untuk mengganti sudut pandang
    glRasterPos2i(10, 580);
    std::string viewInfo = "Press arrow keys to rotate view";
    
    for (size_t i = 0; i < viewInfo.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, viewInfo[i]);
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}

// Variabel untuk rotasi manual
float manualRotateX = 0.0f;
float manualRotateY = 0.0f;

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    positionCamera();
    
    // Terapkan rotasi manual (hanya untuk mode tertentu)
    if (currentProjection >= PERSP_ONE_POINT) {
        glRotatef(manualRotateX, 1.0f, 0.0f, 0.0f);
        glRotatef(manualRotateY, 0.0f, 1.0f, 0.0f);
    }
    
    // Menggambar sumbu koordinat
    drawAxis(3.0f);
    
    // Menggambar roket
    drawRocket();
    
    // Menampilkan informasi proyeksi
    displayProjectionInfo();
    
    glutSwapBuffers();
}

// Fungsi reshape
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    setProjection(width, height);
}

// Fungsi keyboard
void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        // Mengubah jenis proyeksi saat spasi ditekan
        currentProjection = static_cast<ProjectionType>((currentProjection + 1) % PROJECTION_COUNT);
        setProjection(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        glutPostRedisplay();
    }
    else if (key == 27) { // ESC key
        exit(0);
    }
}

// Fungsi special keys (untuk panah)
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            manualRotateX += 5.0f;
            break;
        case GLUT_KEY_DOWN:
            manualRotateX -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            manualRotateY += 5.0f;
            break;
        case GLUT_KEY_LEFT:
            manualRotateY -= 5.0f;
            break;
    }
    glutPostRedisplay();
}

// Fungsi inisialisasi
void init() {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f); // Background biru gelap
    glEnable(GL_DEPTH_TEST);
    
    // Aktivasi blending untuk transparansi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Pengaturan pencahayaan yang lebih baik
    GLfloat light_position[] = { 10.0f, 10.0f, 10.0f, 0.0f };
    GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    // Cahaya kedua dari arah yang berbeda
    GLfloat light1_position[] = { -5.0f, -5.0f, 5.0f, 0.0f };
    GLfloat light1_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    // Kualitas material yang lebih baik
    GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// Fungsi main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Roket 3D dengan Berbagai Proyeksi");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    
    glutMainLoop();
    return 0;
}
