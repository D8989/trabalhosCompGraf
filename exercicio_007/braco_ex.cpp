/*
    Exercício 1 e 2 do slide 04
*/

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

enum COR {
    RED,
    GREEN,
    BLUE,
    YELLOW
};


glm::vec3 red     = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 green   = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 blue    = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 yellow  = glm::vec3(1.0f, 1.0f, 0.0f);

COR selected;

float angleArmYellow = 0.0f, angleArmBlue = 0.0f, angleArmGreen = 0.0f;

const float minAngleClaw = 40.0f, maxAngleClaw = 89.0f;
float angleClaw = minAngleClaw;

void init(void);
void desenhaEixos();
void display(void);
void reshape (int w, int h);
void keyboard (unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

void posicionarCamera();
void drawOneArm(glm::vec3 cor, float angle);
void drawClaw(glm::vec3 cor, float angle);
void drawPartClaw(glm::vec3 cor, float angle); // função auxiliar para desenhar a garra 
void moveClockwise();
void moveAntiClockwise();
void openClaw();
void closeClaw();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}

void init(void)
{
    printf("Pressione as setas direita e esquerda para mover o braco.\n");
    printf("Selecione as teclas 1, 2 ou 3 para escolher o segmento a ser movido.\n");
    printf("Pressione ESC para sair.\n");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);         // habilita luz 0
    glEnable(GL_COLOR_MATERIAL); // Utiliza cor do objeto como material
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    glEnable(GL_LIGHTING);   // Habilita luz
    glEnable(GL_DEPTH_TEST); // Habilita Z-buffer
    glEnable(GL_CULL_FACE);  // Habilita Backface-Culling

}

void desenhaEixos()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Perguntar aonde coloco essa função 
void posicionarCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    desenhaEixos();

    glPushMatrix();
        drawOneArm(yellow, angleArmYellow);
        glTranslatef (1.0, 0.0, 0.0); // origem posicionada
        drawOneArm(green, angleArmGreen);
        glTranslatef (1.0, 0.0, 0.0); // origem posicionada
        drawOneArm(blue, angleArmBlue);
        glTranslatef (1.0, 0.0, 0.0); // origem posicionada
        drawClaw(red, angleClaw);
    glPopMatrix(); 
    glutSwapBuffers();
}

void reshape (int w, int h)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   // Por que o lookAt está dentro da função de reshape??
   gluLookAt (10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void drawOneArm(glm::vec3 cor, float angle)
{
    glColor3f(cor.x, cor.y, cor.z);
    glRotatef (angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glPushMatrix();
        glScalef(2.0f, 0.5f, 0.5f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void drawClaw(glm::vec3 cor, float angle)
{
    glPushMatrix();
        drawPartClaw(cor, angle);
        glScalef(1.0f, -1.0f, 1.0f);
        drawPartClaw(cor, angle);
    glPopMatrix();
}

void drawPartClaw(glm::vec3 cor, float angle)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
        // metade de tras da garra
        glColor3f(cor.x, cor.y, cor.z);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.5f, 0.0f, 0.0f);
        glPushMatrix();
            glScalef(1.0f, 0.25f, 0.25f);
            glutSolidCube(1.0f);
        glPopMatrix();

        // metade da frente da garra
        glColor3f(cor.x * 0.5f, cor.y * 0.5f, cor.z * 0.5f);
        glTranslatef(0.5f, 0.0f, 0.0f);
        glRotatef(-minAngleClaw*2.0f, 0.0f, 0.0f, 1.0f); // angulo fixo
        glTranslatef(0.5f, 0.0f, 0.0f);
        glScalef(1.0f, 0.25f, 0.25f);
        glutSolidCube(1.0f);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void moveClockwise()
{
    if(selected == COR::YELLOW){
        angleArmYellow = ((int) angleArmYellow - 5) % 360;
    } 
    if(selected == COR::BLUE){
        angleArmBlue = ((int) angleArmBlue - 5) % 360;
    }
    if(selected == COR::GREEN){
        angleArmGreen = ((int) angleArmGreen - 5) % 360;
    }
}

void moveAntiClockwise()
{
    if(selected == COR::YELLOW){
        angleArmYellow = ((int) angleArmYellow + 5) % 360;
    } 
    if(selected == COR::BLUE){
        angleArmBlue = ((int) angleArmBlue + 5) % 360;
    }
    if(selected == COR::GREEN){
        angleArmGreen = ((int) angleArmGreen + 5) % 360;
    }
}

void openClaw()
{
    angleClaw = ((int) angleClaw + 5) % 360;
    if( angleClaw > maxAngleClaw) {
        angleClaw = maxAngleClaw;
    }
}

void closeClaw()
{
    angleClaw = ((int) angleClaw - 5) % 360;
    if( angleClaw < minAngleClaw) {
        angleClaw = minAngleClaw;
    }
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        selected = COR::YELLOW;
        break;
    case '2':
        selected = COR::GREEN;
        break;
    case '3':
        selected = COR::BLUE;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void specialKeys(int key, int x, int y)
{
   switch(key)
   {
    case GLUT_KEY_LEFT:
		moveAntiClockwise();
        break;
    case GLUT_KEY_RIGHT:
        moveClockwise();
        break;
    case GLUT_KEY_UP:
        openClaw();
        break;
    case GLUT_KEY_DOWN:
        closeClaw();
        break;
   }
   glutPostRedisplay();
}