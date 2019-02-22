#include "GamePiece.hpp"

extern Camera myCamera;
extern Light myLight;

extern bool isShading;
//extern bool isTexture;

GamePiece::GamePiece() {
// your definition of cube vertices and faces
	r = 1;
	g = 1;
	b = 1;

	fill = 1;
	lock = false;

	//back bottom left
	vertex[0][0] = -0.25;
	vertex[0][1] = -0.25;
	vertex[0][2] = -0.25;

	//back top left
	vertex[1][0] = -0.25;
	vertex[1][1] = 0.25;
	vertex[1][2] = -0.25;

	//back bottom right
	vertex[2][0] = 0.25;
	vertex[2][1] = -0.25;
	vertex[2][2] = -0.25;

	//back top right
	vertex[3][0] = 0.25;
	vertex[3][1] = 0.25;
	vertex[3][2] = -0.25;

	//front bottom left
	vertex[4][0] = -0.25;
	vertex[4][1] = -0.25;
	vertex[4][2] = 0.25;

	//front top left
	vertex[5][0] = -0.25;
	vertex[5][1] = 0.25;
	vertex[5][2] = 0.25;

	//front bottom right
	vertex[6][0] = 0.25;
	vertex[6][1] = -0.25;
	vertex[6][2] = 0.25;

	//front top right
	vertex[7][0] = 0.25;
	vertex[7][1] = 0.25;
	vertex[7][2] = 0.25;

	//back
	face[0][0] = 0;
	face[0][1] = 1;
	face[0][2] = 3;
	face[0][3] = 2;

	//right
	face[1][0] = 3;
	face[1][1] = 7;
	face[1][2] = 6;
	face[1][3] = 2;

	//front
	face[2][0] = 7;
	face[2][1] = 5;
	face[2][2] = 4;
	face[2][3] = 6;

	//left
	face[3][0] = 4;
	face[3][1] = 5;
	face[3][2] = 1;
	face[3][3] = 0;

	//top
	face[4][0] = 5;
	face[4][1] = 7;
	face[4][2] = 3;
	face[4][3] = 1;

	//bottom
	face[5][0] = 6;
	face[5][1] = 4;
	face[5][2] = 0;
	face[5][3] = 2;
}

void GamePiece::draw_face(int i) {
	if (isShading) {
		GLfloat shade = getShade(i, myLight);
		glColor3f(r * shade, g * shade, b * shade);
	} else {
		glColor3f(r, b, b);
	}

	if (fill == 1) {
		glBegin(GL_POLYGON);
		glVertex3fv(vertex[face[i][0]]);
		glVertex3fv(vertex[face[i][1]]);
		glVertex3fv(vertex[face[i][2]]);
		glVertex3fv(vertex[face[i][3]]);
		glEnd();
	} else {
		glBegin(GL_LINE_LOOP);
		glVertex3fv(vertex[face[i][0]]);
		glVertex3fv(vertex[face[i][1]]);
		glVertex3fv(vertex[face[i][2]]);
		glVertex3fv(vertex[face[i][3]]);
		glEnd();
	}

}

void GamePiece::setColour(int set) { //if 0 red, else blue
	if (!lock) {
		if (set == 0) {
			r = 1.0;
			g = 0;
			b = 0;
		} else {
			r = 0.137255;
			g = 0.137255;
			b = 0.556863;
		}
		lock = true;
	}
}

void GamePiece::setGhost() {
	r = 1;
	g = 1;
	b = 1;
	fill = 0;
}

void GamePiece::setFill(int set) { //0 for no fill, 1 for fill
	fill = set;
}

void GamePiece::setLock(bool set) { //false unlock true lock
	lock = set;
}

GLfloat* GamePiece::getCoord() {
	GLfloat temp[2];
	temp[0] = getMC().mat[0][3];
	temp[1] = getMC().mat[1][3];
	return temp;

}

void GamePiece::drawMC() {
	glColor3f(r, g, b);
	for (int i = 0; i < 6; i++) {
		if (isFrontface(i, myCamera)) {
			if (isShading) {
				GLfloat shade = getShade(i, myLight);
				glColor3f(r * shade, g * shade, b * shade);
			} else {
				glColor3f(r, g, b);
			}
			draw_face(i);
		}
	}
}

void GamePiece::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	//this->setColour(turn % 2);
	drawMC();
	glPopMatrix();
}

bool GamePiece::isFrontface(int faceindex, Camera cam) {
	// make a vector v of as normal of the face
	// multiply mc to v
	// compute the dot product of v and (ref-eye).
	// return true if it is a front face otherwise false
	GLfloat v[4];
	//p1 - p0
	Vector p0;
	p0.set(vertex[face[faceindex][1]][0] - vertex[face[faceindex][0]][0],
			vertex[face[faceindex][1]][1] - vertex[face[faceindex][0]][1],
			vertex[face[faceindex][1]][2] - vertex[face[faceindex][0]][2]);
	//p2 - p1
	Vector p1;
	p1.set(vertex[face[faceindex][2]][0] - vertex[face[faceindex][1]][0],
			vertex[face[faceindex][2]][1] - vertex[face[faceindex][1]][1],
			vertex[face[faceindex][2]][2] - vertex[face[faceindex][1]][2]);
	Vector norm = p0.cross(p1); //get cross product
	norm.normalize(); //normalize it
	v[0] = norm.x;
	v[1] = norm.y;
	v[2] = norm.z;
	v[3] = 0.0;
	this->mc.multiplyVector(v);

	GLfloat front = (cam.ref.x - cam.eye.x) * v[0]
			+ (cam.ref.y - cam.eye.y) * v[1] + (cam.ref.z - cam.eye.z) * v[2];

	//front face is < 0
	return front < 0;
}

GLfloat GamePiece::getShade(int faceindex, Light light) {
	GLfloat v[4], s[3], temp;

	s[0] = light.getMC().mat[0][3] - vertex[face[faceindex][0]][0];
	s[1] = light.getMC().mat[1][3] - vertex[face[faceindex][0]][1];
	s[2] = light.getMC().mat[2][3] - vertex[face[faceindex][0]][2];

	temp = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
	s[0] = s[0] / temp;
	s[1] = s[1] / temp;
	s[2] = s[2] / temp;

	//p1 - p0
	Vector p0;
	p0.set(vertex[face[faceindex][1]][0] - vertex[face[faceindex][0]][0],
			vertex[face[faceindex][1]][1] - vertex[face[faceindex][0]][1],
			vertex[face[faceindex][1]][2] - vertex[face[faceindex][0]][2]);
	//p2 - p1
	Vector p1;
	p1.set(vertex[face[faceindex][2]][0] - vertex[face[faceindex][1]][0],
			vertex[face[faceindex][2]][1] - vertex[face[faceindex][1]][1],
			vertex[face[faceindex][2]][2] - vertex[face[faceindex][1]][2]);
	Vector norm = p0.cross(p1); //get cross product
	v[0] = norm.x;
	v[1] = norm.y;
	v[2] = norm.z;
	v[3] = 1.0;
	this->mc.multiplyVector(v);

	mc.normalize();

	temp = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	GLfloat shade = light.I * light.Rd * temp + light.Ia * light.Ra;

	if (shade < 0)
		shade = 0;
	if (shade > 1)
		shade = 1;

	return shade;
}

void GamePiece::setTextureID(int index, int textureid) {
	textureID[index] = textureid;
}
