 #include "object.h"
#include <iostream>
#include "render.h"
#include <vector>
#include <cmath>

float angle = 0.0;  
Player player;

std::vector<BoundingBox> boundingBoxes; // Vector to store bounding boxes

void createHitbox(float x, float y, float z, float width, float height, float depth) {
    // Create a hitbox using the given parameters
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(width, height, depth);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the hitbox
    glutWireCube(1.0f); // Draw a wireframe cube as the hitbox
    glPopMatrix();
    boundingBoxes.push_back({x, y, z, width, height, depth}); // Store the bounding box
}

void drawCar(const Car& car)  
{
    glPushMatrix();
    glTranslatef(car.position.x, car.position.y, car.position.z);
    glScalef(3, 3, 3); // Scale the whole car by 1.5 in all dimensions

    boundingBoxes.push_back({car.position.x, car.position.y, car.position.z, 5.0f, 1.5f, 1.0f}); // Create a hitbox for the car

    // Car body color
    glColor3f(0.8f, 0.2f, 0.0f); // Example: Orange color
    // Front Body
    glBegin(GL_QUADS);
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
    glPushMatrix();
    glTranslatef(car.position.x, 0, car.position.z);

    // Front Body
    glBegin(GL_QUADS);
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
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray

    // Function to draw a wheel
    auto drawWheel = [&](float x, float z)
    {
        glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glTranslatef(x, 0.2f, z);
        glRotatef(angle, 0, 0, 1); // Rotate the wheel
        glutSolidTorus(0.025, 0.07, 10, 25);
        glPopMatrix();

        // Draw the rim as a full circle (torus)
        glColor3f(0.9f, 0.9f, 0.9f); // Light gray for the rim
        glPushMatrix();
        glTranslatef(x, 0.2f, z);
        glRotatef(angle, 0, 0, 1);          // Rotate the wheel
        glutSolidTorus(0.02, 0.05, 10, 25); // Inner radius, outer radius, sides, rings
        glPopMatrix();

        // use "for" loop to draw the spokes
        for (int i = 0; i < 360; i += 45)
        {
            glPushMatrix();
            glColor3f(0.9f, 0.9f, 0.9f); // Light gray for the spokes
            glTranslatef(x, 0.2f, z);
            glRotatef(i, 0, 0, 1);     // Rotate the wheel
            glRotatef(90.0f, 0, 1, 0); // Rotate to align with the wheel
            gluCylinder(gluNewQuadric(), 0.005, 0.005, 0.06, 10, 10);
            glPopMatrix();
        }
    };

    // Draw each wheel
    drawWheel(0.6f, 0.62f);
    drawWheel(0.6f, 0.18f);
    drawWheel(1.7f, 0.18f);
    drawWheel(1.7f, 0.62f);

    glPopMatrix();
}

