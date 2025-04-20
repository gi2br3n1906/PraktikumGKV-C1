#ifndef CAMERA_H
#define CAMERA_H 

#include <GL/glut.h> 
#include <chrono>
#include "object.h" // Include object.h for Car struct
  
// Camera parameters
extern float cameraX, cameraY, cameraZ;
extern float cameraLX, cameraLY, cameraLZ;
extern float cameraSensitivity;
extern int mouseX, mouseY;
extern bool isJumping;
extern std::chrono::time_point<std::chrono::steady_clock> jumpStartTime;
extern float cameraRotationAroundCar;
extern float cameraRotationY;
extern float cameraRotationX ;
extern float movementDirectionX;
extern float movementDirectionZ;

void cameraReshape(int w, int h);
void cameraCenterMouse(int w, int h);
void updateCamera(const Player& player); // Pass player object to updateCamera
void orientMe(float ang); // Add declaration for orientMe
void mouseMove(int x, int y); // Add declaration for mouseMove
void mousePassiveMove(int x1, int y1);
void updateCameraForCar();
void updateCameraForPlayer(const Player& player);
void movePlayerBasedOnCamera(Player& player, float forward, float right);

// Jumping variables
extern float jumpSpeed;
extern float gravity;
extern float initialJumpVelocity;
extern float currentJumpVelocity;

extern bool isDriving; // State apakah sedang menyetir mobil
extern Car* currentCar; // Mobil yang sedang dikendarai
extern const float carDetectionRadius; // Radius deteksi mobil

#endif 
 