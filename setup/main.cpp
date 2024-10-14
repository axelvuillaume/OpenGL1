// setup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#define TITLE "Hello OpenGL!"
#include <chrono>
#include <string>
//#include "exercice1.h"
#include "exercice2.h"
#include "exercice1.h"
#include "constants.cpp"

bool projection = false;

void updateProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Réinitialise la matrice de projection

	GLfloat aspect = (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT; // Ratio d'aspect

	if (projection) {
		gluPerspective(70.0, aspect, 0.1, 100.0);
	}
	else {
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -2.0, 2.0);
	}

	glMatrixMode(GL_MODELVIEW); // Revenir à la matrice de modèle/vue
	glLoadIdentity(); // Réinitialise la matrice de modèle/vue
}

void select_exercice(int exercice) {
	switch (exercice) {
	case 1:
		glutDisplayFunc(launchExercice1);  // Afficher l'exercice 1
		break;
	case 2:
		glutDisplayFunc(launchExercice2); // Afficher l'exercice 2
		break;
	default:
		std::cout << "Exercice non valide" << std::endl;
		return;
	}
	glutPostRedisplay();  // Redessiner la fenêtre
}

void keyfunc(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		select_exercice(1);  // Sélectionner exercice 1
		break;
	case '2':
		select_exercice(2);  // Sélectionner exercice 2
		break;
	case 'c':
		projection = !projection; // Inverse la projection
		updateProjection(); // Met à jour la projection immédiatement
		glutPostRedisplay();
		break;
	case 'q':
		glutLeaveMainLoop();  // Quitter
		break;
	default:
		std::cout << "Touche non valide" << std::endl;
		break;
	}
}


void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // Couleur de fond

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	if (projection) {
		gluPerspective(70.0, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1, 100.0);
	}
	else {
		glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
	}


	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	
}


void reshape(int width, int height) {
	if (height == 0) height = 1;

	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	if (projection) {
		gluPerspective(70.0, aspect, 0.1, 100.0);
	}
	else {
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -2.0, 2.0); 
	}
	std::cout << projection << std::endl;

	glMatrixMode(GL_MODELVIEW);
}


void cleanup()
{
	// free allocated memory
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow(TITLE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	init();
	glutKeyboardFunc(keyfunc);
	//glutReshapeFunc(reshape);
	updateProjection();
	select_exercice(1);
	glutMainLoop();
	cleanup();
}
