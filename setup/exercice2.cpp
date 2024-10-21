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
bool wireframeMode = false;
bool blending = false;
bool fogEnabled = false;
float sensibilityDrag = 0.5f;



void updatePetitCubeRotation() {
    anglePetitCube += rotationSpeedPetitCube;
    glutPostRedisplay();
}

void updateBlending() {
    blending = !blending;
    glutPostRedisplay();
}


void toggleWireframeMode() {
    wireframeMode = !wireframeMode;
    glutPostRedisplay();
}

void fogEnabledMode() {
    fogEnabled = !fogEnabled;
    if (fogEnabled) {
        glEnable(GL_FOG);  // Activer le brouillard
    }
    else {
        glDisable(GL_FOG);  // Désactiver le brouillard
    }
    glutPostRedisplay();
}

void exercice2Display() {
    if (blending) {
        glEnable(GL_BLEND);   // Active le mode fil de fer
    }
    else {
        glDisable(GL_BLEND);

    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    gluLookAt(0.0f, 0.0f, -2.0f,  // Position de la caméra (0, 1, 3)
        0.0f, 0.0f, 0.0f,  // Point à regarder (0, 0, 0)
        0.0f, 1.0f, 0.0f); // Vecteur "up" (0, 1, 0)


    if (wireframeMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Active le mode fil de fer
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Rendu normal (faces pleines)
    }


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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DrawListCube = glGenLists(1);
    glNewList(DrawListCube, GL_COMPILE);
        glBegin(GL_QUADS);

        // Face avant
        glColor4f(1.0f, 1.0f, 0.0f, 0.5f); // Rouge
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);

        // Face arrière
        glColor4f(0.0f, 1.0f, 0.0f, 0.5f); // Vert
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);

        // Face gauche
        glColor4f(0.0, 0.0, 1.0, 0.5f); // Bleu
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);

        // Face droite
        glColor4f(1.0, 1.0, 0.0, 0.5f); // Jaune
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);

        // Face du haut
        glColor4f(1.0, 0.0, 1.0, 0.5f); // Magenta
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);

        // Face du bas
        glColor4f(0.0, 1.0, 1.0, 0.5f); // Cyan
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
        glColor4f(0.5, 0.5, 1.0,0.5f); // Bleu clair
        glVertex3f(-0.125, -0.125, 0.125);
        glVertex3f(0.125, -0.125, 0.125);
        glVertex3f(0.125, 0.125, 0.125);
        glVertex3f(-0.125, 0.125, 0.125);

        // Facearrière
        glColor4f(0.5, 1.0, 0.5, 0.5f); // Vert clair
        glVertex3f(-0.125, -0.125, -0.125);
        glVertex3f(-0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, -0.125);
        glVertex3f(0.125, -0.125, -0.125);

        // Face gauche
        glColor4f(1.0, 0.5, 0.5, 0.5f); // Rouge clair
        glVertex3f(-0.125, -0.125, -0.125);
        glVertex3f(-0.125, -0.125, 0.125);
        glVertex3f(-0.125, 0.125, 0.125);
        glVertex3f(-0.125, 0.125, -0.125);

        // Face droite
        glColor4f(1.0, 1.0, 0.5, 0.5f); // Jaune clair
        glVertex3f(0.125, -0.125, -0.125);
        glVertex3f(0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, 0.125);
        glVertex3f(0.125, -0.125, 0.125);

        // Face du haut
        glColor4f(0.5, 0.5, 0.5, 0.5f); // Gris
        glVertex3f(-0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, -0.125);
        glVertex3f(0.125, 0.125, 0.125);
        glVertex3f(-0.125, 0.125, 0.125);

        // Face du bas
        glColor4f(0.0, 1.0, 1.0, 0.5f); // Cyan
        glVertex3f(-0.125, -0.125, -0.125);
        glVertex3f(0.125, -0.125, -0.125);
        glVertex3f(0.125, -0.125, 0.125);
        glVertex3f(-0.125, -0.125, 0.125);

        glEnd();
    glEndList();

    DrawListSphere = glGenLists(1);
    glNewList(DrawListSphere, GL_COMPILE);
    glColor4f(1.0, 0.5, 0.0, 0.5f);
    glutSolidSphere(0.125, 20, 20);  
    glEndList();


    GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };  // Couleur du brouillard (gris)
    glFogfv(GL_FOG_COLOR, fogColor);  // Appliquer la couleur du brouillard
    glFogi(GL_FOG_MODE, GL_EXP);   // Mode de brouillard linéaire (tu peux essayer GL_EXP ou GL_EXP2)
    glFogf(GL_FOG_START, 1.0f);       // Début du brouillard
    glFogf(GL_FOG_END, 5.0f);



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
