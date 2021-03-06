#include "Shape.hpp"
#include <stdio.h>
using namespace std;

Shape::Shape() {
	mc.loadIdentity();
	pmc = NULL;
	s = 1;
	tcounter = 0;
}

Shape::~Shape() { };

Matrix Shape::getMC() {
	return  mc;
};

void Shape::setParentMC(Matrix *pm) {
	pmc = pm;
}

void Shape::reset() {
	mc.loadIdentity();
	s = 1;
	tcounter = 0;
}

void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	mc.mat[0][3] += tx;
	mc.mat[1][3] += ty;
	mc.mat[2][3] += tz;
	mc.mat[3][3] = 1;
}

void Shape::set(GLfloat tx, GLfloat ty, GLfloat tz) {
	mc.mat[0][3] = tx;
	mc.mat[1][3] = ty;
	mc.mat[2][3] = tz;
	mc.mat[3][3] = 1;
}

void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle);
	mc.matrixPreMultiply(&m);
//	tcounter++;
//	if (tcounter >= 100) {
//		mc.normalize();
//		tcounter = 0;
//	}
}

void Shape::rotateMC(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	GLfloat x0 = mc.mat[0][3], y0 = mc.mat[1][3], z0 = mc.mat[2][3];
	//translate(-x0, -y0, -z0);
	rotate(rx, ry, rz, angle);
	//translate(x0, y0, z0);

	mc.mat[0][3] = x0;
	mc.mat[1][3] = y0;
	mc.mat[2][3] = z0;

//	tcounter++;
//	if (tcounter >= 100) {
//		mc.normalize();
//		tcounter = 0;
//	}
}

void Shape::rotateOrigin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = mc.mat[0][3];
	v[1] = mc.mat[1][3];
	v[2] = mc.mat[2][3];
	v[3] = mc.mat[3][3];
	m.multiplyVector(v);
	mc.mat[0][3] = v[0];
	mc.mat[1][3] = v[1];
	mc.mat[2][3] = v[2];
	mc.mat[3][3] = v[3];

//	// or, which is better?
//	Matrix *m = new Matrix();
//	m->rotateMatrix(rx, ry, rz, angle);
//	GLfloat v[4];
//	v[0] = mc.mat[0][3];
//	v[1] = mc.mat[1][3];
//	v[2] = mc.mat[2][3];
//	v[3] = mc.mat[3][3];
//	m->multiplyVector(v);
//	mc.mat[0][3] = v[0];
//	mc.mat[1][3] = v[1];
//	mc.mat[2][3] = v[2];
//	mc.mat[3][3] = v[3];
//	delete m;
}

void Shape::rotateRelative(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat rx,
		GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle * 1);
	GLfloat v[4];
	v[0] = mc.mat[0][3] - x0;
	v[1] = mc.mat[1][3] - y0;
	v[2] = mc.mat[2][3] - z0;
	v[3] = 1;
	m.multiplyVector(v);
	mc.mat[0][3] = v[0] + x0;
	mc.mat[1][3] = v[1] + y0;
	mc.mat[2][3] = v[2] + z0;
	mc.mat[3][3] = 1;
}


void Shape::scaleChange(GLfloat x) {
	s += x;
}

void Shape::scaleSet(GLfloat x) {
	s = x;
}

void Shape::ctmMultiply() {
	GLfloat M[16];
	M[0] = mc.mat[0][0];
	M[1] = mc.mat[1][0];
	M[2] = mc.mat[2][0];
	M[3] = 0;
	M[4] = mc.mat[0][1];
	M[5] = mc.mat[1][1];
	M[6] = mc.mat[2][1];
	M[7] = 0;
	M[8] = mc.mat[0][2];
	M[9] = mc.mat[1][2];
	M[10] = mc.mat[2][2];
	M[11] = 0;
	M[12] = mc.mat[0][3];
	M[13] = mc.mat[1][3];
	M[14] = mc.mat[2][3];
	M[15] = 1;
	glMultMatrixf(M);

//	mc.transpose();
//	glMultMatrixf(&mc.mat[0][0]);
//	mc.transpose();
}
