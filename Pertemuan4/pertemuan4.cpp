#include <GL/glut.h>
#include <chrono>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>

#define checkImageWidth 64
#define checkImageHeight 64

GLubyte checkImage[checkImageWidth][checkImageHeight][3];
GLuint texture[1];

const int MAX_KEYS = 256;
bool keys[MAX_KEYS];
bool inMenu = true;

// Camera parameters
float angle = 0.0f, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float targetAngle = 0.0f, currentAngle = 0.0f;
float targetLy = 0.0f, currentLy = 0.0f;
float cameraSensitivity = 0.01f;
int h, w, mouseX, mouseY;

// Jumping parameters
bool isJumping = false;
float jumpSpeed = 0.1f;
float gravity = 0.0001f;
float initialJumpVelocity = 0.02f;
float currentJumpVelocity = 0.0f;

// Idle detection
auto lastMoveTime = std::chrono::steady_clock::now();
const auto idleThreshold = std::chrono::seconds(1);

// Lighting parameters
const GLfloat light_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
const GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat light_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat light_position[] = {0.0f, 20.0f, 10.0f, 0.0f};
const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

// Car parameters
float carX = 0.0f;
float carZ = 0.0f;
float carLength = 8.0f;
float carWidth = 4.0f;

void centerMouse() {
    glutWarpPointer(w / 2, h / 2);
    mouseX = w / 2;
    mouseY = h / 2;
    lastMoveTime = std::chrono::steady_clock::now();
}

void mouseMove(int x1, int y1) {
    if (!inMenu) {
        int dx = x1 - mouseX;
        int dy = y1 - mouseY;

        targetAngle += dx * cameraSensitivity;

        targetLy -= dy * cameraSensitivity;
        targetLy = std::max(-0.8f, std::min(targetLy, 0.8f));

        mouseX = x1;
        mouseY = y1;
        lastMoveTime = std::chrono::steady_clock::now();
    }
}

void Reshape(int w1, int h1) {
    w = w1;
    h = h1 > 0 ? h1 : 1;
    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
}

void keyboard(unsigned char key, int x2, int y2) {
    keys[key] = true;

    if (key == 27) exit(0);

    if (key == 32 && !isJumping) {
        isJumping = true;
        currentJumpVelocity = initialJumpVelocity;
    }

    if (inMenu && key == ' ') {
        inMenu = false;
        centerMouse();
    }
}

void keyboardUp(unsigned char key, int x2, int y2) { keys[key] = false; }

void processKeys() {
    if (!inMenu) {
        float speed = (keys[16]) ? 0.02f : 0.005f;
        float newX = x, newZ = z;

        if (keys['w']) {
            newX += lx * speed;
            newZ += lz * speed;
        }
        if (keys['s']) {
            newX -= lx * speed;
            newZ -= lz * speed;
        }
        if (keys['a']) {
            newX += lz * speed;
            newZ -= lx * speed;
        }
        if (keys['d']) {
            newX -= lz * speed;
            newZ += lx * speed;
        }

        x = newX;
        z = newZ;
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
    }
}

