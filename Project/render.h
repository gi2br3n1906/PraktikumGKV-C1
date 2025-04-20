#ifndef RENDER_H
#define RENDER_H
#include <GL/glut.h>

void Grid();
void renderScene();
void drawWall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z, GLfloat thickness);
void KotakKayu();
void drawSolidCylinder(GLfloat radius, GLfloat height, int slices, int stacks);
void drawTree(float x, float z);
void makeCheckImage(void);
void makeWallImage(void);
void makeRoofImage(void);
void loadTexture(void);
void drawText(const char* text, int x, int y, void* font = GLUT_BITMAP_HELVETICA_18); // Default value here
float calculateFPS();
void updatePlayerAnimation(Player& player, float deltaTime, bool isMoving);
void updatePunchAnimation(Player& player, float deltaTime);
extern GLuint woodTexture;
extern GLuint grassTexture; // Grass texture
// textures
extern GLuint texture[3];

#endif   