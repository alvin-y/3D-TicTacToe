#include "Light.hpp"
#include "Matrix.hpp"
#include <stdio.h>

Light::Light() {
	mc.mat[0][3] = 2.0;
	mc.mat[1][3] = 2.0;
	mc.mat[2][3] = 2.0;

	I = 1.0;
	Rd = 0.5;
	Ia = 1.0;
	Ra = 0.5;
	On = true;
	size = 30;
}

void Light::Reset() {
	I = 1.0;
	Rd = 0.5;
	Ia = 1.0;
	Ra = 0.5;
	On = true;
	size = 30;
}

void Light::Increment(GLfloat p, GLfloat ra, GLfloat rd) {
	I += p;
	if (I < 0)
		I = 0;
	if (I > 1)
		I = 1;

	Rd += rd;
	if (Rd < 0)
		Rd = 0;
	if (Rd > 1)
		Rd = 1;

	Ra += ra;
	if (Ra < 0)
		Ra = 0;
	if (Ra > 1)
		Ra = 1;

}


void Light::draw() {
	if (On == true) {
		glPushMatrix();
		this->ctmMultiply();
		glColor3f(I, I, I);
		glutSolidSphere(0.15, 50, 50);
		glPopMatrix();
		glPointSize(1);
	}
}