void Grid() {
    const float Z_MIN = -500, Z_MAX = 500;
    const float X_MIN = -500, X_MAX = 500;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(X_MIN, 0, Z_MIN);

    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(X_MAX, 0, Z_MIN);

    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(X_MAX, 0, Z_MAX);

    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(X_MIN, 0, Z_MAX);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawCar(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glScalef(4, 4, 4);

    glColor3f(0.8f, 0.2f, 0.0f);

    glBegin(GL_QUADS);
    // Front Body
    // Top
    glVertex3f(0.2f, 0.4f, 0.6f);
    glVertex3f(0.6f, 0.5f, 0.6f);
    glVertex3f(0.6f, 0.5f, 0.2f);
    glVertex3f(0.2f, 0.4f, 0.2f);

    // Bottom
    glVertex3f(0.2f, 0.2f, 0.6f);
    glVertex3f(0.6f, 0.2f, 0.6f);
    glVertex3f(0.6f, 0.2f, 0.2f);
    glVertex3f(0.2f, 0.2f, 0.2f);

    // Front
    glVertex3f(0.2f, 0.2f, 0.6f);
    glVertex3f(0.2f, 0.4f, 0.6f);
    glVertex3f(0.2f, 0.4f, 0.2f);
    glVertex3f(0.2f, 0.2f, 0.2f);

    // Back
    glVertex3f(0.6f, 0.2f, 0.6f);
    glVertex3f(0.6f, 0.5f, 0.6f);
    glVertex3f(0.6f, 0.5f, 0.2f);
    glVertex3f(0.6f, 0.2f, 0.2f);

    // Left
    glVertex3f(0.2f, 0.2f, 0.6f);
    glVertex3f(0.6f, 0.2f, 0.6f);
    glVertex3f(0.6f, 0.5f, 0.6f);
    glVertex3f(0.2f, 0.4f, 0.6f);

    // Right
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.6f, 0.2f, 0.2f);
    glVertex3f(0.6f, 0.5f, 0.2f);
    glVertex3f(0.2f, 0.4f, 0.2f);
    glEnd();

    // Middle Body Top Cover
    glBegin(GL_QUADS);
    glVertex3f(0.7f, 0.65f, 0.6f);
    glVertex3f(0.7f, 0.65f, 0.2f);
    glVertex3f(1.7f, 0.65f, 0.2f);
    glVertex3f(1.7f, 0.65f, 0.6f);
    glEnd();

    // Back Guard
    glColor3f(0.8f, 0.2f, 0.0f); // Match car body color
    glBegin(GL_QUADS);
    // Front
    glVertex3f(1.8f, 0.5f, 0.6f);
    glVertex3f(1.8f, 0.5f, 0.2f);
    glVertex3f(2.1f, 0.4f, 0.2f);
    glVertex3f(2.1f, 0.4f, 0.6f);

    // Bottom
    glVertex3f(2.1f, 0.2f, 0.6f);
    glVertex3f(2.1f, 0.2f, 0.2f);
    glVertex3f(1.8f, 0.2f, 0.2f);
    glVertex3f(1.8f, 0.2f, 0.6f);

    // Back
    glVertex3f(2.1f, 0.4f, 0.6f);
    glVertex3f(2.1f, 0.4f, 0.2f);
    glVertex3f(2.1f, 0.2f, 0.2f);
    glVertex3f(2.1f, 0.2f, 0.6f);

    // Left
    glVertex3f(1.8f, 0.2f, 0.2f);
    glVertex3f(1.8f, 0.5f, 0.2f);
    glVertex3f(2.1f, 0.4f, 0.2f);
    glVertex3f(2.1f, 0.2f, 0.2f);

    // Right
    glVertex3f(1.8f, 0.2f, 0.6f);
    glVertex3f(1.8f, 0.5f, 0.6f);
    glVertex3f(2.1f, 0.4f, 0.6f);
    glVertex3f(2.1f, 0.2f, 0.6f);
    glEnd();

    // Middle Body
    glBegin(GL_QUADS);
    // Front
    glVertex3f(0.6f, 0.5f, 0.6f);
    glVertex3f(0.6f, 0.2f, 0.6f);
    glVertex3f(1.8f, 0.2f, 0.6f);
    glVertex3f(1.8f, 0.5f, 0.6f);

    // Bottom
    glVertex3f(0.6f, 0.2f, 0.6f);
    glVertex3f(0.6f, 0.2f, 0.2f);
    glVertex3f(1.8f, 0.2f, 0.2f);
    glVertex3f(1.8f, 0.2f, 0.6f);

    // Back
    glVertex3f(0.6f, 0.5f, 0.2f);
    glVertex3f(0.6f, 0.2f, 0.2f);
    glVertex3f(1.8f, 0.2f, 0.2f);
    glVertex3f(1.8f, 0.5f, 0.2f);
    glEnd();

    // Windows
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    // Front Windows
    glVertex3f(0.77f, 0.63f, 0.2f);
    glVertex3f(0.75f, 0.5f, 0.2f);
    glVertex3f(1.2f, 0.5f, 0.2f);
    glVertex3f(1.22f, 0.63f, 0.2f);

    glVertex3f(1.27f, 0.63f, 0.2f);
    glVertex3f(1.25f, 0.5f, 0.2f);
    glVertex3f(1.65f, 0.5f, 0.2f);
    glVertex3f(1.67f, 0.63f, 0.2f);

    // Back Windows
    glVertex3f(0.77f, 0.63f, 0.6f);
    glVertex3f(0.75f, 0.5f, 0.6f);
    glVertex3f(1.2f, 0.5f, 0.6f);
    glVertex3f(1.22f, 0.63f, 0.6f);

    glVertex3f(1.27f, 0.63f, 0.6f);
    glVertex3f(1.25f, 0.5f, 0.6f);
    glVertex3f(1.65f, 0.5f, 0.6f);
    glVertex3f(1.67f, 0.63f, 0.6f);
    glEnd();

    // Window Separations
    glColor3f(0.8f, 0.2f, 0.0f); // Match car body color
    glBegin(GL_QUADS);
    // Vertical Separations
    glVertex3f(0.7f, 0.65f, 0.2f);
    glVertex3f(0.7f, 0.5f, 0.2f);
    glVertex3f(0.75f, 0.5f, 0.2f);
    glVertex3f(0.77f, 0.65f, 0.2f);

    glVertex3f(1.2f, 0.65f, 0.2f);
    glVertex3f(1.2f, 0.5f, 0.2f);
    glVertex3f(1.25f, 0.5f, 0.2f);
    glVertex3f(1.27f, 0.65f, 0.2f);

    glVertex3f(1.65f, 0.65f, 0.2f);
    glVertex3f(1.65f, 0.5f, 0.2f);
    glVertex3f(1.7f, 0.5f, 0.2f);
    glVertex3f(1.7f, 0.65f, 0.2f);

    // Horizontal Separations
    glVertex3f(0.75f, 0.65f, 0.2f);
    glVertex3f(0.75f, 0.63f, 0.2f);
    glVertex3f(1.7f, 0.63f, 0.2f);
    glVertex3f(1.7f, 0.65f, 0.2f);

    glVertex3f(0.75f, 0.65f, 0.6f);
    glVertex3f(0.75f, 0.63f, 0.6f);
    glVertex3f(1.7f, 0.63f, 0.6f);
    glVertex3f(1.7f, 0.65f, 0.6f);

    // Vertical Separations (Back Windows)
    glVertex3f(0.7f, 0.65f, 0.6f);
    glVertex3f(0.7f, 0.5f, 0.6f);
    glVertex3f(0.75f, 0.5f, 0.6f);
    glVertex3f(0.77f, 0.65f, 0.6f);

    glVertex3f(1.2f, 0.65f, 0.6f);
    glVertex3f(1.2f, 0.5f, 0.6f);
    glVertex3f(1.25f, 0.5f, 0.6f);
    glVertex3f(1.27f, 0.65f, 0.6f);

    glVertex3f(1.65f, 0.65f, 0.6f);
    glVertex3f(1.65f, 0.5f, 0.6f);
    glVertex3f(1.7f, 0.5f, 0.6f);
    glVertex3f(1.7f, 0.65f, 0.6f);
    glEnd();

    // Top of Middle Body Sides
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(0.6f, 0.5f, 0.6f);
    glVertex3f(0.6f, 0.5f, 0.2f);
    glVertex3f(0.7f, 0.65f, 0.2f);
    glVertex3f(0.7f, 0.65f, 0.6f);

    glVertex3f(1.7f, 0.65f, 0.6f);
    glVertex3f(1.7f, 0.65f, 0.2f);
    glVertex3f(1.8f, 0.5f, 0.2f);
    glVertex3f(1.8f, 0.5f, 0.6f);
    glEnd();

    // Triangles on Top of Windows
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.6f, 0.5f, 0.6f);
    glVertex3f(0.7f, 0.65f, 0.6f);
    glVertex3f(0.7f, 0.5f, 0.6f);

    glVertex3f(0.6f, 0.5f, 0.2f);
    glVertex3f(0.7f, 0.65f, 0.2f);
    glVertex3f(0.7f, 0.5f, 0.2f);

    glVertex3f(1.7f, 0.65f, 0.2f);
    glVertex3f(1.8f, 0.5f, 0.2f);
    glVertex3f(1.7f, 0.5f, 0.2f);

    glVertex3f(1.7f, 0.65f, 0.6f);
    glVertex3f(1.8f, 0.5f, 0.6f);
    glVertex3f(1.7f, 0.5f, 0.6f);
    glEnd();

    // Ignition System
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.7f);
    glTranslatef(1.65f, 0.2f, 0.3f);
    glRotatef(90.0f, 0, 1, 0);
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.02, 0.03, 0.5, 10, 10);
    gluDeleteQuadric(quad);
    glPopMatrix();

    // Wheels
    glColor3f(0.2f, 0.2f, 0.2f);

    auto drawWheel = [&](float x, float z) {
        glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glTranslatef(x, 0.2f, z);
        glRotatef(angle, 0, 0, 1);
        glutSolidTorus(0.025, 0.07, 10, 25);
        glPopMatrix();

        glColor3f(0.9f, 0.9f, 0.9f);
        glPushMatrix();
        glTranslatef(x, 0.2f, z);
        glRotatef(angle, 0, 0, 1);
        glutSolidTorus(0.02, 0.05, 10, 25);
        glPopMatrix();

        for (int i = 0; i < 360; i += 45) {
            glPushMatrix();
            glColor3f(0.9f, 0.9f, 0.9f);
            glTranslatef(x, 0.2f, z);
            glRotatef(i, 0, 0, 1);
            glRotatef(90.0f, 0, 1, 0);
            gluCylinder(gluNewQuadric(), 0.005, 0.005, 0.06, 10, 10);
            glPopMatrix();
        }
    };

    drawWheel(0.6f, 0.62f);
    drawWheel(0.6f, 0.18f);
    drawWheel(1.7f, 0.18f);
    drawWheel(1.7f, 0.62f);

    glPopMatrix();
}

