#include "World.hpp"

World::World() {
	objnum = 3; // number of object
	list[0] = (Shape*) malloc( sizeof(Shape*) * objnum);  // array to hold object pointers

	//cube object
	list[0] = new Board();
	//list[0]->translate(1, 0, 0);

	list[1] = new GamePiece();
	list[2] = new GamePiece();
	//list[1]->translate(0, 0, 0);

	//house, replace the following by your house
//	list[2] = new House();
//	list[2]->scaleChange(-0.5);

}

World::~World(){
	for (int i = 0; i<objnum; i++)
	   delete list[i];

	free(list);
}

void World::draw() {
	for (int i = 0; i < 1; i++)
	   list[i]->draw();
}

void World::reset() {
	for (int i = 0; i < objnum; i++) {
	   list[i]->reset();
	}

	list[0]->translate(0, 0, 0);
	//list[2]->scaleChange(-0.5);

}

