#include <GL/glut.h>
#include <math.h>

// Konstanta Warna (sama seperti sebelumnya)
const GLfloat GRASS_GREEN[] = {0.0, 0.6, 0.0};
const GLfloat ASPHALT_GRAY[] = {0.4, 0.4, 0.4};
const GLfloat WHITE[] = {1.0, 1.0, 1.0};
const GLfloat BLACK[] = {0.0, 0.0, 0.0};
const GLfloat YELLOW[] = {1.0, 1.0, 0.0};
const GLfloat MOUNTAIN_GRAY[] = {0.6, 0.6, 0.6};
const GLfloat CAR_RED[] = {1.0, 0.0, 0.0};
const GLfloat GLASS_GRAY[] = {0.43, 0.43, 0.43};

// Variabel global untuk posisi mobil
GLfloat carX = 40; // Posisi awal mobil (koordinat X)
GLfloat carSpeed = 0.5; // Kecepatan mobil

// Fungsi untuk menggambar lingkaran (sama seperti sebelumnya)
void circle(GLfloat r, GLfloat cx, GLfloat cy, int num_segments, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Fungsi untuk menggambar velg (sama seperti sebelumnya)
void drawRim(GLfloat x, GLfloat y, GLfloat innerRadius, GLfloat outerRadius, int numSpokes, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);

    circle(innerRadius, x, y, 30, red, green, blue);

    for (int i = 0; i < numSpokes; i++) {
        float angle = i * 2.0f * M_PI / numSpokes;
        float spokeX = outerRadius * cosf(angle);
        float spokeY = outerRadius * sinf(angle);
        glColor3f(red*0.7, green*0.7, blue*0.7);
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + spokeX, y + spokeY);
        glEnd();
    }
}

// Fungsi untuk menggambar roda (sama seperti sebelumnya)
void drawWheel(GLfloat cx, GLfloat cy, GLfloat wheelRadius, GLfloat rimInnerRadius, GLfloat rimOuterRadius, int numSpokes, GLfloat wheelRed, GLfloat wheelGreen, GLfloat wheelBlue, GLfloat rimRed, GLfloat rimGreen, GLfloat rimBlue) {
    circle(wheelRadius, cx, cy, 30, wheelRed, wheelGreen, wheelBlue);
    drawRim(cx, cy, rimInnerRadius, rimOuterRadius, numSpokes, rimRed, rimGreen, rimBlue);
}

// Fungsi untuk menggambar persegi panjang (sama seperti sebelumnya)
void drawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

// Fungsi untuk menggambar segitiga (sama seperti sebelumnya)
void drawTriangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

// Fungsi inisialisasi (sama seperti sebelumnya)
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
}

// Fungsi keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Tombol 'a' untuk bergerak ke kiri
            carX -= carSpeed;
            if (carX < 0) carX = 0; // Batasi agar tidak keluar dari layar
            break;
        case 'd': // Tombol 'd' untuk bergerak ke kanan
            carX += carSpeed;
            if (carX > 360) carX = 360; // Batasi agar tidak keluar dari layar
            break;
        case 'w': // Tombol 'w' untuk mempercepat
        	carSpeed += 0.1;
            break;
        case 's': // Tombol 's' untuk memperlambat
            carSpeed -= 0.1;
            if (carSpeed < 0.1) carSpeed = 0.1; // Memastikan agar tidak jadi negatif
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Memaksa jendela untuk digambar ulang
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Rerumputan (sama seperti sebelumnya)
    drawRectangle(0, 0, 400, 100, GRASS_GREEN[0], GRASS_GREEN[1], GRASS_GREEN[2]);

    // Jalan aspal (sama seperti sebelumnya)
    drawRectangle(0, 50, 400, 100, ASPHALT_GRAY[0], ASPHALT_GRAY[1], ASPHALT_GRAY[2]);

    // Gunung (sama seperti sebelumnya)
    drawTriangle(50, 150, 150, 300, 250, 150, MOUNTAIN_GRAY[0], MOUNTAIN_GRAY[1], MOUNTAIN_GRAY[2]);
    drawTriangle(200, 150, 300, 350, 400, 150, MOUNTAIN_GRAY[0], MOUNTAIN_GRAY[1], MOUNTAIN_GRAY[2]);

    // Matahari (sama seperti sebelumnya)
    circle(30, 350, 350, 30, YELLOW[0], YELLOW[1], YELLOW[2]);

    // Garis aspal (sama seperti sebelumnya)
    for (int i = 0; i < 9; i++) {
        drawRectangle(i * 50, 100, 30, 10, WHITE[0], WHITE[1], WHITE[2]);
    }

    // Mobil (dimodifikasi)
    glColor3f(CAR_RED[0], CAR_RED[1], CAR_RED[2]);
    glBegin(GL_POLYGON);
    glVertex2d(carX, 120);
    glVertex2d(carX + 328, 120);
    glVertex2d(carX + 330, 180);
    glVertex2d(carX + 270, 200);
    glVertex2d(carX + 230, 240);
    glVertex2d(carX + 110, 240);
    glVertex2d(carX + 70, 200);
    glVertex2d(carX, 180);
    glEnd();

    // Lampu Depan (dimodifikasi)
    glColor3f(YELLOW[0], YELLOW[1], YELLOW[2]);
    glBegin(GL_POLYGON);
    glVertex2d(carX + 2, 168);
    glVertex2d(carX - 2, 168);
    glVertex2d(carX - 2, 146);
    glVertex2d(carX + 2, 146);
    glVertex2d(carX + 2, 168);
    glEnd();

    // Kaca (dimodifikasi)
    glColor3f(GLASS_GRAY[0], GLASS_GRAY[1], GLASS_GRAY[2]);
    glBegin(GL_POLYGON);
    glVertex2d(carX + 70, 200);
    glVertex2d(carX + 110, 200);
    glVertex2d(carX + 110, 240);
    glVertex2d(carX + 70, 200);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(carX + 118, 200);
    glVertex2d(carX + 170, 200);
    glVertex2d(carX + 170, 240);
    glVertex2d(carX + 120, 240);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(carX + 180, 200);
    glVertex2d(carX + 220, 200);
    glVertex2d(carX + 220, 240);
    glVertex2d(carX + 180, 240);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(carX + 230, 240);
    glVertex2d(carX + 230, 200);
    glVertex2d(carX + 270, 200);
    glVertex2d(carX + 230, 240);
    glEnd();

    // Roda dan velg (dimodifikasi)
    float wheel_radius = 30;
    float rim_inner_radius = 10;
    float rim_outer_radius = 25;
    int num_spokes = 5;

    drawWheel(carX + 80, 120, wheel_radius, rim_inner_radius, rim_outer_radius, num_spokes, BLACK[0], BLACK[1], BLACK[2], GLASS_GRAY[0], GLASS_GRAY[1], GLASS_GRAY[2]); // Roda kiri
    drawWheel(carX + 250, 120, wheel_radius, rim_inner_radius, rim_outer_radius, num_spokes, BLACK[0], BLACK[1], BLACK[2], GLASS_GRAY[0], GLASS_GRAY[1], GLASS_GRAY[2]); // Roda kanan

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Daftarkan fungsi keyboard

    glutMainLoop();
    return 0;
}