void drawMenu() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Title
    const char *title = "GAME KEREN BGT COY";
    int titleWidth = 0;
    for (const char *c = title; *c != '\0'; c++) {
        titleWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
    int titleX = (w - titleWidth) / 2;
    int titleY = h / 2 + 20;

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(titleX, titleY);
    for (const char *c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    // Instructions
    const char *instructions = "Press SPACE to start";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(w / 2 - 100, h / 2 - 20);
    for (const char *c = instructions; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glutSwapBuffers();
}

void display() {
    if (inMenu) {
        drawMenu();
    } else {
        glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processKeys();

        // Jumping logic
        if (isJumping) {
            y += currentJumpVelocity;
            currentJumpVelocity -= gravity;

            if (y <= 1.75f) {
                y = 1.75f;
                isJumping = false;
                currentJumpVelocity = initialJumpVelocity;
            }
        }

        // Smooth camera movement
        float smoothFactor = 0.1f;
        currentAngle += (targetAngle - currentAngle) * smoothFactor;
        currentLy += (targetLy - currentLy) * smoothFactor;

        orientMe(currentAngle);

        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + currentLy, z + lz, 0.0f, 1.0f, 0.0f);

        Grid();
        drawCar(carX, carZ);
        glutSwapBuffers();

        // Reset mouse if idle
        auto now = std::chrono::steady_clock::now();
        auto duration =
                std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                                                                                            lastMoveTime);
        if (duration > idleThreshold) {
            centerMouse();
        }
    }
}

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
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT_MODEL_LOCAL_VIEWER);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (int i = 0; i < MAX_KEYS; i++) {
        keys[i] = false;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("3D Lighting");
    glutSetCursor(GLUT_CURSOR_NONE);

    glutFullScreen();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    lighting();
    init();

    centerMouse();

    glutMainLoop();
    return (0);
}
