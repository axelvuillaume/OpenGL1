#include <GL/freeglut.h>
#include "exercice2.h"


float angleX = 0.0f;
float angleY = 0.0f;
bool dragging = false;
int lastX, lastY;

float anglePetitCube = 0.0f;
float rotationSpeedPetitCube = 0.05f;

GLuint DrawListCube;
GLuint DrawListCube2;
GLuint DrawListSphere;



void updatePetitCubeRotation() {
    anglePetitCube += rotationSpeedPetitCube;
    glutPostRedisplay();
}




void exercice2Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluLookAt(0.0f, 0.0f, -2.0f,  // Position de la caméra (0, 1, 3)
        0.0f, 0.0f, 0.0f,  // Point à regarder (0, 0, 0)
        0.0f, 1.0f, 0.0f); // Vecteur "up" (0, 1, 0)

    glPushMatrix();
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotation autour de l'axe X
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotation autour de l'axe Y
    glCallList(DrawListCube);

    glPushMatrix();
    glTranslatef(-0.5f, 0.5f, -0.5f);
    glRotatef(anglePetitCube, 0.0f, 1.0f, 0.0f);
    glCallList(DrawListCube2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.5f);
    glCallList(DrawListSphere); 

    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
    

}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            dragging = true;
            lastX = x;
            lastY = y;
        }
        else if (state == GLUT_UP) {
            dragging = false;
        }
    }
}


void mouseMotion(int x, int y) {
    if (dragging) {
        int deltaX = x - lastX;
        int deltaY = y - lastY;

        angleY += deltaX * sensibilityDrag;
        angleX -= deltaY * sensibilityDrag;


        std::cout << "Angle X: " << angleX << ", Angle Y: " << angleY << std::endl;

        lastX = x;
        lastY = y;

        glutPostRedisplay();
    }
}

void init2() {
    DrawListCube = glGenLists(1);
    glNewList(DrawListCube, GL_COMPILE);
        glBegin(GL_QUADS);

        // Face avant
        glColor3f(1.0, 0.0, 0.0); // Rouge
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);

        // Face arrière
        glColor3f(0.0, 1.0, 0.0); // Vert
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);

        // Face gauche
        glColor3f(0.0, 0.0, 1.0); // Bleu
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);

        // Face droite
        glColor3f(1.0, 1.0, 0.0); // Jaune
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);

        // Face du haut
        glColor3f(1.0, 0.0, 1.0); // Magenta
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);

        // Face du bas
        glColor3f(0.0, 1.0, 1.0); // Cyan
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);

        glEnd();
    glEndList();


    DrawListCube2 = glGenLists(1);
    glNewList(DrawListCube2, GL_COMPILE);
        glBegin(GL_QUADS);

        // Petit cube (0.5x plus petit que le premier)
        // Face avant
        glColor3f(0.5, 0.5, 1.0); // Bleu clair
        glVertex3f(-0.125, -0.125, 0.125);
        glVertex3f(0.125, -0.125, 0.125);
        glVertex3f(0.125, 0.125, 0.125);
        glVertex3f(-0.125, 0.125, 0.125);

        // Face arrière
        glColor3f(0.5, 1.0, 0.5); // Vert clair
        glVertex3f(-0.125, -0.125, -0.125);
        glVertex3f(-0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, -0.125);
        glVertex3f(0.125, -0.125, -0.125);

        // Face gauche
        glColor3f(1.0, 0.5, 0.5); // Rouge clair
        glVertex3f(-0.125, -0.125, -0.125);
        glVertex3f(-0.125, -0.125, 0.125);
        glVertex3f(-0.125, 0.125, 0.125);
        glVertex3f(-0.125, 0.125, -0.125);

        // Face droite
        glColor3f(1.0, 1.0, 0.5); // Jaune clair
        glVertex3f(0.125, -0.125, -0.125);
        glVertex3f(0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, 0.125);
        glVertex3f(0.125, -0.125, 0.125);

        // Face du haut
        glColor3f(0.5, 0.5, 0.5); // Gris
        glVertex3f(-0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, 0.125);
        glVertex3f(-0.125, 0.125, 0.125);

        // Face du bas
        glColor3f(0.0, 1.0, 1.0); // Cyan
        glVertex3f(-0.125, -0.125, -0.125);
        glVertex3f(0.125, -0.125, -0.125);
        glVertex3f(0.125, -0.125, 0.125);
        glVertex3f(-0.125, -0.125, 0.125);

        glEnd();
    glEndList();

    DrawListSphere = glGenLists(1);
    glNewList(DrawListSphere, GL_COMPILE);
    glColor3f(1.0, 0.5, 0.0);
    glutSolidSphere(0.125, 20, 20);  
    glEndList();

}


void cleanup2()
{
    glDeleteLists(DrawListCube2, 1);
    glDeleteLists(DrawListCube, 1);
    glDeleteLists(DrawListSphere, 1);
}


void launchExercice2(){
    init2();
    glutDisplayFunc(exercice2Display);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutIdleFunc(updatePetitCubeRotation);
    glEnable(GL_DEPTH_TEST);
    //cleanup2();
}
