/*
    exercicio 3 do slide 03
*/

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h> // ceil, floor

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;

const float FPS = 60.0; // a animação terá 'FPS' frames por segundo.
float lastXpos = -2.5, lastYpos = -2.5, lastZpos = 0;

// teste
const float speed = 0.5;
const float margem = 0.1;

const int WINDOW_SIZE = 300;

void display(void);
void mouse_callback(int button, int state, int x, int y);
void desenhaTabuleiro();
void desenhaQuadrado(int x, int y, int lado, glm::vec3 cor);
void desenhaCirculo(float raio, glm::vec3 cor);


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("exercicio 3 - 3");

    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMouseFunc(mouse_callback);

    glutMainLoop();

    return 0;
}


void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Inicializa com matriz identidade

    glMatrixMode(GL_VIEWPORT);
    glLoadIdentity();
    
    desenhaTabuleiro();

    glPushMatrix();
    glTranslatef(lastXpos, lastYpos, lastZpos);
    desenhaCirculo(0.4, glm::vec3(1.0, 0.0, 0.0));
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();

}

void desenhaTabuleiro()
{
    bool tradeColor = true;
    glm::vec3 cor;
    int lado = 1;
    int x = -3;
    int y = 3;

    for(int i = 0; i <= 6; ++i)
    {
        x = -3;
        for(int j = 0; j <= 6; ++j)
        {
            if( tradeColor ) {
                cor = glm::vec3(0.0, 0.0, 0.0);
            } else {
                cor = glm::vec3(1.0, 1.0, 1.0);
            }
            
            desenhaQuadrado(x, y, lado, cor);
            tradeColor = !tradeColor;

            x += lado;
        }
        y -= lado;
    }
}

void desenhaQuadrado(int x, int y, int lado, glm::vec3 cor)
{
    glBegin(GL_QUADS);
    // cor
    glColor3f(cor.x, cor.y, cor.z);
    // posicao
    glVertex2f(x, y);
    glVertex2f(x+lado, y);
    glVertex2f(x+lado, y+lado);
    glVertex2f(x, y+lado);
    glEnd();
}

void desenhaCirculo(float raio, glm::vec3 cor)
{
    glColor3f(cor.x, cor.y , cor.z);
    glutSolidSphere(raio, 25, 25);
}

void mouse_callback(int button, int state, int x, int y)
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        lastXpos = (float)x - WINDOW_SIZE/2.0;
        lastYpos = (float)y - WINDOW_SIZE/2.0;

        std::cout << "x: " << x << ", y: " << y << std::endl;
        std::cout << "x': " << lastXpos << ", y': " << lastYpos << std::endl;
    }
}

