#include "GL/glut.h"
#include <SOIL/SOIL.h>
#include <iostream> 
#include <string.h>
#include <math.h>
// #include "perlin.h"
using namespace std;

#define ALTURA 600 
#define LARGURA 600
#define LIN 20 // Numero de linhas e colunas da malha
#define COL 20
#define ESP 10 // espacamento entre vertices da malha
#define ALTURA_MAX 150
#define QTD_NIVEIS 5

// Para compilar: g++ terreno.cpp -o terreno -lGL -lglut -lGLU -lm -lSOIL
// ./terreno

const string textureArqPlant = "imagens/imgTextura2.jpg";
float posXCamera = 80.0f;
float posYCamera = -180.0f;

int altura[LIN][COL]; // pontos de altura Z para o terreno
GLuint imgTextura;
GLfloat angulo,fAspect;

void observador(void)
{

	// Observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posXCamera, posYCamera,280, 80,50,40, 0,0,1);
	
	// Projecao
	glMatrixMode(GL_VIEWPORT);
    glViewport(0, 0, LARGURA, ALTURA);
	fAspect = (GLfloat)LARGURA/(GLfloat)ALTURA;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angulo,fAspect,0.5,5000);
}

// move camera pra direita
void cameraToRight(float posX, float posY ) {
	posXCamera += 5.5f;
	//posYCamera -= sin(posY);
}

void cameraToLeft(float posX, float posY ) {
	posXCamera -= 5.5f;
	//posYCamera += sin(posY);
}

void drawLineHorizontal(int inicio, int fim, int pos, int posZ) {
	for( int i = inicio; i <= fim; ++i) {
		altura[pos][i] = posZ;
	}
}

void drawLineVertical(int inicio, int fim, int pos, int posZ) {
	for( int i = inicio; i <= fim; ++i) {
		altura[i][pos] = posZ;
	}
}

void drawNivel(int xBegin, int yBegin, int xEnd, int yEnd, int posZ) {
	drawLineHorizontal(yBegin, yEnd, xBegin, posZ);
	drawLineHorizontal(yBegin, yEnd, xBegin, posZ);

	drawLineVertical(xBegin, xEnd, yBegin, posZ);
	drawLineVertical(xBegin, xEnd, yEnd, posZ);
}

// Gerando pontos em Z
void pontosZ(void)
{
	int jump = LIN/QTD_NIVEIS;
	int meio = COL/2; // LIN == COL
	//altura[meio][meio] = ALTURA_MAX; // ponto mais alto da montanha
/*	
	for( int nivel = 0; nivel < totalNiveis; nivel += 1){

	}
*/

	for (int y = 1; y < LIN-1; y++)
	{
		for (int x = 1; x < COL-2; x++)
		{	
			//altura[x][y] = rand() % 10 + (-10); 
			//altura[x][y] = 50 * perlin2d(x, y,0.3,4);
			altura[x][y] = rand() % (ALTURA_MAX + 1 - 10) + 10;
			//int posZ = rand() % (ALTURA_MAX + 1 - 50) + 50;
			//drawNivel(x, y, x+jump, y+jump,posZ);
		}
	}

}

void desenhaPontos(void)
{
	observador();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar todos os pixels
    //glColor3f (1, 1, 1);
	
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, imgTextura);

	// pontosZ();

	//glTranslatef(-LIN/2, -COL/2, 0.0f);

	for(int y = 0; y < LIN; y++)
	{
		glBegin(GL_TRIANGLE_STRIP);

			for(int x = 0; x < COL-1; x++)
			{
				glTexCoord3f(x*ESP*0.001, y*ESP*0.001,altura[x][y]*0.001);
				glVertex3i(x*ESP,y*ESP,altura[x][y]);

				glTexCoord3f(x*ESP*0.001, (y+1)*ESP*0.001,altura[x][y+1]*0.001);
				glVertex3i(x*ESP,(y+1)*ESP,altura[x][y+1]);
			}	

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	
   	glutSwapBuffers();
}


void inicializa(void)
{ 

	angulo = 45;

	// habilita mesclagem de cores
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	imgTextura = SOIL_load_OGL_texture(
	    textureArqPlant.c_str(),
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	if (imgTextura == 0) 
	{
		//printf("Erro do SOIL: '%s'\n", SOIL_last_result());
		cout << "Imagem da textura nao foi carregada";
	}

	bzero(altura, sizeof(LIN*COL)); // zera a matriz de alura

	// Efeito vazado nos triangulos 
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

//Posicao do observador e projecao


void teclado(unsigned char key, int x, int y) {
	switch (key)
    {
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
		cameraToLeft(posXCamera, posYCamera);
        break;
    case GLUT_KEY_RIGHT:
        cameraToRight(posXCamera, posYCamera);
        break;
   }
   glutPostRedisplay();
}

// Main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(LARGURA,ALTURA);
	glutCreateWindow("Geracao de terrano");
	inicializa();
	// observador();
	pontosZ();
    glutDisplayFunc(desenhaPontos);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
}