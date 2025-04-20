#include <bits/stdc++.h>
#include <GL/glut.h>
#include <stdio.h>
#include <chrono>
#include "input.h"
#include "camera.h"
#include "render.h"
#include "lighting.h"
#include "menu.h"
#include "collision.h"
#include "object.h"
  
Player* pl = &player; // Pointer to player object

// Global Variables (Avoid these if possible, but some are necessary for GLUT)
int windowWidth = 640;
int windowHeight = 480;
bool inMenu = true;  

void display() {
    static auto lastFrameTime = std::chrono::steady_clock::now(); // Waktu frame sebelumnya
    auto currentFrameTime = std::chrono::steady_clock::now();     // Waktu frame saat ini
    float deltaTime = std::chrono::duration<float>(currentFrameTime - lastFrameTime).count(); // Hitung deltaTime
    lastFrameTime = currentFrameTime; // Perbarui waktu frame sebelumnya

    if (inMenu) {
        drawMenu(windowWidth, windowHeight); // Pass width and height
    } else {
        // Atur warna latar belakang (langit) menjadi biru muda
        glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Contoh: Warna biru langit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processKeys(*pl); // Gunakan input.cpp untuk memproses input
        updateCamera(*pl); // Perbarui posisi kamera berdasarkan player
        renderScene();     // Gambar scene

        // Tampilkan informasi di layar
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, windowWidth, 0, windowHeight);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // Set warna teks
        glColor3f(1.0f, 1.0f, 1.0f);

        // Tampilkan informasi rotasi dan posisi
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "Rotation Y: %.2f", pl->rotationY);
        drawText(buffer, 10, windowHeight - 20);

        snprintf(buffer, sizeof(buffer), "Position X: %.2f", pl->position.x);
        drawText(buffer, 10, windowHeight - 40);

        snprintf(buffer, sizeof(buffer), "Position Y: %.2f", pl->position.y);
        drawText(buffer, 10, windowHeight - 60);

        snprintf(buffer, sizeof(buffer), "Position Z: %.2f", pl->position.z);
        drawText(buffer, 10, windowHeight - 80);

        snprintf(buffer, sizeof(buffer), "playerRotationY: %.2f", player.rotationY);
        drawText(buffer, 10, windowHeight - 100);

        snprintf(buffer, sizeof(buffer), "cameraRotationY: %.2f", cameraRotationY);
        drawText(buffer, 10, windowHeight - 120);

        // Tampilkan FPS
        float fps = calculateFPS();
        snprintf(buffer, sizeof(buffer), "FPS: %.2f", fps);
        drawText(buffer, 10, windowHeight - 140);

        snprintf(buffer, sizeof(buffer), "Speed: %.2f", speed);
        drawText(buffer, 10, windowHeight - 160);

        // Kembalikan proyeksi dan modelview ke pengaturan semula
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glutSwapBuffers();
    }
}

void Reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    cameraReshape(w, h);  // Call camera.cpp's reshape function
}


void init()
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    loadTexture(); // Load grass, wall, and roof textures

    player = createPlayer("Player", 0.0f, 0.0f, 0.0f);

    
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Exploring Game");
    glutSetCursor(GLUT_CURSOR_NONE);

    glutFullScreen(); // Add full screen

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);

    // Daftarkan fungsi mouse
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutPassiveMotionFunc(mousePassiveMove);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp); // Add keyboard up function
    initLighting();
    init();

    // Initialize mouse position and last move time
    cameraCenterMouse(windowWidth, windowHeight);

    glutMainLoop();
    return 0;
}
 
