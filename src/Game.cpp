//#include <GL/glew.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>

#include "Menu.hpp"

// global variables
GLint winWidth = 800, winHeight = 800;
GLint moving = 0; // 0:not mouse moving mode, 1: in mouse down moving mode
GLint xBegin = 0; // global variable to store the first mouse x coordainte
GLint coordinate = 1; // coordinate system option, 1:MC, 2:WC, 3:VC
GLint type = 2;   // transformation type/option
GLint selected = 0; // index of selected object
bool isShading = true; // shading option

World myWorld; //world
Camera myCamera; //camera
Light myLight; //lamp

bool isTexture = false;

//Game Variables
int turn;
int playerTurn;
int boardState[3][3];

//Pieces
GamePiece piece0;
GamePiece piece1;
GamePiece piece2;
GamePiece piece3;
GamePiece piece4;
GamePiece piece5;
GamePiece piece6;
GamePiece piece7;
GamePiece piece8;

GamePiece ghost;

int checkWin();
void winAnim();

void init(void) {
	glClearColor(0.137255, 0.756863, 0.419608, 1.0); //Set display-window color to black
	myCamera.setDefaultCamera();

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			boardState[i][j] = 0;
		}
	}
	turn = 1;
	playerTurn = 1;
	myLight.set(0, 3, 0);

	ghost.setFill(0);

	piece0.set(-2, 2, 0);
	piece0.setTextureID(0, 1);
	piece0.setTextureID(1, 1);
	piece0.setTextureID(2, 1);
	piece0.setTextureID(3, 1);
	piece0.setTextureID(4, 1);
	piece0.setTextureID(5, 1);
	piece1.set(0, 2, 0);
	piece2.set(2, 2, 0);
	piece3.set(-2, 0, 0);
	piece4.set(0, 0, 0);
	piece5.set(2, 0, 0);
	piece6.set(-2, -2, 0);
	piece7.set(0, -2, 0);
	piece8.set(2, -2, 0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();

	myWorld.draw();
	myLight.draw();

	ghost.draw();

	int drawX;
	int drawY;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (boardState[i][j] != 0) {
				//find piece on board
				if (j == 0) {
					drawX = -2;
				} else if (j == 1) {
					drawX = 0;
				} else {
					drawX = 2;
				}

				if (i == 0) {
					drawY = -2;
				} else if (i == 1) {
					drawY = 0;
				} else {
					drawY = 2;
				}

				//draw accordingly
				if (drawX == -2 && drawY == 2) {
					if (boardState[i][j] == 1)
						piece0.setColour(0);
					else
						piece0.setColour(1);
					//printf("%d\n", boardState[i][j]);
					piece0.draw();
				}
				if (drawX == 0 && drawY == 2) {
					if (boardState[i][j] == 1)
						piece1.setColour(0);
					else
						piece1.setColour(1);
					piece1.draw();
				}
				if (drawX == 2 && drawY == 2) {
					if (boardState[i][j] == 1)
						piece2.setColour(0);
					else
						piece2.setColour(1);
					piece2.draw();
				}
				if (drawX == -2 && drawY == 0) {
					if (boardState[i][j] == 1)
						piece3.setColour(0);
					else
						piece3.setColour(1);
					piece3.draw();
				}
				if (drawX == 0 && drawY == 0) {
					if (boardState[i][j] == 1)
						piece4.setColour(0);
					else
						piece4.setColour(1);
					piece4.draw();
				}
				if (drawX == 2 && drawY == 0) {
					if (boardState[i][j] == 1)
						piece5.setColour(0);
					else
						piece5.setColour(1);
					piece5.draw();
				}
				if (drawX == -2 && drawY == -2) {
					if (boardState[i][j] == 1)
						piece6.setColour(0);
					else
						piece6.setColour(1);
					piece6.draw();
				}
				if (drawX == 0 && drawY == -2) {
					if (boardState[i][j] == 1)
						piece7.setColour(0);
					else
						piece7.setColour(1);
					piece7.draw();
				}
				if (drawX == 2 && drawY == -2) {
					if (boardState[i][j] == 1)
						piece8.setColour(0);
					else
						piece8.setColour(1);
					piece8.draw();
				}
			}
		}
	}

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int action, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (action == GLUT_DOWN) {
			moving = 1;
			xBegin = x;
		} else if (action == GLUT_UP) {
			moving = 0;
		}
	}
}

void keyboardMoveAction(int key, int x, int y) {
	GLfloat *coords = ghost.getCoord();
	if (coords[0] == 0 && coords[1] == 3) {
		return;
	}
	switch (key) {
	case (GLUT_KEY_RIGHT):
		if (coords[0] == 2) {
			ghost.set(-2, coords[1], 0);
		} else {
		ghost.translate(2, 0, 0);
		}
		break;
	case (GLUT_KEY_LEFT):
		if (coords[0] == -2) {
			ghost.set(2, coords[1], 0);
		} else {
			ghost.translate(-2, 0, 0);
		}
		break;
	case (GLUT_KEY_UP):
		if (coords[1] == 2) {
			ghost.set(coords[0], -2, 0);
		} else {
			ghost.translate(0, 2, 0);
		}
		break;
	case (GLUT_KEY_DOWN):
		if (coords[1] == -2) {
			ghost.set(coords[0], 2, 0);
		} else {
			ghost.translate(0, -2, 0);
		}
		break;
	}
}

