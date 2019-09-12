/*
    Name: Daniel Juventude Moreira
    
    Description: exercício 1 do slide "02 introdução ao OpenGl.pdf"
*/

// #include <stdio.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

int width = 500;
int heigth = 500;

bool figure_1_on = false;
bool figure_2_on = false;
bool figure_3_on = false;
bool figure_4_on = false;

void display(void);
void keyboardPress(unsigned char key, int x, int y);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, heigth);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Exercício 001");
    glClearColor(1., 1., 1., 0.);

    glutKeyboardFunc(keyboardPress);

    glutDisplayFunc(display);

    // printf("Janela criada.\n");
    cout << "Janela criada.\n";
    cout << "Digite 'a' para ver a figura 1.\n";
    cout << "Digite 'b' para ver a figura 2.\n";
    cout << "Digite 'c' para ver a figura 3.\n";
    cout << "Digite 'd' para ver a figura 4.\n";
    cout << "Digite qualquer letra para apagar.\n";


    glutMainLoop();
    

    return 0;
}

void display(void)
{
    // limpa todos os pixels
     glClear(GL_COLOR_BUFFER_BIT);

    // desenha o plano cartesiano
    glBegin(GL_LINES);
        glColor3f (0.0, 1.0, 0.0);
        glVertex2f (-1.0,0.0);
        glVertex2f(1.0,0.0);
        glVertex2f(0.0, 1.0);
        glVertex2f(0.0, -1.0);
    glEnd();

    if( figure_1_on ){
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(0.9, 0.0);
            glVertex2f(0.5, 0.9);
        glEnd();
    } else 
    if( figure_2_on ){
        glBegin(GL_LINE_LOOP);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(0.9, 0.0);
            glVertex2f(0.5, 0.9);
        glEnd();
    } else
    if ( figure_3_on ){
        glBegin(GL_LINE_LOOP);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(0.9, 0.0);
            glVertex2f(0.5, 0.9);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(-0.9, 0.0);
            glVertex2f(-0.5, -0.9);
        glEnd();

    } else
    if( figure_4_on )
    {
        glBegin(GL_LINE_STRIP);
            glColor3f(0.0, 0.0, 0.0);
            glVertex2f(-0.4, 0.8);
            glVertex2f(-0.8, 0.0);
            glVertex2f(-0.4, -0.8);
            glVertex2f(0.4, -0.8);
            glVertex2f(0.8, 0.0);
            glVertex2f(0.4, 0.8);
        glEnd();
    }

    glutSwapBuffers();
    glutPostRedisplay();

}

void keyboardPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        figure_1_on = true;
        figure_2_on = false;
        figure_3_on = false;
        figure_4_on = false;
        break;
    
    case 'b':
        figure_1_on = false;
        figure_2_on = true;
        figure_3_on = false;
        figure_4_on = false;
        break;
    
    case 'c':
        figure_1_on = false;
        figure_2_on = false;
        figure_3_on = true;
        figure_4_on = false;
        break;
    
    case 'd':
        figure_1_on = false;
        figure_2_on = false;
        figure_3_on = false;
        figure_4_on = true;
        break;

    default:
        figure_1_on = false;
        figure_2_on = false;
        figure_3_on = false;
        figure_4_on = false;
        break;
    }
}