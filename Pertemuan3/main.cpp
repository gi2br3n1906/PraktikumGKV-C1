#include <GL/glut.h>
#include <map>

static int shoulder = 0, elbow = 0, wrist = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, thumb = 0;
static int upperArmRotationY = 0; 

std::map<unsigned char, bool> keyStates;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST); 
}

void drawCubeWithBorder(GLfloat r, GLfloat g, GLfloat b, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ) {

    glColor3f(r, g, b);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidCube(1.0);

    // Draw the border
    glLineWidth(2.0); 
    glColor3f(0.0, 0.0, 0.0); 
    glutWireCube(1.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glPushMatrix();

    // Rotasi lengan atas terhadap sumbu Y
    glRotatef((GLfloat)upperArmRotationY, 0.0, 1.0, 0.0);

    // Shoulder and upper arm
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    drawCubeWithBorder(1.0, 0.8, 0.6, 2.0, 0.4, 1.0); 
    glPopMatrix();

    // Elbow and lower arm
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    drawCubeWithBorder(1.0, 0.8, 0.6, 2.0, 0.4, 1.0); 
    glPopMatrix();

    // Wrist joint and palm
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    drawCubeWithBorder(1.0, 0.8, 0.6, 1.0, 0.4, 1.2); 
    glPopMatrix();

    // Finger 1 (index finger)
    glPushMatrix();
    glTranslatef(0.5, 0.2, 0.3);
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);

	    // First segment
	    glTranslatef(0.2, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.4, 0.2, 0.2); 
	    glPopMatrix();
	
	    // Second segment
	    glTranslatef(0.2, 0.0, 0.0);
	    glRotatef((GLfloat)finger1 / 2, 0.0, 0.0, 1.0);
	    glTranslatef(0.2, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.4, 0.2, 0.2); 
	    glPopMatrix();
	
	    // Third segment
	    glTranslatef(0.2, 0.0, 0.0);
	    glRotatef((GLfloat)finger1 / 2, 0.0, 0.0, 1.0);
	    glTranslatef(0.15, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.3, 0.2, 0.2); 
	    glPopMatrix();

    glPopMatrix();

    // Finger 2 (middle finger)
    glPushMatrix();
    glTranslatef(0.5, 0.2, 0.0);
    glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);

	    // First segment
	    glTranslatef(0.23, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.46, 0.2, 0.2); 
	    glPopMatrix();
	
	    // Second segment
	    glTranslatef(0.23, 0.0, 0.0);
	    glRotatef((GLfloat)finger2 / 2, 0.0, 0.0, 1.0);
	    glTranslatef(0.23, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.46, 0.2, 0.2);
	    glPopMatrix();
	
	    // Third segment
	    glTranslatef(0.23, 0.0, 0.0);
	    glRotatef((GLfloat)finger2 / 2, 0.0, 0.0, 1.0);
	    glTranslatef(0.17, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.34, 0.2, 0.2); 
	    glPopMatrix();

    glPopMatrix();

    // Finger 3 (ring finger)
    glPushMatrix();
    glTranslatef(0.5, 0.2, -0.3);
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);

	    // First segment
	    glTranslatef(0.2, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.4, 0.2, 0.2); 
	    glPopMatrix();
	
	    // Second segment
	    glTranslatef(0.2, 0.0, 0.0);
	    glRotatef((GLfloat)finger3 / 2, 0.0, 0.0, 1.0);
	    glTranslatef(0.2, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.4, 0.2, 0.2); 
	    glPopMatrix();
	
	    // Third segment
	    glTranslatef(0.2, 0.0, 0.0);
	    glRotatef((GLfloat)finger3 / 2, 0.0, 0.0, 1.0);
	    glTranslatef(0.15, 0.0, 0.0);
	    glPushMatrix();
	    drawCubeWithBorder(1.0, 0.8, 0.6, 0.3, 0.2, 0.2); 
	    glPopMatrix();

    glPopMatrix();

    // Finger 4 (pinky)
    glPushMatrix();
    glTranslatef(0.5, 0.2, -0.5);
    glRotatef((GLfloat)finger4, 0.0, 0.0, 1.0);

        // First segment
        glTranslatef(0.17, 0.0, 0.0);
        glPushMatrix();
        drawCubeWithBorder(1.0, 0.8, 0.6, 0.34, 0.15, 0.15); 
        glPopMatrix();

        // Second segment
        glTranslatef(0.17, 0.0, 0.0);
        glRotatef((GLfloat)finger4 / 2, 0.0, 0.0, 1.0);
        glTranslatef(0.17, 0.0, 0.0);
        glPushMatrix();
        drawCubeWithBorder(1.0, 0.8, 0.6, 0.34, 0.15, 0.15); 
        glPopMatrix();

        // Third segment
        glTranslatef(0.17, 0.0, 0.0);
        glRotatef((GLfloat)finger4 / 2, 0.0, 0.0, 1.0);
        glTranslatef(0.13, 0.0, 0.0);
        glPushMatrix();
        drawCubeWithBorder(1.0, 0.8, 0.6, 0.26, 0.15, 0.15); 
        glPopMatrix();

    glPopMatrix();

    // Thumb
    glPushMatrix();
    glTranslatef(0.3, -0.2, 0.5);
    glRotatef(-(GLfloat)thumb - 30, -1.0, 0.0, 1.0);

        // First segment
        glTranslatef(0.17, 0.0, 0.0);
        glPushMatrix();
        drawCubeWithBorder(1.0, 0.8, 0.6, 0.34, 0.2, 0.2); 
        glPopMatrix();

        // Second segment
        glTranslatef(0.17, 0.0, 0.0);
        glRotatef(-(GLfloat)thumb / 2, 1.0, 0.0, 1.0);
        glTranslatef(0.17, 0.0, 0.0);
        glPushMatrix();
        drawCubeWithBorder(1.0, 0.8, 0.6, 0.34, 0.2, 0.2); 
        glPopMatrix();

        // Third segment
        glTranslatef(0.17, 0.0, 0.0);
        glRotatef(-(GLfloat)thumb / 2, 1.0, 0.0, 1.0);
        glTranslatef(0.13, 0.0, 0.0);
        glPushMatrix();
        drawCubeWithBorder(1.0, 0.8, 0.6, 0.26, 0.2, 0.2); 
        glPopMatrix();

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

