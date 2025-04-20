#include "lighting.h"


// Lighting parameters
const GLfloat light_ambient[] = {0.6f, 0.6f, 0.6f, 1.0f};    // Reduced ambient light
const GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};    // Reduced diffuse light
const GLfloat light_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};   // Reduced specular light
const GLfloat light_position[] = {0.0f, 20.0f, 10.0f, 0.0f}; // Directional light
const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};
   
void initLighting()
{ 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    // Enable shadow calculation
    glEnable(GL_LIGHT_MODEL_LOCAL_VIEWER);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}  