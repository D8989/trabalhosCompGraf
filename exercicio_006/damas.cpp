/*
    exercicio 3 do slide 03
*/

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h> // ceil, floor


const float FPS = 60.0; // a animação terá 'FPS' frames por segundo.
float lastXpos = -2.5, lastYpos = -2.5, lastZpos = 1;
float xDestiny = lastXpos, yDestiny = lastYpos, zDestiny = 0.0f;

// teste
const float speed = 0.15f;
const float margem = 0.08;

const int WINDOW_SIZE = 300;
const float ORTHO_SIZE = 3.0;

glm::mat3 sistem = glm::mat3(1.0); // tdentity matrix


void display(void);
void mouse_callback(int button, int state, int x, int y);
void idle(void);

void desenhaTabuleiro();
void desenhaQuadrado(int x, int y, int lado, glm::vec3 cor);
void desenhaCirculo(float raio, glm::vec3 cor);
float updateCoord(float ponto, float destiny, float margem, float speed);

float updateCoordX(float ponto, float destiny, float margem, float speed);
float updateCoordY(float coefAngular, float x, float coefLinear);

float coeficienteAngular(float x1,float y1,float x2,float y2);
float coeficienteLinear(float coefAng, float x, float y);


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
    glOrtho(-ORTHO_SIZE, ORTHO_SIZE, -ORTHO_SIZE, ORTHO_SIZE, -1.0, 1.0);

    // init sistema para traduzir as coordenadas da janela para as coordenadas do glORtho
    sistem[0][0] =  ORTHO_SIZE/(WINDOW_SIZE/2.0);
    sistem[0][2] = -ORTHO_SIZE;
    sistem[1][1] = -ORTHO_SIZE/(WINDOW_SIZE/2.0);
    sistem[1][2] =  ORTHO_SIZE;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMouseFunc(mouse_callback);
    glutIdleFunc(idle);

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

    // glm::vec3 lastCoord = glm::vec3(lastXpos, lastYpos, lastZpos) * sistem;

    //std::cout << "x': " << lastXpos << ", y': " << lastYpos << std::endl;
    
    //float newX = (floor(lastXpos) + ceil(lastXpos))/2.0f;
    //float newY = (floor(lastYpos) + ceil(lastYpos))/2.0f;
    //float newZ = lastZpos;

    //std::cout << "new x: " << newX << ", new y': " << newY << std::endl;

    glPushMatrix();
    glTranslatef(lastXpos, lastYpos, lastZpos);
    desenhaCirculo(0.4f, glm::vec3(1.0, 0.0, 0.0));
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
        glm::vec3 newCoord = glm::vec3(x, y, 1.0) * sistem;
        xDestiny = ((int)floor(newCoord.x) + (int)ceil(newCoord.x))/2.0f;
        yDestiny = ((int)floor(newCoord.y) + (int)ceil(newCoord.y))/2.0f;
    }
}

void idle(void)
{
    float time, desiredFrameTime, frameTime;
    static float lastTime = 0.0f;

    time = glutGet(GLUT_ELAPSED_TIME);
    // convert milliseconds to seconds
    time /= 1000.0f;

    frameTime = time - lastTime;
    desiredFrameTime = 1.0 / FPS;

    // check if the desired frame time was achived.
    // if not, skip animation
    if (frameTime <= desiredFrameTime ) return;

    float coefAng = coeficienteAngular(lastXpos, lastYpos, xDestiny, yDestiny);
    float coefLin = coeficienteLinear(coefAng, lastXpos, lastYpos);
/*
    lastXpos = updateCoordX(lastXpos, xDestiny, margem, speed);
    lastYpos = updateCoordY(coefAng, lastXpos, coefLin);
*/
    lastXpos = updateCoord(lastXpos, xDestiny, margem, speed);
    lastYpos = updateCoord(lastYpos, yDestiny, margem, speed);

    lastTime = time;    
}


float updateCoord(float ponto, float destiny, float margem, float jump)
{
    float newPoint = ponto;

    if(ponto > destiny+margem){
        newPoint -= jump;
    }

    if( ponto < destiny-margem) {
        newPoint += jump;
    }

    return newPoint;
}
float updateCoordX(float ponto, float destiny, float margem, float jump)
{
    float newPoint = ponto;

    if(ponto > destiny+margem){
        newPoint -= jump;
    }

    if( ponto < destiny-margem) {
        newPoint += jump;
    }

    return newPoint;
}

float updateCoordY(float coefAngular, float x, float coefLinear)
{
    return coefAngular * x + coefLinear;
}

float coeficienteAngular(float x1,float y1,float x2,float y2)
{
    return (y2 - y1) / (x2 - x1);
}

float coeficienteLinear(float coefAng, float x, float y)
{
    return y - coefAng * x;
}
