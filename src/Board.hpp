#ifndef BOARD_H
#define BOARD_H

#include <GL/glut.h>

#include "Block.hpp"
#include "Shape.hpp"

class Board: public Shape {
protected:
	Block* Piece0;
	Block* Piece1;
	Block* Piece2;
	Block* Piece3;
	Block* Piece4;
	Block* Piece5;
	Block* Piece6;
	Block* Piece7;
	Block* Piece8;
	Block* Piece9;
	Block* Piece10;
	Block* Piece11;
	Block* Piece12;
	Block* Piece13;
	Block* Piece14;
	Block* Piece15;

public:
	Board();
	void draw();
};

#endif
