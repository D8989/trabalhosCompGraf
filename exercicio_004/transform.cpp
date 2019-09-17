/*
    exercício 1 do slide "03 tramsformações em 2D"
*/

#include <GL/glut.h>
#include <iostream>

using namespace std;

float scale = 1.0;
float angle = 0.0;
float translation_x = 0.0, translation_y = 0.0, translation_z = 0.0;


void desenhaEixos();
void display(void);
void keyboardPress(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);
void init(void);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(300,300);
    glutInitWindowPosition(100,100);
    glutCreateWindow("tranformações 2d");
    init();
    cout << "use as setas para mover o quadrado\n";
    cout << "use o '+' ou '-', para aumentar ou diminuir o tamanho\n";
    cout << "use 'r' ou 'R' para rotacionar o quadrado.\n";

    glutKeyboardFunc(keyboardPress);
    glutSpecialFunc(specialKeysPress);
    glutDisplayFunc(display);
    
    glutMainLoop();

    return 0;
}

void init(void)
{
    glClearColor(0.,0.,0.,0.);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100., 100., -100., 100., -100., 100.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    desenhaEixos();

    glColor3f(1., 0., 0.);

    glPushMatrix();
    glTranslatef(translation_x, translation_y, translation_z);
    glRotatef(angle, 0., 0., 1.);
    glScalef(scale, scale, scale);
    glutWireCube(10); 
    /*
        Como o opengl sabe que quero mover só o quadrado?
        se inicio o lado com 10, como que o opengl desenha o tamanho com a escala?
        Como funciona o glPushMatrix e o glPopMatrix?
    */
    glPopMatrix();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void keyboardPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+':
        scale += 1;
        break;
    case '-':
        scale -= 1;
        break;
    case 'r':
        angle -= 10; 
        break;
    case 'R':
        angle += 10;
        break;
    default:
        break;
    }
}

void specialKeysPress(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        translation_y += 1;
        break;
    case GLUT_KEY_DOWN:
        translation_y -= 1;
        break;
    case GLUT_KEY_RIGHT:
        translation_x += 1;
        break;
    case GLUT_KEY_LEFT:
        translation_x -= 1;
        break;
    
    default:
        break;
    }
}