void keyboardAction(unsigned char key, int x, int y) {
	if (!checkWin() && turn < 10) {
		printf("Turn %d | Player %d's Turn\n", turn, playerTurn);

		switch (key) {
		case (' '):
			GLfloat* coords = ghost.getCoord();
			if (!(boardState[(int) coords[1] / 2 + 2][(int) coords[0] / 2 - 2])) {
				boardState[(int) coords[1] / 2 + 2][(int) coords[0] / 2 - 2] =
						playerTurn;
				turn++; //next turn
				if (playerTurn == 1) {
					ghost.setLock(false);
					ghost.setColour(1);
					playerTurn = 2;
				} else {
					ghost.setLock(false);
					ghost.setColour(0);
					playerTurn = 1;

				}
				PlaySound("move.wav", NULL, SND_ASYNC | SND_FILENAME);
			}
			//printf("%.1f %.1f\n", coords[0], coords[1]);
			break;

		}
		//Test printing
		for (int i = 2; i >= 0; i--) {
			printf("%d %d %d\n", boardState[i][0], boardState[i][1],
					boardState[i][2]);
		}
	}
	if (checkWin()) {
		printf("Player %d Won!\n", checkWin());
		PlaySound("win.wav", NULL, SND_ASYNC | SND_FILENAME);
		ghost.setFill(1);
		ghost.set(0, 3, 0);
		ghost.scaleSet(2);
		if (checkWin() == 1) {
			//printf("red");
			ghost.setLock(false);
			ghost.setColour(0);
		} else {
			ghost.setLock(false);
			//printf("blue");
			ghost.setColour(1);
		}
		glutIdleFunc(winAnim);
	} else if (!checkWin() && turn == 10) {
		printf("There's a Tie!\n");
	}
}

void mouseMotion(GLint x, GLint y) {
	if (moving) {
		if (coordinate == 1) {      //view transformations
			viewTransforms(x);
		} else if (coordinate == 2) { //light transformations
			lightTransforms(x);
		}
		glutPostRedisplay();
	}
}

int checkWin() {
	//horizontal
	if (boardState[0][0] != 0 && boardState[0][0] == boardState[0][1]
			&& boardState[0][1] == boardState[0][2]) {
		return boardState[0][0];
	}
	if (boardState[1][0] != 0 && boardState[1][0] == boardState[1][1]
			&& boardState[1][1] == boardState[2][2]) {
		return boardState[1][0];
	}
	if (boardState[2][0] != 0 && boardState[2][0] == boardState[2][1]
			&& boardState[2][1] == boardState[2][2]) {
		return boardState[2][0];
	}
	//vertical
	if (boardState[0][0] != 0 && boardState[0][0] == boardState[1][0]
			&& boardState[1][0] == boardState[2][0]) {
		return boardState[0][0];
	}
	if (boardState[0][1] != 0 && boardState[0][1] == boardState[1][1]
			&& boardState[1][1] == boardState[2][1]) {
		return boardState[0][1];
	}
	if (boardState[0][2] != 0 && boardState[0][2] == boardState[1][2]
			&& boardState[1][2] == boardState[2][2]) {
		return boardState[0][2];
	}
	//diagonal
	if (boardState[1][1] != 0 && boardState[0][0] == boardState[1][1]
			&& boardState[1][1] == boardState[2][2]) {
		return boardState[1][1];
	}
	if (boardState[1][1] != 0 && boardState[0][2] == boardState[1][1]
			&& boardState[1][1] == boardState[2][0]) {
		return boardState[1][1];
	}
	return 0;
}

void pieceMove() {
	piece0.rotateMC(1, -1, 1, 5);
	piece1.rotateMC(-1, 1, 1, 5);
	piece2.rotateMC(1, 1, 1, 5);
	piece3.rotateMC(-1, -1, -1, 5);
	piece4.rotateMC(-1, 1, -1, 5);
	piece5.rotateMC(-1, -1, 1, 5);
	piece6.rotateMC(1, 1, -1, 5);
	piece7.rotateMC(1, -1, -1, 5);
	piece8.rotateMC(-1, 1, -1, 5);

	glutPostRedisplay();
}

void winAnim() {
	//ghost.scaleChange(1);
	ghost.rotateMC(1, 0, 0, 5);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);  //used for prompt Eclipse console output
	setvbuf(stderr, NULL, _IONBF, 0);
	//ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);  //used to hide console

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("3D TicTacToe (Alvin Yao)");


	menu();
	init();

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutSpecialFunc(keyboardMoveAction);
	glutKeyboardFunc (keyboardAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();
	return 0;
}
