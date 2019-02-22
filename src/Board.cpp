#include "Board.hpp"

Board::Board() {
	Piece0 = new Block();
	Piece0->set(-1, 2, 0);
	Piece0->setTextureID(0, 1);
	Piece0->setTextureID(1, 1);
	Piece0->setTextureID(2, 1);
	Piece0->setTextureID(3, 1);
	Piece0->setTextureID(4, 1);
	Piece0->setTextureID(5, 1);

	Piece1 = new Block();
	Piece1->set(1, 2, 0);
	Piece1->setTextureID(0, 1);
	Piece1->setTextureID(1, 1);
	Piece1->setTextureID(2, 1);
	Piece1->setTextureID(3, 1);
	Piece1->setTextureID(4, 1);
	Piece1->setTextureID(5, 1);

	Piece2 = new Block();
	Piece2->set(-2, 1, 0);
	Piece3 = new Block();
	Piece3->set(-1, 1, 0);
	Piece4 = new Block();
	Piece4->set(0, 1, 0);
	Piece5 = new Block();
	Piece5->set(1, 1, 0);
	Piece6 = new Block();
	Piece6->set(2, 1, 0);
	Piece7 = new Block();
	Piece7->set(-1, 0, 0);
	Piece8 = new Block();
	Piece8->set(1, 0, 0);
	Piece9 = new Block();
	Piece9->set(-2, -1, 0);
	Piece10 = new Block();
	Piece10->set(-1, -1, 0);
	Piece11 = new Block();
	Piece11->set(0, -1, 0);
	Piece12 = new Block();
	Piece12->set(1, -1, 0);
	Piece13 = new Block();
	Piece13->set(2, -1, 0);
	Piece14 = new Block();
	Piece14->set(-1, -2, 0);
	Piece15 = new Block();
	Piece15->set(1, -2, 0);
}

void Board::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	Piece0->draw();
	Piece1->draw();
	Piece2->draw();
	Piece3->draw();
	Piece4->draw();
	Piece5->draw();
	Piece6->draw();
	Piece7->draw();
	Piece8->draw();
	Piece9->draw();
	Piece10->draw();
	Piece11->draw();
	Piece12->draw();
	Piece13->draw();
	Piece14->draw();
	Piece15->draw();
	glPopMatrix();
}
