#ifndef CSHAPE_H
#define CSHAPE_H

#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/glut.h>

#include "Matrix.hpp"

using namespace std;

/**
 * Shape class the common class that will be inherited model object class
 */
class Shape {
protected:
	Matrix mc; // the Model coordinate system in (X, Y, Z, O)
	Matrix *pmc; // parent mc pointer
	GLfloat s; // scale factor
	GLint tcounter; // rotation transform counter

public:
	Shape();           // constructor
	virtual ~Shape();  // destructor
	Matrix getMC();   // Matrix
	void setParentMC(Matrix *pm);
	void ctmMultiply();          // function to do the CTM * MC
	void scaleChange(GLfloat x); // to change the scale factor
	void scaleSet(GLfloat x); // to change the scale factor
	void translate(GLfloat tx, GLfloat ty, GLfloat tz); //translate the MC origin
	void set(GLfloat tx, GLfloat ty, GLfloat tz); //move to set location
	void rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);      // rotate object in WC
	void rotateOrigin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);// just rotate the origin of object in WC
	void rotateMC(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);    // to rotate in MC
	void rotateRelative(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat rx,
			GLfloat ry, GLfloat rz, GLfloat angle);
	void reset();   // a function that resets the shape transformation matrix
	virtual void draw() = 0; // draw function must be overwritten
};

#endif