void update() {
    // Cek tombol yang ditekan dan ubah sudut rotasi
    if (keyStates['w']) shoulder = (shoulder + 5) % 360;
    if (keyStates['s']) shoulder = (shoulder - 5) % 360;

    if (keyStates['a']) elbow = (elbow + 5) % 360;
    if (keyStates['d']) elbow = (elbow - 5) % 360;

    if (keyStates['i']) wrist = (wrist + 5) % 360;
    if (keyStates['k']) wrist = (wrist - 5) % 360;

    if (keyStates['o']) thumb = (thumb + 5) % 100;
    if (keyStates['p']) thumb = (thumb - 5) % 100;

    if (keyStates['[']) finger1 = (finger1 + 5) % 100;
    if (keyStates[']']) finger1 = (finger1 - 5) % 100;

    if (keyStates['1']) finger2 = (finger2 + 5) % 100;
    if (keyStates['2']) finger2 = (finger2 - 5) % 100;

    if (keyStates['4']) finger3 = (finger3 + 5) % 100;
    if (keyStates['5']) finger3 = (finger3 - 5) % 100;

    if (keyStates['7']) finger4 = (finger4 + 5) % 100;
    if (keyStates['8']) finger4 = (finger4 - 5) % 100;

    // Rotasi lengan atas terhadap sumbu Y
    if (keyStates['t']) upperArmRotationY = (upperArmRotationY + 5) % 360;
    if (keyStates['g']) upperArmRotationY = (upperArmRotationY - 5) % 360;

    glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y) {
    keyStates[key] = true;
    if (key == 27) exit(0); // ESC
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void timer(int value) {
    update(); // update status tombol tiap frame
    glutTimerFunc(16, timer, 0); // panggil lagi dalam 16 ms (~60 FPS)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable depth buffer
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
