#include "Sphere.hpp"

Sphere::Sphere() {
	radius = 1.0;
	textureID = 0;
	splices = 50;
	stacks = 50;
	quad = gluNewQuadric();
}

Sphere::~Sphere() {
	gluDeleteQuadric(quad);
}

void Sphere::draw() {
	gluQuadricTexture(this->quad, GL_TRUE);
	gluQuadricOrientation(this->quad, GLU_OUTSIDE);
	gluQuadricNormals(this->quad, GLU_SMOOTH);

	glPushMatrix();
	this->ctmMultiply();
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textureID);
	gluSphere(this->quad, radius, 50, 50);
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(this->quad);
	glPopMatrix();
}