void drawPlayer(const Player& player) {
    glPushMatrix();
    // Badan
    glPushMatrix();
        glColor3f(0.2, 0.6, 0.8); // Biru
        glTranslatef(0.0f, 1.4f, 0.0f);
        glScalef(0.85f, 1.1f, 0.5f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Kepala
    glPushMatrix();
        glColor3f(1.0, 0.8, 0.6); // Warna kulit
        glTranslatef(0.0f, 2.4f, 0.0f);
        glRotatef(player.headRotation, 0.0f, 1.0f, 0.0f); // Rotasi kepala
        glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();
    
    // Rambut
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0); // Warna hitam
        glTranslatef(0.0f, 2.5f, 0.0f);
        glRotatef(player.headRotation, 0.0f, 1.0f, 0.0f); // Rotasi kepala
        glPushMatrix();
            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 0.0f, 0.0f); // Titik pusat setengah bola
            for (int angle = 0; angle <= 180; angle += 5) {
                float rad = angle * M_PI / 180.0f;
                glVertex3f(0.7f * cos(rad), 0.7f * sin(rad), 0.0f); // Titik-titik pada setengah lingkaran
            }
            glEnd();
        glPopMatrix();
    glPopMatrix();
    
    
    // Lengan kiri
    glPushMatrix();
        glColor3f(0.2, 0.6, 0.8); // Sama warna badan
        glTranslatef(-0.6f, 1.6f, 0.0f); // Pindahkan ke pangkal lengan kiri (ujung atas)
        glRotatef(player.leftArmRotation, 1.0f, 0.0f, 0.0f); // Rotasi lengan kiri
        glTranslatef(0.0f, -0.2f, 0.0f); // Geser ke bawah untuk menggambar lengan
        glScalef(0.25f, 0.8f, 0.25f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Lengan kanan (animasi memukul)
    glPushMatrix();
        glColor3f(0.2, 0.6, 0.8);
        glTranslatef(0.6f, 1.6f, 0.0f); // Pindahkan ke pangkal lengan kanan (ujung atas)
        glRotatef(player.rightArmRotation, 1.0f, 0.0f, 0.0f); // Rotasi lengan kanan
        float punchAngle = player.isPunching ? sin(player.punchProgress * M_PI_2) * 90.0f : 0.0f;
        glRotatef(punchAngle, 1.0f, 0.0f, 0.0f); // Tambahkan rotasi animasi memukul
        glTranslatef(0.0f, -0.2f, 0.0f); // Geser ke bawah untuk menggambar lengan
        glScalef(0.25f, 0.8f, 0.25f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki kiri
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0); // Hitam
        glTranslatef(-0.2f, 0.8f, 0.0f); // Pindahkan ke pangkal kaki
        glRotatef(player.leftLegRotation, 1.0f, 0.0f, 0.0f); // Rotasi kaki kiri
        glTranslatef(0.0f, -0.4f, 0.0f); // Geser ke bawah untuk menggambar kaki
        glScalef(0.35f, 1.0f, 0.3f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki kanan
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(0.2f, 0.8f, 0.0f); // Pindahkan ke pangkal kaki
        glRotatef(player.rightLegRotation, 1.0f, 0.0f, 0.0f); // Rotasi kaki kanan
        glTranslatef(0.0f, -0.4f, 0.0f); // Geser ke bawah untuk menggambar kaki
        glScalef(0.35f, 1.0f, 0.3f);
        glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void drawWall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z, GLfloat thickness) {-=
    // Tambahkan koordinat dinding ke sistem collision
    if (woodTexture == 0) return; // Pastikan tekstur sudah dimuat
    float centerX = (x1 + x2) / 2.0f; // Hitung titik tengah dinding pada sumbu X
    float centerZ = z + thickness / 2.0f; // Hitung titik tengah dinding pada sumbu X

    float height = fabs(y2 - y1); // Hitung tinggi dinding
    float width = fabs(x2 - x1); // Hitung lebar dinding

    float depth = thickness; // Ketebalan dinding

    // Buat bounding box untuk dinding
    boundingBoxes.push_back({centerX, y1 + height / 2.0f, centerZ, width, height, depth}); // Simpan bounding box

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, woodTexture); // Wall texture
    
    float repeatX = 5.0f; // Ulangi tekstur 5 kali di sumbu X
    float repeatY = 5.0f; // Ulangi tekstur 5 kali di sumbu Y

    // Draw front face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih agar tekstur terlihat jelas
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z + thickness);
    glTexCoord2f(repeatX, 0.0f); glVertex3f(x2, y1, z + thickness);
    glTexCoord2f(repeatX, repeatY); glVertex3f(x2, y2, z + thickness);
    glTexCoord2f(0.0f, repeatY); glVertex3f(x1, y2, z + thickness);
    glEnd();

    // Draw back face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f); // Normal pointing inwards
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih agar tekstur terlihat jelas
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z);
    glTexCoord2f(repeatX, 0.0f); glVertex3f(x2, y1, z);
    glTexCoord2f(repeatX, repeatY); glVertex3f(x2, y2, z);
    glTexCoord2f(0.0f, repeatY); glVertex3f(x1, y2, z);
    glEnd();

    // Draw left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f); // Normal pointing left
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih agar tekstur terlihat jelas
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z);
    glTexCoord2f(repeatX, 0.0f); glVertex3f(x1, y1, z + thickness);
    glTexCoord2f(repeatX, repeatY); glVertex3f(x1, y2, z + thickness);
    glTexCoord2f(0.0f, repeatY); glVertex3f(x1, y2, z);
    glEnd();

    // Draw right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f); // Normal pointing right
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih agar tekstur terlihat jelas
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x2, y1, z);
    glTexCoord2f(repeatX, 0.0f); glVertex3f(x2, y1, z + thickness);
    glTexCoord2f(repeatX, repeatY); glVertex3f(x2, y2, z + thickness);
    glTexCoord2f(0.0f, repeatY); glVertex3f(x2, y2, z);
    glEnd();

    // Draw top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f); // Normal pointing up
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih agar tekstur terlihat jelas
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y2, z);
    glTexCoord2f(repeatX, 0.0f); glVertex3f(x2, y2, z);
    glTexCoord2f(repeatX, repeatY); glVertex3f(x2, y2, z + thickness);
    glTexCoord2f(0.0f, repeatY); glVertex3f(x1, y2, z + thickness);
    glEnd();

    // Draw bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f); // Normal pointing down
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih agar tekstur terlihat jelas
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z);
    glTexCoord2f(repeatX, 0.0f); glVertex3f(x2, y1, z);
    glTexCoord2f(repeatX, repeatY); glVertex3f(x2, y1, z + thickness);
    glTexCoord2f(0.0f, repeatY); glVertex3f(x1, y1, z + thickness);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawSolidCylinder(GLfloat radius, GLfloat height, int slices, int stacks)
{
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluCylinder(quadric, radius, radius, height, slices, stacks);
    gluDeleteQuadric(quadric);
}

