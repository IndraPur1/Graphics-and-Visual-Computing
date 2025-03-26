#include <GL/glut.h>

// Joint angles
static int shoulder = 0, elbow = 0, wrist = 0, wristTwist = 0;
static int thumb1 = 20, thumb2 = 20, thumbTwist = 0; // Default thumb position more natural
static int indexBase = 0, indexMiddle = 0, indexTip = 0;
static int middleBase = 0, middleMiddle = 0, middleTip = 0;
static int ringBase = 0, ringMiddle = 0, ringTip = 0;
static int pinkyBase = 0, pinkyMiddle = 0, pinkyTip = 0;
static int sceneRotation = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    
    // Enable lighting
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

// Function to draw a finger segment
void drawFingerSegment(float length, float width, float height) {
    glPushMatrix();
    glScalef(length, width, height);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Function to draw a finger with 3 segments (base, middle, tip)
void drawFinger(float baseLength, float middleLength, float tipLength, 
                float width, float height, int baseAngle, int middleAngle, int tipAngle) {
    // Base segment
    glRotatef((GLfloat)baseAngle, 0.0, 0.0, 1.0);
    drawFingerSegment(baseLength, width, height);
    
    // Middle segment
    glTranslatef(baseLength/2, 0.0, 0.0);
    glRotatef((GLfloat)middleAngle, 0.0, 0.0, 1.0);
    glTranslatef(middleLength/2, 0.0, 0.0);
    drawFingerSegment(middleLength, width*0.9, height*0.9);
    
    // Tip segment
    glTranslatef(middleLength/2, 0.0, 0.0);
    glRotatef((GLfloat)tipAngle, 0.0, 0.0, 1.0);
    glTranslatef(tipLength/2, 0.0, 0.0);
    drawFingerSegment(tipLength, width*0.8, height*0.8);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set material properties
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.6, 1.0 };
    GLfloat mat_diffuse[] = { 0.4, 0.4, 0.8, 1.0 };
    GLfloat mat_specular[] = { 0.8, 0.8, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glPushMatrix();
    
    // Apply scene rotation around Y-axis
    glRotatef((GLfloat)sceneRotation, 0.0, 1.0, 0.0);
    
    // Coordinate system visualization
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.0); // X-axis in red
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    
    glColor3f(0.0, 1.0, 0.0); // Y-axis in green
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    
    glColor3f(0.0, 0.0, 1.0); // Z-axis in blue
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glEnable(GL_LIGHTING);
    
    // Shoulder
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Upper arm
    glPushMatrix();
    glScalef(2.0, 0.4, 0.6);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Elbow
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Lower arm
    glPushMatrix();
    glScalef(2.0, 0.4, 0.6);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Wrist
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)wristTwist, 1.0, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    
    // Palm
    glPushMatrix();
    glScalef(0.8, 0.3, 0.7);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // THUMB - SIGNIFICANTLY IMPROVED
    glPushMatrix();
    // Move thumb to side of palm - x is now positive to move it outward, z is negative to position correctly
    glTranslatef(0.0, -0.15, 0.35); 
    
    // Rotate thumb to point inward toward palm
    glRotatef(90.0, 0.0, 1.0, 0.0);  // Point thumb inward
    glRotatef(-45.0, 1.0, 0.0, 0.0); // Angle thumb to face other fingers
    glRotatef((GLfloat)thumbTwist, 0.0, 1.0, 0.0); // Allow twist control
    
    // Draw thumb base segment
    glRotatef((GLfloat)thumb1, 0.0, 0.0, 1.0);
    drawFingerSegment(0.25, 0.18, 0.18);
    
    // Draw thumb tip segment
    glTranslatef(0.125, 0.0, 0.0);
    glRotatef((GLfloat)thumb2, 0.0, 0.0, 1.0);
    glTranslatef(0.125, 0.0, 0.0);
    drawFingerSegment(0.25, 0.16, 0.16);
    glPopMatrix();
    
    // Index finger
    glPushMatrix();
    glTranslatef(0.4, 0.0, 0.25);
    drawFinger(0.3, 0.25, 0.2, 0.12, 0.12, indexBase, indexMiddle, indexTip);
    glPopMatrix();
    
    // Middle finger
    glPushMatrix();
    glTranslatef(0.4, 0.0, 0.08);
    drawFinger(0.32, 0.28, 0.22, 0.13, 0.13, middleBase, middleMiddle, middleTip);
    glPopMatrix();
    
    // Ring finger
    glPushMatrix();
    glTranslatef(0.4, 0.0, -0.12);
    drawFinger(0.3, 0.26, 0.2, 0.12, 0.12, ringBase, ringMiddle, ringTip);
    glPopMatrix();
    
    // Pinky finger
    glPushMatrix();
    glTranslatef(0.4, 0.0, -0.3);
    drawFinger(0.25, 0.2, 0.16, 0.1, 0.1, pinkyBase, pinkyMiddle, pinkyTip);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Scene rotation controls
        case 'a':  // Rotate scene left (around Y-axis)
            sceneRotation = (sceneRotation + 5) % 360;
            glutPostRedisplay();
            break;
        case 'd':  // Rotate scene right (around Y-axis)
            sceneRotation = (sceneRotation - 5) % 360;
            glutPostRedisplay();
            break;
            
        // Shoulder controls
        case 's':
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
            break;
        case 'S':
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();
            break;
            
        // Elbow controls
        case 'e':
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();
            break;
        case 'E':
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();
            break;
            
        // Wrist controls
        case 'w':
            wrist = (wrist + 5) % 360;
            glutPostRedisplay();
            break;
        case 'W':
            wrist = (wrist - 5) % 360;
            glutPostRedisplay();
            break;
            
        // Wrist twist controls
        case 'q':
            wristTwist = (wristTwist + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Q':
            wristTwist = (wristTwist - 5) % 360;
            glutPostRedisplay();
            break;
            
        // Thumb controls
        case 't':
            thumb1 = (thumb1 + 5) % 90;
            if (thumb1 > 60) thumb1 = 60;
            glutPostRedisplay();
            break;
        case 'T':
            thumb1 = (thumb1 - 5) % 90;
            if (thumb1 < 0) thumb1 = 0;
            glutPostRedisplay();
            break;
        case 'y':
            thumb2 = (thumb2 + 5) % 90;
            if (thumb2 > 60) thumb2 = 60;
            glutPostRedisplay();
            break;
        case 'Y':
            thumb2 = (thumb2 - 5) % 90;
            if (thumb2 < 0) thumb2 = 0;
            glutPostRedisplay();
            break;
        // NEW: Thumb twist control
        case 'g':
            thumbTwist = (thumbTwist + 5) % 360;
            glutPostRedisplay();
            break;
        case 'G':
            thumbTwist = (thumbTwist - 5) % 360;
            glutPostRedisplay();
            break;
            
        // Index finger controls
        case 'i':
            indexBase = (indexBase + 5) % 90;
            if (indexBase > 80) indexBase = 80;
            glutPostRedisplay();
            break;
        case 'I':
            indexBase = (indexBase - 5) % 90;
            if (indexBase < 0) indexBase = 0;
            glutPostRedisplay();
            break;
        case 'j':
            indexMiddle = (indexMiddle + 5) % 90;
            if (indexMiddle > 80) indexMiddle = 80;
            glutPostRedisplay();
            break;
        case 'J':
            indexMiddle = (indexMiddle - 5) % 90;
            if (indexMiddle < 0) indexMiddle = 0;
            glutPostRedisplay();
            break;
        case 'k':
            indexTip = (indexTip + 5) % 90;
            if (indexTip > 80) indexTip = 80;
            glutPostRedisplay();
            break;
        case 'K':
            indexTip = (indexTip - 5) % 90;
            if (indexTip < 0) indexTip = 0;
            glutPostRedisplay();
            break;
            
        // Middle finger controls
        case 'm':
            middleBase = (middleBase + 5) % 90;
            if (middleBase > 80) middleBase = 80;
            glutPostRedisplay();
            break;
        case 'M':
            middleBase = (middleBase - 5) % 90;
            if (middleBase < 0) middleBase = 0;
            glutPostRedisplay();
            break;
        case 'n':
            middleMiddle = (middleMiddle + 5) % 90;
            if (middleMiddle > 80) middleMiddle = 80;
            glutPostRedisplay();
            break;
        case 'N':
            middleMiddle = (middleMiddle - 5) % 90;
            if (middleMiddle < 0) middleMiddle = 0;
            glutPostRedisplay();
            break;
        case 'b':
            middleTip = (middleTip + 5) % 90;
            if (middleTip > 80) middleTip = 80;
            glutPostRedisplay();
            break;
        case 'B':
            middleTip = (middleTip - 5) % 90;
            if (middleTip < 0) middleTip = 0;
            glutPostRedisplay();
            break;
            
        // Ring finger controls
        case 'r':
            ringBase = (ringBase + 5) % 90;
            if (ringBase > 80) ringBase = 80;
            glutPostRedisplay();
            break;
        case 'R':
            ringBase = (ringBase - 5) % 90;
            if (ringBase < 0) ringBase = 0;
            glutPostRedisplay();
            break;
        case 'f':
            ringMiddle = (ringMiddle + 5) % 90;
            if (ringMiddle > 80) ringMiddle = 80;
            glutPostRedisplay();
            break;
        case 'F':
            ringMiddle = (ringMiddle - 5) % 90;
            if (ringMiddle < 0) ringMiddle = 0;
            glutPostRedisplay();
            break;
        case 'v':
            ringTip = (ringTip + 5) % 90;
            if (ringTip > 80) ringTip = 80;
            glutPostRedisplay();
            break;
        case 'V':
            ringTip = (ringTip - 5) % 90;
            if (ringTip < 0) ringTip = 0;
            glutPostRedisplay();
            break;
            
        // Pinky finger controls
        case 'p':
            pinkyBase = (pinkyBase + 5) % 90;
            if (pinkyBase > 80) pinkyBase = 80;
            glutPostRedisplay();
            break;
        case 'P':
            pinkyBase = (pinkyBase - 5) % 90;
            if (pinkyBase < 0) pinkyBase = 0;
            glutPostRedisplay();
            break;
        case 'o':
            pinkyMiddle = (pinkyMiddle + 5) % 90;
            if (pinkyMiddle > 80) pinkyMiddle = 80;
            glutPostRedisplay();
            break;
        case 'O':
            pinkyMiddle = (pinkyMiddle - 5) % 90;
            if (pinkyMiddle < 0) pinkyMiddle = 0;
            glutPostRedisplay();
            break;
        case 'l':
            pinkyTip = (pinkyTip + 5) % 90;
            if (pinkyTip > 80) pinkyTip = 80;
            glutPostRedisplay();
            break;
        case 'L':
            pinkyTip = (pinkyTip - 5) % 90;
            if (pinkyTip < 0) pinkyTip = 0;
            glutPostRedisplay();
            break;
            
        case 27:  // ESC key
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lengan Bergerak");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
