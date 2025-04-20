#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include <GL/glut.h>


// Struct untuk mendefinisikan posisi 3D
struct Position {
    float x;
    float y;
    float z;
};
 
// Struct untuk mendefinisikan warna
struct Color {
    float r;
    float g;
    float b;
};
  
// Struct untuk mendefinisikan objek dasar
struct GameObject {
    std::string name;  // Nama objek
    Position position; // Posisi objek
    Color color;       // Warna objek
    float scale;       // Skala objek
};
struct Player : public GameObject {
    float speed;       // Kecepatan pemain
    float rotation;    // Rotasi pemain
    Position position;
    float rotationY;

    // Rotasi untuk animasi
    float leftArmRotation;
    float rightArmRotation;
    float leftLegRotation;
    float rightLegRotation;
    float headRotation;

    // Animasi memukul
    bool isPunching = false;       // Apakah sedang memukul
    float punchProgress = 0.0f;    // Progres animasi memukul (0.0 - 1.0)

    void (*draw)(const Player&); // Pointer ke fungsi untuk menggambar pemain
};

// Struct untuk mobil
struct Car : public GameObject {
    float speed;       // Kecepatan mobil
    float rotation;    // Rotasi mobil
    void (*draw)(const Car&); // Pointer ke fungsi untuk menggambar mobil
};

// Struct untuk pohon
struct Tree : public GameObject {
    float height;      // Tinggi pohon
    float trunkRadius; // Radius batang pohon
};

// Struct untuk dinding
struct Wall : public GameObject {
    float width;       // Lebar dinding
    float height;      // Tinggi dinding
    float thickness;   // Ketebalan dinding
};

// Struct untuk menyimpan semua objek dalam game
struct GameWorld {
    std::vector<Car> cars;       // Daftar mobil
    std::vector<Tree> trees;     // Daftar pohon
    std::vector<Wall> walls;     // Daftar dinding
};

struct BoundingBox {
    float minX, minY, minZ; // Koordinat minimum
    float maxX, maxY, maxZ; // Koordinat maksimum
};

extern std::vector<BoundingBox> boundingBoxes; // Daftar bounding box untuk collision detection

// Fungsi
void drawCar(const Car& car);
void drawTree(const Tree& tree);
void drawWall(const Wall& wall);
void drawSolidCylinder(GLfloat radius, GLfloat height, int slices, int stacks);
Car createCar(const std::string& name, float x, float y, float z, float speed, float rotation);
Tree createTree(const std::string& name, float x, float y, float z, float scale, float height, float trunkRadius, const Color& color);
Wall createWall(const std::string& name, float x, float y, float z, float scale, float width, float height, float thickness, const Color& color);
Player createPlayer(const std::string& name, float x, float y, float z);
void printGameObjectInfo(const GameObject& obj);
void changePlayerPosition(Player& player, float dx, float dy, float dz);
void drawPlayer(const Player& player); // Function to draw the player
extern Player player; // Declare player globally 

#endif    
    
  
