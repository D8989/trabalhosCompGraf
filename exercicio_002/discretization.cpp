/*
    Name: Daniel Juventude Moreira
    
    Description:    exercício 2 do slide "02 introdução ao OpenGl.pdf"
                    Discretização da função seno em 6, 12 e 180 partes.
*/

#include <iostream>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

using namespace std;

void initGL(void);
void initGlut(int *argc, char **argv, int width, int heigth, int posX, int posY, const char *title);
void display(void);
void drawSin(int parte, int limite);
void keyboardPress(unsigned char key, int x, int y);

const int limite = 360;
const int parte_6 = 6;
const int parte_12 = 12;
const int parte_180 = 180;
const int parte_360 = 360;
bool figure_1_on = false;
bool figure_2_on = false;
bool figure_3_on = false;

int main(int argc, char *argv[])
{
    initGlut(&argc, argv, 500, 500, 100, 100, "renderização");

    initGL();

    glutKeyboardFunc(keyboardPress);
    glutDisplayFunc(display);

    cout << "aperte 'a' para 6 partes.\n";
    cout << "aperte 's' para 12 partes.\n";
    cout << "aperte 'd' para 180 partes.\n";
    cout << "aperte qualquer tecla para apagar.\n";

    glutMainLoop();

    return 0;
}

void initGlut(int *argc, char **argv, int width, int heigth, int posX, int posY, const char *title)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, heigth);
    glutInitWindowPosition(posX, posY);
    glutCreateWindow(title);
}

void initGL(void)
{
    glClearColor(0., 0., 0., 0.); // limpa a tela com uma cor
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 390.0, -2.0, 2.0, -1.0, 1.0); // define o tamanho do dominio de cena
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    // Limpar todos os pixels
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o plano
    glBegin(GL_LINES);
    glColor3f(1., 1., 1.);
    glVertex3f(0, 2, 0);
    glVertex3f(0, -2, 0);
    glVertex3f(-10, 0, 0);
    glVertex3f(390, 0, 0);
    glEnd();

    if (figure_1_on)
    {
        drawSin(parte_6, limite);
    }
    else if (figure_2_on)
    {
        drawSin(parte_12, limite);
    }
    else if (figure_3_on)
    {
        drawSin(parte_180, limite);
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void drawSin(int parte, int limite)
{
    int passo = limite / parte;
    int pontos[parte];
    for (int i = 0; i <= parte; ++i)
    {
        pontos[i] = passo * i;
    }

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 0.0); // green
    
    for(int i = 0; i <= parte; ++i){
        glVertex2f(pontos[i], sin(pontos[i]*PI/180));
    }

    glEnd();
}

void keyboardPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        figure_1_on = true;
        figure_2_on = false;
        figure_3_on = false;
        break;
    
    case 's':
        figure_1_on = false;
        figure_2_on = true;
        figure_3_on = false;
        break;
    
    case 'd':
        figure_1_on = false;
        figure_2_on = false;
        figure_3_on = true;
        break;
    
    default:
        figure_1_on = false;
        figure_2_on = false;
        figure_3_on = false;
        break;
    }
}