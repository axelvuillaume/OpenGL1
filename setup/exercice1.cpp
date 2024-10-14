#include <GL/freeglut.h>
#include "exercice1.h"
#define TITLE "Hello OpenGL!"


float listVertex[3][2] = { {-0.5f, -0.5f}, { 0.5f, -0.5f }, { -0.5f, -0.5f } };
int current_vertice = -1;
int frameCount = 0;
double fps = 0.0;
std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();


void exercice1Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(listVertex[0][0], listVertex[0][1]);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(listVertex[1][0], listVertex[1][1]);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(listVertex[2][0], listVertex[2][1]);
	glEnd();

	glutSwapBuffers();
}


void motionfunc(int x, int y)
{
	listVertex[current_vertice][0] = (float)(x - SCREEN_WIDTH / 2) / (SCREEN_WIDTH / 2);
	listVertex[current_vertice][1] = -(float)(y - SCREEN_HEIGHT / 2) / (SCREEN_HEIGHT / 2);
	glutPostRedisplay();
}

void mousefunc(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON) {
			current_vertice = 0;

		}	if (button == GLUT_RIGHT_BUTTON) {
			current_vertice = 1;
		}if (button == GLUT_MIDDLE_BUTTON) {
			current_vertice = 2;
		}

	}
	glutPostRedisplay();
}


void idlefunc()
{
	frameCount++;

	auto currentTime = std::chrono::steady_clock::now();

	std::chrono::duration<double> elapsedTime = currentTime - lastTime;

	if (elapsedTime.count() >= 1.0) {
		fps = frameCount / elapsedTime.count();
		frameCount = 0;
		lastTime = currentTime;


		std::string windowTitle = TITLE + std::string(" | FPS: ") + std::to_string(fps);
		glutSetWindowTitle(windowTitle.c_str());
	}


	glutPostRedisplay();
}





void launchExercice1() {
	glutDisplayFunc(exercice1Display);
	glutMouseFunc(mousefunc);
	glutMotionFunc(motionfunc);
	glutIdleFunc(idlefunc);
}
