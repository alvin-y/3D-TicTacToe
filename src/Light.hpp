#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <GL/glut.h>
#include "Shape.hpp"

class Light: public Shape {
public:
	//light and shading. use MC origin as the light position
	GLfloat I, Rd, Ia, Ra;
	GLboolean On;
	GLfloat size;

	Light();
	void Reset();
	void draw();
	void LightReset();
	void Increment(GLfloat, GLfloat, GLfloat);

};
#endif /* LIGHT_HPP_ */
