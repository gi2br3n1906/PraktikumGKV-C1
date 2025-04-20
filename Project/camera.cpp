#include "camera.h"
#include <iostream>
#include <math.h>
#include <chrono> 
#include "object.h" 
 
// Camera parameters 
float cameraAngle = 0.0f, cameraRatio;
float cameraX = 0.0f, cameraY = 1.75f, cameraZ = 15.0f;
float cameraLX = 0.0f, cameraLY = 0.0f, cameraLZ = -1.0f;
float cameraTargetAngle = 0.0f, cameraCurrentAngle = 0.0f;
float cameraTargetLy = 0.0f, cameraCurrentLy = 0.0f;
float cameraSensitivity = 0.02f; // Coba nilai yang lebih kecil atau lebih besar;
int mouseX, mouseY; // Removed window width and height dependencies
float cameraRotationY = 0.0f;
float cameraRotationX = 0.0f;
 
// Jumping parameters
float jumpSpeed = 0.1f;
float initialJumpVelocity = 0.02f;
float currentJumpVelocity = 0.0f;
std::chrono::time_point<std::chrono::steady_clock> jumpStartTime;
const std::chrono::seconds jumpDuration(3); // 1 second jump duration

// Idle mouse variables
auto lastMoveTime = std::chrono::steady_clock::now();
const auto idleThreshold = std::chrono::milliseconds(1); // 500 ms

bool isDriving = false; // State apakah sedang menyetir mobil
Car* currentCar = nullptr; // Mobil yang sedang dikendarai
const float carDetectionRadius = 5.0f; // Radius deteksi mobil
extern bool inMenu;
extern int windowWidth, windowHeight;

float movementDirectionX = 0.0f; // Arah gerak di sumbu X
float movementDirectionZ = 0.0f; // Arah gerak di sumbu Z

void cameraReshape(int w, int h) {
    cameraRatio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, cameraRatio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + cameraLX, cameraY + cameraLY, cameraZ + cameraLZ, 0.0f, 1.0f, 0.0f);
}

void cameraCenterMouse(int w, int h) {
    glutSetWindow(glutGetWindow()); // Pastikan jendela GLUT aktif
    glutWarpPointer(w / 2, h / 2);
    mouseX = w / 2;
    mouseY = h / 2;
    lastMoveTime = std::chrono::steady_clock::now();
    std::cout << "Mouse centered at: " << mouseX << ", " << mouseY << std::endl;
}

void mouseMove(int x, int y) {
    extern int windowWidth, windowHeight;

    // Hitung pergerakan relatif mouse
    int dx = x - (windowWidth / 2);
    int dy = y - (windowHeight / 2);

    // Perbarui rotasi kamera
    cameraRotationY -= dx * cameraSensitivity;
    cameraRotationX -= dy * cameraSensitivity;

    // Batasi rotasi vertikal kamera agar tidak melewati batas
    if (cameraRotationX > 89.0f) cameraRotationX = 89.0f;
    if (cameraRotationX < -89.0f) cameraRotationX = -89.0f;

    // Pindahkan kursor kembali ke tengah jendela
    glutWarpPointer(windowWidth / 2, windowHeight / 2);
}

void mousePassiveMove(int x, int y) {
    mouseMove(x, y); // Gunakan logika yang sama dengan `mouseMove`
}
void orientMe(float ang) {
    cameraLX = sin(ang);
    cameraLZ = -cos(ang);
}

// Tambahkan variabel offset kamera
const float cameraDistance = 8.0f; // Jarak kamera ke player
const float cameraHeight = 4.3f;   // Tinggi kamera dari player
// Variabel untuk mengontrol rotasi kamera terhadap mobil
float cameraRotationAroundCar = 0.0f;

void movePlayerBasedOnCamera(Player& player, float forward, float right) {
    // Hitung arah kamera
    float radY = player.rotationY * M_PI / 180.0f;

    // Hitung vektor gerakan relatif terhadap rotasi player
    float moveX = forward * sin(radY) + right * cos(radY);
    float moveZ = forward * cos(radY) - right * sin(radY);

    // Perbarui posisi player
    player.position.x += moveX;
    player.position.z += moveZ;
}

void updateCameraForCar() {
    // Update rotasi kamera berdasarkan input mouse
    cameraRotationAroundCar += (mouseX - (windowWidth / 2)) * cameraSensitivity;
    glutWarpPointer(windowWidth / 2, windowHeight / 2); // Reset mouse ke tengah layar

    // Batasi rotasi kamera jika perlu
    cameraRotationAroundCar = fmod(cameraRotationAroundCar, 360.0f);

    // Konversi rotasi kamera dan rotasi mobil ke radian
    float carRad = currentCar->rotation * M_PI / 180.0f;
    float cameraRad = cameraRotationAroundCar * M_PI / 180.0f;

    // Hitung posisi kamera relatif terhadap mobil
    cameraX = currentCar->position.x - (cameraDistance * sin(carRad + cameraRad));
    cameraY = currentCar->position.y + cameraHeight;
    cameraZ = currentCar->position.z - (cameraDistance * cos(carRad + cameraRad));

    // Arahkan kamera ke mobil
    cameraLX = currentCar->position.x - cameraX;
    cameraLY = currentCar->position.y - cameraY;
    cameraLZ = currentCar->position.z - cameraZ;

    // Normalisasi vektor arah kamera
    float length = sqrt(cameraLX * cameraLX + cameraLY * cameraLY + cameraLZ * cameraLZ);
    cameraLX /= length;
    cameraLY /= length;
    cameraLZ /= length;

    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,
              currentCar->position.x, currentCar->position.y + 1.0f, currentCar->position.z,
              0.0f, 1.0f, 0.0f);
}

void updateCameraForPlayer(const Player& player) {
    // Hitung arah kamera berdasarkan rotasi kamera
    float radY = cameraRotationY * M_PI / 180.0f;
    float radX = cameraRotationX * M_PI / 180.0f;

    // Hitung posisi kamera relatif terhadap player
    cameraX = player.position.x - sin(radY) * 7.0f * cos(radX);
    cameraY = player.position.y + 3.3f + sin(radX) * 7.0f;
    cameraZ = player.position.z - cos(radY) * 7.0f * cos(radX);

    // Arahkan kamera ke player
    cameraLX = player.position.x - cameraX;
    cameraLY = player.position.y - cameraY;
    cameraLZ = player.position.z - cameraZ;

    // Normalisasi vektor arah kamera
    float length = sqrt(cameraLX * cameraLX + cameraLY * cameraLY + cameraLZ * cameraLZ);
    cameraLX /= length;
    cameraLY /= length;
    cameraLZ /= length;

    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,
              player.position.x, player.position.y + 1.0f, player.position.z,
              0.0f, 1.0f, 0.0f);
}



void updateCamera(const Player& player) {
    if (isDriving && currentCar) {
        updateCameraForCar(); // Kamera mengikuti mobil
    } else {
        updateCameraForPlayer(player); // Kamera mengikuti player
    }
}
