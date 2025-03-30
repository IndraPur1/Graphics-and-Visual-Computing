#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=15.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int bitmapHeight=12;

void Reshape(int w1, int h1) {
    // Fungsi reshape
    if(h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + lx,y + ly,z + lz,
        0.0f,1.0f,0.0f
    );
}

void orientMe(float ang) {
    // Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + lx,y + ly,z + lz,
        0.0f,0.1f,0.0f
    );
}

void moveMeFlat(int i) {
    // Fungsi ini untuk maju mundur kamera
    x = x + i*(lx)*0.01;
    z = z + i*(lz)*0.01;
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + lx,y + ly,z + lz,
        0.0f,1.0f,0.0f
    );
}

void Grid() {
    // Fungsi untuk membuat grid di "lantai"
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for(i=Z_MIN;i<Z_MAX;i+=gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for(i=X_MIN;i<X_MAX;i+=gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

void Mobil3d() {
    // Depan 
    glPushMatrix();
    glTranslatef(0,0,3);
    glColor3f(0.5f, 1.0f, 1.0f);//cyan
    glBegin(GL_QUADS);
    glVertex3f(-1.9f,1.0f,0.0f);
    glVertex3f(1.9f,1.0f,0.0f);
    glVertex3f(1.4f,1.8f,0.0f);
    glVertex3f(-1.4f,1.8f,0.0f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,3);
	glColor3f(1.0f, 0.0f, 0.0f); // merah
    glBegin(GL_QUADS);
    glVertex3f(-3.0f,0.0f,0.0f);
    glVertex3f(3.0f,0.0f,0.0f);
    glVertex3f(3.0f,1.0f,0.0f);
    glVertex3f(-3.0f,1.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,3);
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f); // Warna oranye solid
    glBegin(GL_QUADS);
    glVertex3f(-2.2f,1.0f,0.0f);
    glVertex3f(2.2f,1.0f,0.0f);
    glVertex3f(1.5f,2.0f,0.0f);
    glVertex3f(-1.5f,2.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    


    // Belakang 
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    glTranslatef(0,0,-1);
    glColor3f(0.5f, 1.0f, 1.0f);//cyan
    glBegin(GL_QUADS);
    glVertex3f(-1.9f,-1.0f,0.0f);
    glVertex3f(1.9f,-1.0f,0.0f);
    glVertex3f(1.45f,-1.75f,0.0f);
    glVertex3f(-1.45f,-1.75f,0.0f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    glTranslatef(0,0,-1);
    glColor3f(1.0f, 0.0f, 0.0f); // merah
    glBegin(GL_QUADS);
    glVertex3f(-3.0f,0.0f,0.0f);
    glVertex3f(3.0f,0.0f,0.0f);
    glVertex3f(3.0f,-1.0f,0.0f);
    glVertex3f(-3.0f,-1.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    glTranslatef(0,0,-1);
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f); // Warna oranye solid
    glBegin(GL_QUADS);
    glVertex3f(-2.2f,-1.0f,0.0f);
    glVertex3f(2.2f,-1.0f,0.0f);
    glVertex3f(1.5f,-2.0f,0.0f);
    glVertex3f(-1.5f,-2.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    

    // Bawah 
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0,0,3);
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f); // Warna oranye solid
    glBegin(GL_QUADS);
    glVertex3f(-3.0f,1.0f,-3.0f);
    glVertex3f(3.0f,1.0f,-3.0f);
    glVertex3f(3.0f,3.0f,-3.0f);
    glVertex3f(-3.0f,3.0f,-3.0f);
    glEnd();
    glPopMatrix();
    
    // Bawah 
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0,0,3);
    glColor3f(1.0f, 0.0f, 0.0f); // merah
    glBegin(GL_QUADS);
    glVertex3f(-3.0f,1.0f,-4.0f);
    glVertex3f(-2.2f,1.0f,-4.0f);
    glVertex3f(-2.2f,3.0f,-4.0f);
    glVertex3f(-3.0f,3.0f,-4.0f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0,0,3);
    glColor3f(1.0f, 0.0f, 0.0f); // merah
    glBegin(GL_QUADS);
    glVertex3f(3.0f,1.0f,-4.0f);
    glVertex3f(2.2f,1.0f,-4.0f);
    glVertex3f(2.2f,3.0f,-4.0f);
    glVertex3f(3.0f,3.0f,-4.0f);
    glEnd();
    glPopMatrix();
    
    // Atas Kuning
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0,0,3);
   	glColor3f(1.0f, 0.0f, 0.0f); // merah
    glBegin(GL_QUADS);
    glVertex3f(-1.5f,1.0f,-5.0f);
    glVertex3f(1.5f,1.0f,-5.0f);
    glVertex3f(1.5f,3.0f,-5.0f);
    glVertex3f(-1.5f,3.0f,-5.0f);
    glEnd();
    glPopMatrix();
//
    // Kiri Putih
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(0,0,3);
    glColor3f(1.0f, 0.0f, 0.0f); // merah
    glBegin(GL_QUADS);
    glVertex3f(1.0f,0.0f,0.0f);
    glVertex3f(3.0f,0.0f,0.0f);
    glVertex3f(3.0f,1.0f,0.0f);
    glVertex3f(1.0f,1.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(0,0,3);
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f); // Warna oranye solid
    glBegin(GL_QUADS);
    glVertex3f(1.0f,1.0f,-0.8f);
    glVertex3f(3.0f,1.0f,-0.8f);
    glVertex3f(3.0f,2.0f,-1.5f);
    glVertex3f(1.0f,2.0f,-1.5f);
    glEnd();
    glPopMatrix();
    
//
    // Kanan 
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(0,0,3);
    glColor3f(0.5f, 1.0f, 1.0f);//cyan
    glBegin(GL_QUADS);
    glVertex3f(-1.2f,1.1f,-0.85f);
    glVertex3f(-2.8f,1.1f,-0.85f);
    glVertex3f(-2.8f,1.9f,-1.4f);
    glVertex3f(-1.2f,1.9f,-1.4f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(0,0,3);
    glColor3f(1.0f, 0.0f, 0.0f); // merah
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(-3.0f,0.0f,0.0f);
    glVertex3f(-3.0f,1.0f,0.0f);
    glVertex3f(-1.0f,1.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    // Kanan 
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(0,0,3);
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f); // Warna oranye solid
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,1.0f,-0.8f);
    glVertex3f(-3.0f,1.0f,-0.8f);
    glVertex3f(-3.0f,2.0f,-1.5f);
    glVertex3f(-1.0f,2.0f,-1.5f);
    glEnd();
    glPopMatrix();
    
    // Tire1
    glPushMatrix();
    glTranslatef(-2, -0.05, 0.9);
    glScalef(3.0, 3.0, 3.0); // Penambahan penskalaan sebesar 3x
    glColor3f(0.2f, 0.2f, 0.2f);
    glutSolidTorus(0.05, 0.1, 10, 10);
    glPopMatrix();

    // Tire2
    glPushMatrix();
    glTranslatef(2, -0.05, 0.9);
    glScalef(3.0, 3.0, 3.0); // Penambahan penskalaan sebesar 3x
    glutSolidTorus(0.05, 0.1, 10, 10);
    glPopMatrix();

	//Tire3
	glPushMatrix();
    glTranslatef(2, -0.05, 3.0);
    glScalef(3.0, 3.0, 3.0); // Penambahan penskalaan sebesar 3x
    glutSolidTorus(0.05, 0.1, 10, 10);
    glPopMatrix();
    
    //Tire4
    glPushMatrix();
    glTranslatef(-2, -0.05, 3.0);
    glScalef(3.0, 3.0, 3.0); // Penambahan penskalaan sebesar 3x
    glutSolidTorus(0.05, 0.1, 10, 10);
    glPopMatrix();
    
//
}




void display() {
    
    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Gambar grid
    Grid();
    // Gambar objek di sini...
    Mobil3d();
    glutSwapBuffers();
    glFlush();
}

void pressKey(int key, int x, int y) {
    // Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
    // Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak
    switch (key) {
        case GLUT_KEY_LEFT :
            deltaAngle = -0.01f;
            break;
        case GLUT_KEY_RIGHT :
            deltaAngle = 0.01f;
            break;
        case GLUT_KEY_UP :
            deltaMove = 1;
            break;
        case GLUT_KEY_DOWN :
            deltaMove = -1;
            break;
    }
}

void releaseKey(int key, int x, int y) {
    // Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
    // Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti
    switch (key) {
        case GLUT_KEY_LEFT :
            if (deltaAngle < 0.0f)
                deltaAngle = 0.0f;
            break;
        case GLUT_KEY_RIGHT :
            if (deltaAngle > 0.0f)
                deltaAngle = 0.0f;
            break;
        case GLUT_KEY_UP :
            if (deltaMove > 0)
                deltaMove = 0;
            break;
        case GLUT_KEY_DOWN :
            if (deltaMove < 0)
                deltaMove = 0;
            break;
    }
}

// Variable untuk pencahayaan
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.01f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.0f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 0.75f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 75.0f };

void lighting() {
    // Fungsi mengaktifkan pencahayaan
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
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("3D Lighting");
    glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombol keyboard dipencet terus)
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display); // Fungsi display-nya dipanggil terus-menerus
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return(0);
}
