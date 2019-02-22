#ifndef GAMEPIECE_HPP_
#define GAMEPIECE_HPP_

#include <GL/glut.h>

#include "Shape.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Matrix.hpp"

class GamePiece: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];
	GLfloat r, g, b;
	GLuint textureID[6];
	int fill;
	bool lock;

public:
	GamePiece();
	void draw();
	void drawMC();
	void setTextureID(int index, int textureid);
	void setColour(int set);
	GLfloat* getCoord();
	void setFill(int set);
	void setGhost();
	void setLock(bool);

private:
	void draw_face(int);
	bool isFrontface(int faceindex, Camera cam);
	GLfloat getShade(int faceindex, Light light);
};

#endif
