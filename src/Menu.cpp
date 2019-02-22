#include "Menu.hpp"

extern GLint coordinate, selected;
extern GLint type, xBegin;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;
extern bool isShading;
extern int boardState[3][3];
extern int turn;
extern int playerTurn;

extern GamePiece ghost;
extern GamePiece piece0;
extern GamePiece piece1;
extern GamePiece piece2;
extern GamePiece piece3;
extern GamePiece piece4;
extern GamePiece piece5;
extern GamePiece piece6;
extern GamePiece piece7;
extern GamePiece piece8;

extern void pieceMove();

// light properties
GLfloat ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
GLfloat diffuse[] = { .6f, .6f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat positionSolar[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat local_view[] = { 0.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

void menu() {
	GLint VCTrans_Menu = glutCreateMenu(VCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Clipping Near ", 7);
	glutAddMenuEntry(" Clipping Far ", 8);

	GLint Light_Menu = glutCreateMenu(LightMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Point Light Intensity I", 7);
	glutAddMenuEntry(" Point Light Reflection Rd", 8);
	glutAddMenuEntry(" Ambient Reflection Ra", 9);
	glutAddMenuEntry(" Show Point Light ", 10);
	glutAddMenuEntry(" Hide Point Light ", 11);

	GLint A_Menu = glutCreateMenu(AMenu);
	glutAddMenuEntry(" Piece Animations ", 1);
	glutAddMenuEntry(" Stop Animations ", 2);

	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset Game ", 1);
	glutAddSubMenu(" Rotate Camera ", VCTrans_Menu);
	glutAddSubMenu(" Light Transformations ", Light_Menu);
	glutAddSubMenu(" Animations ", A_Menu);

	glutAddMenuEntry(" Quit", 2);
}

void mainMenu(GLint option) {
	switch (option) {
	case 1:
		myCamera.setDefaultCamera();
		myWorld.reset();
		myLight.reset();
		myLight.set(0, 3, 0);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				boardState[i][j] = 0;
			}
		}

		turn = 1;
		playerTurn = 1;

		ghost.setGhost();
		ghost.scaleSet(1);
		ghost.set(0, 0, 0);

		piece0.setLock(false);
		piece1.setLock(false);
		piece2.setLock(false);
		piece3.setLock(false);
		piece4.setLock(false);
		piece5.setLock(false);
		piece6.setLock(false);
		piece7.setLock(false);
		piece8.setLock(false);

		glutIdleFunc(NULL);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		//isShading = false;

		break;
	case 2:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void VCTransMenu(GLint transOption) {
	coordinate = 1;
	type = transOption;
	glutPostRedisplay();
}

void LightMenu(GLint transOption) {
	coordinate = 2;
	type = transOption;

	if (type == 10) {
		myLight.On = true;
	} else if (type == 11) {
		myLight.On = false;
	}

	glutPostRedisplay();
}

void viewTransforms(GLint x) {
	GLfloat theta = (xBegin - x > 0) ? 1 : -1;
	if (type == 1) { //view rotate x
		myCamera.rotate(1.0, 0.0, 0.0, theta * 0.5);
	} else if (type == 2) { //view rotate y
		myCamera.rotate(0.0, 1.0, 0.0, theta * 0.5);
	} else if (type == 3) { //view rotate z
		myCamera.rotate(0.0, 0.0, 1.0, theta * 0.5);
	} else if (type == 4) { //view translate x
		myCamera.translate(theta, 0.0, 0.0);
	} else if (type == 5) { //view translate y
		myCamera.translate(0.0, theta, 0.0);
	} else if (type == 6) { //view translate z
		myCamera.translate(0.0, 0.0, theta);
	} else if (type == 7) {
		myCamera.dnear += theta * .1;
	} else if (type == 8) {
		myCamera.dfar += theta * .1;
	}
}

void lightTransforms(GLint x) {
	GLfloat theta = (xBegin - x > 0) ? 1 : -1;

	if (type == 1) {
		myLight.rotateOrigin(1, 0, 0, theta * 0.5);
	}

	else if (type == 2) {
		myLight.rotateOrigin(0.0, 1.0, 0.0, theta * 0.5);
	}

	else if (type == 3) {
		myLight.rotateOrigin(0.0, 0.0, 1.0, theta * 0.5);
	}

	else if (type == 4) {
		myLight.translate(theta * 0.02, 0.0, 0.0);
	}

	else if (type == 5) {
		myLight.translate(0.0, theta * 0.02, 0.0);
	}

	else if (type == 6) {
		myLight.translate(0.0, 0.0, theta * 0.02);
	}

	else if (type == 7) {
		myLight.Increment(theta * 0.02, 0, 0);
	}

	else if (type == 8) {
		myLight.Increment(0, 0, theta * 0.02);

	} else if (type == 9) {
		myLight.Increment(0, theta * 0.02, 0);
	}

	position[0] = myLight.getMC().mat[0][3];
	position[1] = myLight.getMC().mat[1][3];
	position[2] = myLight.getMC().mat[2][3];
	glLightfv(GL_LIGHT0, GL_POSITION, position);

}

void AMenu(GLint aOption) {
	switch (aOption) {
	case 1:
		glutIdleFunc(pieceMove);
		break;
	case 2:
		glutIdleFunc(NULL);
		break;
	}
	glutPostRedisplay();
}
