#include <GL/glut.h>
#include <iostream>
#include "menu.h"
#include "camera.h"

void drawBackground(int width, int height) { 
    // Gambar garis jalan
    glColor3f(1.0f, 1.0f, 1.0f); // Putih garis jalan
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < height / 2; i += 40) { // Naikkan posisi garis jalan
        glVertex2i(width / 2, i);
        glVertex2i(width / 2, i + 20);
    }
    glEnd(); 

    // Gambar jalan raya (dipersempit dan dinaikkan)
    glColor3f(0.2f, 0.2f, 0.2f); // Abu-abu jalan
    glBegin(GL_QUADS);
    glVertex2i(width / 2 - 50, 0);          // Naikkan posisi jalan
    glVertex2i(width / 2 + 50, 0);          // Naikkan posisi jalan
    glVertex2i(width / 2 + 50, height / 2);          // Naikkan posisi jalan
    glVertex2i(width / 2 - 50, height / 2);          // Naikkan posisi jalan
    glEnd();

    // Gambar sawah
    glColor3f(0.6f, 0.8f, 0.2f); // Hijau sawah
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(width, 0);
    glVertex2i(width, height / 2);
    glVertex2i(0, height / 2);
    glEnd();

    // Gambar gunung
    glColor3f(0.4f, 0.76f, 0.38f); // Hijau gunung
    glBegin(GL_TRIANGLES);
    glVertex2i(width / 4 - 200, height / 2);
    glVertex2i(width / 2 - 300, height / 2 + 400);
    glVertex2i(3 * width / 4 - 300, height / 2);
    glEnd();

    // Gambar gunung
    glColor3f(0.4f, 0.81f, 0.41f); // Hijau gunung
    glBegin(GL_TRIANGLES);
    glVertex2i(width / 4 + 300, height / 2);
    glVertex2i(width / 2 + 300, height / 2 + 500);
    glVertex2i(3 * width / 4 + 300, height / 2);
    glEnd();

    // Gambar langit
    glColor3f(0.529f, 0.808f, 0.922f); // Biru langit
    glBegin(GL_QUADS);
    glVertex2i(0, height / 2);
    glVertex2i(width, height / 2);
    glVertex2i(width, height);
    glVertex2i(0, height);
    glEnd();
}

void handleMenuClick(int button, int state, int x, int y, int windowWidth, int windowHeight) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Hitung posisi tombol
        int buttonWidth = 100;
        int buttonHeight = 40;
        int buttonX = windowWidth / 2 - buttonWidth / 2;
        int buttonY = windowHeight / 2 - buttonHeight / 2;

        // Konversi koordinat mouse (y terbalik karena OpenGL)
        int mouseX = x;
        int mouseY = windowHeight - y;

        // Periksa apakah klik berada di dalam tombol
        if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
            mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
            extern bool inMenu;
            inMenu = false; // Keluar dari menu
            cameraCenterMouse(windowWidth, windowHeight);
            glutSetCursor(GLUT_CURSOR_NONE); // Sembunyikan kursor saat permainan dimulai
            std::cout << "Start button clicked. Exiting menu and entering game..." << std::endl;
        }
    }
}

void drawMenu(int width, int height) {
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    // Set warna latar belakang menu
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Contoh: Warna biru langit;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set proyeksi orthographic agar teks tidak terpengaruh perspektif
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Tulis judul game
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(width / 2 - 140, height / 2 + 100);
    const char *title = "GAME KEREN BGT COY";
    for (const char *c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    // Gambar tombol "Start"
    int buttonWidth = 200;
    int buttonHeight = 80;
    int buttonX = width / 2 - buttonWidth / 2;
    int buttonY = height / 2 - buttonHeight / 2;

    // Tulis teks "Start" di tombol
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(buttonX + 75, buttonY + 31); // Sesuaikan posisi teks agar tetap di tengah tombol
    const char *buttonText = "Start";
    for (const char *c = buttonText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c); // Gunakan font yang lebih besar
    }
    glColor3f(1.0f, 1.0f, 1.0f); // Warna tombol
    glBegin(GL_QUADS);
    glVertex2i(buttonX, buttonY);
    glVertex2i(buttonX + buttonWidth, buttonY);
    glVertex2i(buttonX + buttonWidth, buttonY + buttonHeight);
    glVertex2i(buttonX, buttonY + buttonHeight);
    glEnd();

    drawBackground(width, height); // Gambar latar belakang


    // Kembalikan proyeksi dan modelview ke pengaturan semula
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glutSwapBuffers();
}
