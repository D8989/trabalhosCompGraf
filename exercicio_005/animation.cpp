/*
    exercicio 2 do slide "03 transformações 2D[parte I]"
*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;

const float FPS = 60.0; // a animação terá 'FPS' frames por segundo.
float lastXpos = 0, lastYpos = 0, lastZpos = 0;
float lastAngle = 0;
float lastScale = 1;

// teste
const float speed = 0.5;
const float margem = 0.1;

void display(void);
void init (void);
void desenhaEixos();
void showMenu();
void mouse(int button, int state, int x, int y);

void idle(void); // principal do exercício

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (300, 300);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   glutIdleFunc(idle);
   glutMouseFunc( mouse );
   init ();
   printf("Posicione as janelas e clique na janela do OpenGL para habilitar o menu.\n");
   glutDisplayFunc(display);

   glutMainLoop();

   return 0;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      enableMenu = 1;
}

void showMenu()
{
   int op;
   system("cls");
   printf("\n=== MENU ===");
   printf("\n1 - Translacao");
   printf("\n2 - Rotacao");
   printf("\n3 - Escala");
   printf("\n4 - Sair");
   printf("\nOpcao: ");

   scanf("%d", &op);
   switch(op)
   {
      case 1:
         printf("\n\nInforme o vetor de translacao (entre -100.0 e 100.0)");
         printf("\nX : ");
         scanf("%f", &xtrans);
         printf("Y : ");
         scanf("%f", &ytrans);
      break;
      case 2:
         printf("\n\nInforme o angulo de rotacao (em graus): ");
         scanf("%f", &angle);
      break;
      case 3:
         printf("\n\nInforme o fator de escala: ");
         scanf("%f", &scale);
      break;
      case 4:
         exit(1);
      break;
      default:
         printf("\n\nOpcao invalida\n\n");
      break;
   }
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

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
      glTranslatef(lastXpos, lastYpos, 0.0);
      glRotatef(lastAngle, 0.0, 0.0, 1.0);
      glScalef(lastScale, lastScale, lastScale);
      glutWireCube(10);
   glPopMatrix();

   glutSwapBuffers ();
   glutPostRedisplay();

   if(enableMenu) showMenu();
}

void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// principal do exercício
void idle(void)
{
    float t, desiredFrameTime, frameTime;
    static float tLast = 0.0;
    bool flagx = false, flagy = false, flagz = false, 
        flagAngle = false, flagScale = false;

    // get elapsed time
    t = glutGet(GLUT_ELAPSED_TIME);
    // convert milliseconds to seconds
    t /= 1000.0;

    // calculate frame time
    frameTime = t - tLast;
    // calculate desired frame time
    desiredFrameTime = 1.0 / FPS;

    // check if the desired frame time was achived.
    // if not, skip animation
    if (frameTime <= desiredFrameTime ) return;

    /*
    Update animation variables
    */
    enableMenu = false;
    
    // update transx
    if (lastXpos > xtrans+margem){
        lastXpos -= speed;
    } else
    if (lastXpos < xtrans-margem) {
        lastXpos += speed;
    } else {
        flagx = true;
    }

    // update transy
    if (lastYpos > ytrans+margem){
        lastYpos -= speed;
    } else 
    if (lastYpos < ytrans-margem){
        lastYpos += speed;
    } else {
        flagy = true;
    }

    // update transz
    if (lastZpos > ztrans+margem){
        lastZpos -= speed;
    } else 
    if (lastZpos < ztrans-margem) {
        lastZpos += speed;
    } else {
        flagz = true;
    }

    // update angle
    if (lastAngle > angle+margem){
        lastAngle -= speed;
    } else
    if (lastAngle < angle-margem) {
        lastAngle += speed;
    } else {
        flagAngle = true;
    }

    // update scale
    if (lastScale > scale+margem){
        lastScale += speed;
    } else 
    if (lastScale < scale-margem) {
        lastScale -= speed;
    } else {
        flagScale = true;
    }

    if (flagx && flagy && flagz && flagAngle && flagScale){
        enableMenu = true;
    }

    // update tLast for next time, using static local variable
    tLast = t;    

    glutPostRedisplay();
}