void drawTree(float x, float z)
{
    // Pohon
    glPushMatrix();
    glTranslatef(x, 0, z);

    // Batang pohon
    glPushMatrix();
    glColor3f(0.5f, 0.35f, 0.05f); // Warna coklat
    glRotatef(-90, 1, 0, 0);
    drawSolidCylinder(0.2, 2, 20, 20); // radius, height, slices, stacks
    glPopMatrix();

    // Daun pohon
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glColor3f(0.0f, 0.5f, 0.0f);
    glRotatef(-90, 1, 0, 0);     // Warna hijau
    glutSolidCone(1, 2, 20, 20); // base, height, slices, stacks
    glPopMatrix();

    // Daun pohon
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glColor3f(0.0f, 0.5f, 0.0f);
    glRotatef(-90, 1, 0, 0);     // Warna hijau
    glutSolidCone(1, 2, 20, 20); // base, height, slices, stacks
    glPopMatrix();

    // Daun pohon
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glColor3f(0.0f, 0.5f, 0.0f);
    glRotatef(-90, 1, 0, 0);     // Warna hijau
    glutSolidCone(1, 2, 20, 20); // base, height, slices, stacks
    glPopMatrix();

    glPopMatrix();
}

Player createPlayer(const std::string& name, float x, float y, float z) {
    Player player;
    player.name = name;
    player.position = {x, y, z};
    player.speed = 0.0f; // Initial speed
    player.rotation = 0.0f; // Initial rotation
    player.draw = drawPlayer; // Assign the draw function
    return player;
}

void changePlayerPosition(Player& player, float dx, float dy, float dz) {
    player.position.x += dx;
    player.position.y += dy;
    player.position.z += dz;
}
// Fungsi untuk membuat objek mobil
Car createCar(const std::string& name, float x, float y, float z, float speed, float rotation) {
    Car car;
    car.name = name;
    car.position = {x, y, z};
    car.speed = speed;
    car.rotation = rotation;
    car.draw = drawCar; // Assign the draw function
    return car;
}

// Fungsi untuk membuat objek pohon
Tree createTree(const std::string& name, float x, float y, float z, float scale, float height, float trunkRadius, const Color& color) {
    Tree tree;
    tree.name = name;
    tree.position = {x, y, z};
    tree.scale = scale;
    tree.height = height;
    tree.trunkRadius = trunkRadius;
    tree.color = color;
    return tree;
}

// Fungsi untuk membuat objek dinding
Wall createWall(const std::string& name, float x, float y, float z, float scale, float width, float height, float thickness, const Color& color) {
    Wall wall;
    wall.name = name; 
    wall.position = {x, y, z};
    wall.scale = scale;
    wall.width = width;
    wall.height = height;
    wall.thickness = thickness;
    wall.color = color;
    return wall;
}

// Fungsi untuk mencetak informasi objek
void printGameObjectInfo(const GameObject& obj) {
    std::cout << "Object Name: " << obj.name << "\n";
    std::cout << "Position: (" << obj.position.x << ", " << obj.position.y << ", " << obj.position.z << ")\n";
    std::cout << "Color: (" << obj.color.r << ", " << obj.color.g << ", " << obj.color.b << ")\n";
    std::cout << "Scale: " << obj.scale << "\n";
}
 
