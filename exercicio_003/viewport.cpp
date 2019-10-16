#include <iostream>
#include <GL/glut.h>

const int window_with = 400;
const int window_height = 400;
const double max_x = 10;
const double max_y = 10;

void desenharTriangulo1();
void desenharTriangulo2();
void desenharLinhas();
void desenharEixos();
void initGL(void);
void initGlut(int *argc, char **argv, int width, int heigth, int posX, int posY, const char *title);
void display(void);

int main(int argc, char* argv[])
{
    initGlut(&argc, argv, window_with, window_height, 100, 100, "exercicio 3 - 4 viemport");
    initGL();

    glutDisplayFunc(display);

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
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_VIEWPORT);
    glViewport(0, 200, 200, 200); // superior esquerdo 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-max_x, max_x, -max_y, max_y, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    desenharEixos();
    desenharLinhas();
    desenharTriangulo1();
    desenharTriangulo2();


    glMatrixMode(GL_VIEWPORT);
    glLoadIdentity();
    glViewport(200, 200, 200, 200); // superior direito
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-1, max_x, -1, max_y, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenharEixos();
    desenharLinhas();
    desenharTriangulo1();
    desenharTriangulo2();

    glMatrixMode(GL_VIEWPORT);
    glViewport(0, 0, 200, 200); // inferior esquerdo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-max_x, 1, -max_y, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    desenharEixos();
    desenharLinhas();
    desenharTriangulo1();
    desenharTriangulo2();

    glMatrixMode(GL_VIEWPORT);
    glViewport(200, 0, 200, 200); // inferior direito
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, max_x, -max_y, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    desenharEixos();
    desenharLinhas();
    desenharTriangulo1();
    desenharTriangulo2();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void desenharTriangulo1()
{
    glBegin(GL_POLYGON);
    glColor3f(1., 1., 0.);
    glVertex3f(2., 2., 0.);
    glVertex3f(8., 2., 0.);
    glVertex3f(2., 8., 0.);
    glEnd();
}

void desenharTriangulo2()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(0., 1., 0.5);
    glVertex3f(2., -2., 0.);
    glVertex3f(8., -2., 0.);
    glVertex3f(2., -8., 0.);
    glEnd();
}

void desenharLinhas()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.,1.,1.);
    glVertex3f(-2., -2., 0.);
    glVertex3f(-8., -2., 0.);
    glVertex3f(-2., -8., 0.);
    glVertex3f(-8., -8., 0.);
    glEnd();
}

void desenharEixos()
{
    glBegin(GL_LINES);
    glColor3f(1.,0.,0.);
    glVertex3f(0., (GLfloat) max_y, 0);
    glVertex3f(0., (GLfloat) -max_y, 0);
    
    glColor3f(0., 1., 0.);
    glVertex3f((GLfloat) max_x, 0., 0);
    glVertex3f((GLfloat) -max_x, 0., 0);
    glEnd();
}