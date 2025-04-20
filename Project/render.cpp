#include <GL/glut.h>
#include <cstdlib>
#include <iostream> 
#include <cmath>
#include <chrono>
#include <algorithm>
#include <GL/glext.h>
#include "collision.h"
#include "object.h"
#include "render.h"

#define checkImageWidth 64
#define checkImageHeight 64

GLubyte checkImage[checkImageWidth][checkImageHeight][3];
GLubyte wallImage[checkImageWidth][checkImageHeight][3];
GLubyte roofImage[checkImageWidth][checkImageHeight][3];
 
// textures 
GLuint texture[3];
 // Player object from object.h    
Player* pla = &player;
GLuint woodTexture;
GLuint grassTexture;
 
GLuint loadBMP(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        std::cerr << "Failed to load BMP file: " << filename << std::endl;
        return 0;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file); // Baca header BMP

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = 3 * width * height;

    unsigned char* data = new unsigned char[imageSize];
    fread(data, sizeof(unsigned char), imageSize, file); // Baca data piksel
    fclose(file);

    // Balikkan data vertikal karena BMP disimpan terbalik
    for (int i = 0; i < height / 2; i++) {
        for (int j = 0; j < width * 3; j++) {
            std::swap(data[i * width * 3 + j], data[(height - i - 1) * width * 3 + j]);
        }
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    delete[] data;
    return textureID;
}

void updatePlayerAnimation(Player& player, float deltaTime, bool isMoving) {
    static float animationTime = 0.0f;

    if (isMoving) {
        animationTime += deltaTime;

        // Animasi lengan dan kaki (ayunan)
        player.leftArmRotation = sin(animationTime * 5.0f) * 30.0f;  // Ayunan lengan kiri
        player.rightArmRotation = -sin(animationTime * 5.0f) * 30.0f; // Ayunan lengan kanan
        player.leftLegRotation = -sin(animationTime * 5.0f) * 30.0f;  // Ayunan kaki kiri
        player.rightLegRotation = sin(animationTime * 5.0f) * 30.0f;  // Ayunan kaki kanan
    } else {
        // Reset rotasi jika karakter diam
        player.leftArmRotation = 0.0f;
        player.rightArmRotation = 0.0f;
        player.leftLegRotation = 0.0f;
        player.rightLegRotation = 0.0f;
    }
}

void updatePunchAnimation(Player& player, float deltaTime) {
    if (player.isPunching) {
        player.punchProgress += deltaTime * 4.0f; // Kecepatan animasi memukul
        if (player.punchProgress >= 1.0f) {
            player.punchProgress = 0.0f;
            player.isPunching = false; // Selesai memukul
        }
    }
}

void drawText(const char* text, int x, int y, void* font) {
    glRasterPos2i(x, y); 
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c); 
    }
}

float calculateFPS() {
    static int frameCount = 0;
    static float fps = 0.0f;
    static auto lastTime = std::chrono::steady_clock::now();

    frameCount++;
    auto currentTime = std::chrono::steady_clock::now();
    float elapsedTime = std::chrono::duration<float>(currentTime - lastTime).count();

    if (elapsedTime > 1.0f) {
        fps = frameCount / elapsedTime;
        frameCount = 0;
        lastTime = currentTime;
    }

    return fps;
}

void makeCheckImage(void) 
{
    int i, j;

    for (i = 0; i < checkImageWidth; i++)
    {
        for (j = 0; j < checkImageHeight; j++)
        {
            checkImage[i][j][0] = (GLubyte)0;   // Red
            checkImage[i][j][1] = (GLubyte)255; // Green
            checkImage[i][j][2] = (GLubyte)0;   // Blue
        }
    }
}

void makeWallImage(void)
{
    int i, j;
    for (i = 0; i < checkImageWidth; i++)
    {
        for (j = 0; j < checkImageHeight; j++)
        {
            // Example: Brownish color for wood
            wallImage[i][j][0] = (GLubyte)139; // Red
            wallImage[i][j][1] = (GLubyte)69;  // Green
            wallImage[i][j][2] = (GLubyte)19;  // Blue
        }
    }
}

void makeRoofImage(void)
{
    int i, j;
    for (i = 0; i < checkImageWidth; i++)
    {
        for (j = 0; j < checkImageHeight; j++)
        {
            // Example: Dark red for roof tiles
            roofImage[i][j][0] = (GLubyte)178; // Red
            roofImage[i][j][1] = (GLubyte)34;  // Green
            roofImage[i][j][2] = (GLubyte)34;  // Blue
        }
    }
}

void loadTexture(void) {
    makeCheckImage();
    makeWallImage();
    makeRoofImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(3, texture);

    // Wall texture
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, checkImageWidth, checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, wallImage);

    // Roof texture
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, checkImageWidth, checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, roofImage);

    // Load wood texture
    woodTexture = loadBMP("stone.bmp"); // Ganti "wood.bmp" dengan path file BMP kayu
    grassTexture = loadBMP("grass.bmp"); 
}

