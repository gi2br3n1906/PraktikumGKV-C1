#include <GL/glut.h>
#include "input.h"
#include "camera.h" // Include for camera-related actions
#include "collision.h" // Include for checkCollision
#include "render.h"
#include "menu.h"
#include <cmath>
#include <windows.h>
 
#include <iostream>
 
const int MAX_KEYS = 256;
bool keys[MAX_KEYS];
bool isDragging = false;
bool isShiftPressed = false; // Variabel untuk menandai apakah tombol Shift ditekan
const float moveSpeed = 0.02f; // Kecepatan gerakan

bool isJumping = false;
float jumpHeight = 0.0f;
float jumpVelocity = 0.15f;    // Kecepatan awal lompatan
float gravity = 0.002f;        // Gravitasi
float speed;
 
void keyboard(unsigned char key, int x2, int y2) {
    keys[key] = true;
    extern bool inMenu;
    extern int windowWidth, windowHeight;

    if (key == 27) { // Escape key
        exit(0); 
    } 
}

void keyboardUp(unsigned char key, int x2, int y2) {
    keys[key] = false;

    // Pastikan animasi berhenti jika semua tombol gerakan dilepas
    if (!(keys['w'] || keys['W'] || keys['s'] || keys['S'] || keys['a'] || keys['A'] || keys['d'] || keys['D'])) {
        extern Player* pl;
        updatePlayerAnimation(*pl, 0.0f, false);
    }
}

void mouseButton(int button, int state, int x, int y) {
    extern bool inMenu;
    extern int windowWidth, windowHeight;

    if (inMenu) {
        handleMenuClick(button, state, x, y, windowWidth, windowHeight);
    } else {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            extern Player* pl;
            if (!pl->isPunching) {
                pl->isPunching = true; // Mulai animasi memukul
                pl->punchProgress = 0.0f;
            }
        }
    }
}

void processKeys(Player& player) {
    static auto lastFrameTime = std::chrono::steady_clock::now();
    auto currentFrameTime = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration<float>(currentFrameTime - lastFrameTime).count();
    lastFrameTime = currentFrameTime;

    const float rotationOffset = 90.0f; // Rotasi tambahan untuk A dan D

    // Reset arah gerak
    movementDirectionX = 0.0f;
    movementDirectionZ = 0.0f;

    bool isMoving = keys['w'] || keys['W'] || keys['a'] || keys['A'] || keys['s'] || keys['S'] || keys['d'] || keys['D'];
    isShiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    speed = (isMoving && isShiftPressed) ? moveSpeed * 7.0f : moveSpeed;
    float currentSpeed = speed; // Kecepatan saat ini berdasarkan deltaTime

    // Hanya proses gerakan jika ada tombol yang ditekan
    if (isMoving) {
        if (keys['w'] || keys['W']) {
            movementDirectionX += sin(cameraRotationY * M_PI / 180.0f);
            movementDirectionZ += cos(cameraRotationY * M_PI / 180.0f);
            player.rotationY = cameraRotationY;
        }
        if (keys['s'] || keys['S']) {
            movementDirectionX -= sin(cameraRotationY * M_PI / 180.0f);
            movementDirectionZ -= cos(cameraRotationY * M_PI / 180.0f);
            player.rotationY = cameraRotationY + 180.0f;
        }
        if (keys['a'] || keys['A']) {
            float rad = (cameraRotationY + rotationOffset) * M_PI / 180.0f;
            movementDirectionX += sin(rad);
            movementDirectionZ += cos(rad);
            player.rotationY = cameraRotationY - 90.0f;
        }
        if (keys['d'] || keys['D']) {
            float rad = (cameraRotationY - rotationOffset) * M_PI / 180.0f;
            movementDirectionX += sin(rad);
            movementDirectionZ += cos(rad);
            player.rotationY = cameraRotationY + 90.0f;
        }

        // Normalisasi arah gerak
        float length = sqrt(movementDirectionX * movementDirectionX + 
                          movementDirectionZ * movementDirectionZ);
        if (length > 0.0f) {
            movementDirectionX /= length;
            movementDirectionZ /= length;
            // Update posisi hanya jika ada gerakan
            player.position.x += movementDirectionX * currentSpeed;
            player.position.z += movementDirectionZ * currentSpeed;
        }
    }
    // Update animasi berdasarkan status gerakan
    updatePlayerAnimation(player, deltaTime, isMoving);

    // Proses lompatan seperti sebelumnya
    if (keys[' '] && !isJumping) {
        isJumping = true;
        jumpHeight = jumpVelocity;
    }

    if (isJumping) {
        player.position.y += jumpHeight;
        jumpHeight -= gravity;
        if (player.position.y <= 0.0f) {
            player.position.y = 0.0f;
            isJumping = false;
            jumpHeight = 0.0f;
        }
    }
}
