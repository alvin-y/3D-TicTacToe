#ifndef BLOCK_H
#define BLOCK_H

#include <GL/glut.h>

#include "Shape.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Matrix.hpp"

class Block: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];
	GLfloat r, g, b;
	GLuint textureID[6];

public:
	Block();
	void draw();
	void drawMC();
	void setTextureID(int index, int textureid);

private:
	void draw_face(int);
	bool isFrontface(int faceindex, Camera cam);
	GLfloat getShade(int faceindex, Light light);
};

#endif
