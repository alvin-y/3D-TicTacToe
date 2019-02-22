#ifndef MENU_HPP_
#define MENU_HPP_

//#include <GL/glut.h>
//#include "glsl/Angel.h"

#include "World.hpp"
#include "Camera.hpp"

void menu();

void WCTransMenu(GLint transOption);
void mainMenu(GLint option);
void VCTransMenu(GLint transOption);
void LightMenu(GLint objectOption);
void AMenu(GLint aOption);
void LTransMenu(GLint transOption);
//void move();

void viewTransforms(GLint);
void lightTransforms(GLint x);


#endif