void Grid() {
    double i;
    const float Z_MIN = -500, Z_MAX = 500;
    const float X_MIN = -500, X_MAX = 500;
    const float gap = 1.5;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grassTexture);

    glColor3f(1.0, 1.0, 1.0); // Warna putih agar tekstur terlihat jelas
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f); // Normal menghadap ke atas

    float repeatX = 3000.0f; // Ulangi tekstur 10 kali di sumbu X
    float repeatY = 3000.0f; // Ulangi tekstur 10 kali di sumbu Y

    // Ulangi tekstur 50 kali di setiap sumbu
    glTexCoord2f(0.0f, 0.0f); glVertex3f(X_MIN, 0, Z_MIN);
    glTexCoord2f(repeatX, 0.0f); glVertex3f(X_MAX, 0, Z_MIN);
    glTexCoord2f(repeatX, repeatY); glVertex3f(X_MAX, 0, Z_MAX);
    glTexCoord2f(0.0f, repeatY); glVertex3f(X_MIN, 0, Z_MAX);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void KotakKayu()
{
    // Depan
    glPushMatrix();
    glTranslatef(0, 0, 3);
    drawWall(-3.0f, -0.0f, -1.0f, 3.0f, 0.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 3);
    drawWall(1.0f, 0.0f, 3.0f, 3.0f, 0.0f, 1.0f);
    glPopMatrix();

    // Belakang
    glPushMatrix();
    glRotated(-180, 0, 1, 0);
    glTranslatef(0, 0, 3);
    drawWall(-3.0f, -1.0f, 3.0f, 3.0f, 0.0f, 1.0f);
    glPopMatrix();

    // Kiri
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(0, 0, 3);
    drawWall(-3.0f, 0.0f, -1.0f, 3.0f, 0.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(0, 0, 3);
    drawWall(1.0f, 0.0f, 3.0f, 3.0f, 0.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(0, 0, 3);
    drawWall(-3.0f, 0.0f, 3.0f, 2.0f, 0.0f, 1.0f);
    glPopMatrix();

    // Kanan
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(0, 0, 3);
    drawWall(-3.0f, 0.0f, 3.0f, 3.0f, 0.0f, 1.0f);
    glPopMatrix();

    // Atap
    glPushMatrix();
    glTranslatef(0, 3.25, 0);
    glScalef(3.5, 0.25, 3.5); // Scale to create a box-like roof
    glColor3f(0.8f, 0.8f, 0.8f);
    glutSolidCube(2.0f); // Draw a cube as the roof
    glPopMatrix();
    
    // Atap
    glPushMatrix();
    glTranslatef(2, 4, 2);
    glScalef(1, 0.75, 1); // Scale to create a box-like roof
    glColor3f(0.8f, 0.8f, 0.8f);
    glutSolidCube(2.0f); // Draw a cube as the roof
    glPopMatrix();
}

void displayBoundingBoxesOnScreen() {
    // Simpan matriks tampilan saat ini
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Atur ke mode orthographic projection untuk menggambar UI
    gluOrtho2D(0, 800, 0, 600); // Sesuaikan dengan resolusi layar Anda

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Tampilkan bounding boxes sebagai teks di layar
    int yOffset = 20; // Jarak vertikal antar teks
    int startX = 10;  // Posisi X awal untuk teks
    int startY = 580; // Posisi Y awal untuk teks (dari atas layar)

    for (size_t i = 0; i < boundingBoxes.size(); ++i) {
        const auto& box = boundingBoxes[i];
        char text[200];
        snprintf(text, sizeof(text), 
                 "Box %zu: Min(%.2f, %.2f, %.2f), Max(%.2f, %.2f, %.2f)", 
                 i + 1, box.minX, box.minY, box.minZ, box.maxX, box.maxY, box.maxZ);
        drawText(text, startX, startY - (yOffset * i), GLUT_BITMAP_HELVETICA_18);
    }

    // Kembalikan matriks tampilan ke mode semula
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

std::vector<Car> cars = {
    createCar("Car1", 10.0f, 0.0f, 10.0f, 0.1f, 0.0f),
    createCar("Car2", -10.0f, 0.0f, -10.0f, 0.1f, 0.0f)
};

void renderScene() {
    Grid();

    // Gambar pohon
    drawTree(9.0f, 12.0f);
    drawTree(-9.0f, 12.0f);
    drawTree(9.0f, -12.0f);
    drawTree(-9.0f, -12.0f);
    
    
    // Gambar mobil
    for (auto& car : cars) {
        car.draw(car);
    }

    // Gambar player jika tidak sedang menyetir
    extern bool isDriving;
    if (!isDriving) {
        glPushMatrix();
        glTranslatef(player.position.x, player.position.y, player.position.z);
        glRotatef(player.rotationY, 0.0f, 1.0f, 0.0f);
        player.draw(player);
        glPopMatrix();
    }
	
	KotakKayu();

    
}


 
