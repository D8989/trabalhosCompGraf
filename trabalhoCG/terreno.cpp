#include "GL/glut.h"
#include "camera.hpp"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
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

// Para compilar: g++ terreno.cpp -o terreno -lGL -lglut -lGLU -lm -lSOIL
// ./terreno

const string textureArqPlant = "imagens/imgTextura2.jpg";
float posXCamera = 80.0f;
float posYCamera = -180.0f;

int altura[LIN][COL]; // pontos de altura Z para o terreno
GLuint imgTextura;
GLfloat angulo, fAspect;

Camera camera = Camera(glm::vec3(80.0f, -180.0f, 280.0f));

// apenas para debug
void printAturas()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < LIN; ++j)
		{
			cout << altura[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int numberRandom(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}

void observador(void)
{

	// Observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::vec3 position = camera.getPositon();

	// gluLookAt(posXCamera, posYCamera,280, 80,50,40, 0,0,1);
	gluLookAt(position.x, position.y, position.z, 80, 50, 40, 0, 0, 1);

	// Projecao
	glMatrixMode(GL_VIEWPORT);
	glViewport(0, 0, LARGURA, ALTURA);
	fAspect = (GLfloat)LARGURA / (GLfloat)ALTURA;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angulo, fAspect, 0.5, 5000);
}

// move camera pra direita
void cameraToRight(float posX, float posY)
{
	posXCamera += 5.5f;
	//posYCamera -= sin(posY);
}

void cameraToLeft(float posX, float posY)
{
	posXCamera -= 5.5f;
	//posYCamera += sin(posY);
}

void drawLineHorizontal(int inicio, int fim, int pos, int posZ)
{
	for (int i = inicio; i <= fim; ++i)
	{
		altura[pos][i] = posZ;
	}
}

void drawLineVertical(int inicio, int fim, int pos, int posZ)
{
	for (int i = inicio; i <= fim; ++i)
	{
		altura[i][pos] = posZ;
	}
}

void drawNivel(const int x, const int y, const int limitX, const int limitY, const int valMin, const int valMax)
{
	// draw superior line
	for (int i = y; i < limitY; ++i)
	{
		altura[x][i] = numberRandom(valMin, valMax);
	}

	// draw right column
	for (int i = x; i < limitX; ++i)
	{
		altura[i][limitY - 1] = numberRandom(valMin, valMax);
	}

	// draw down line
	for (int i = y; i < limitY; ++i)
	{
		altura[limitX - 1][i] = numberRandom(valMin, valMax);
	}

	// draw left column
	for (int i = x; i < limitX; ++i)
	{
		altura[i][y] = numberRandom(valMin, valMax);
	}
}

// Gerando pontos em Z
void pontosZ(void)
{
	//int jump = LIN/QTD_NIVEIS;
	int meio = COL / 2; // LIN == COL
	int next_jump = ALTURA_MAX / meio;
	int altura_min = 0;
	int altura_max = next_jump;
	//altura[meio][meio] = ALTURA_MAX; // ponto mais alto da montanha

	for (int i = 0, limite = COL - 1; i < meio; i++, limite--)
	{
		drawNivel(i, i, limite, limite, altura_min, altura_max);
		altura_min += next_jump;
		altura_max += next_jump;
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

	for (int y = 0; y < LIN; y++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (int x = 0; x < COL - 1; x++)
		{
			glTexCoord3f(x * ESP * 0.001, y * ESP * 0.001, altura[x][y] * 0.001);
			glVertex3i(x * ESP, y * ESP, altura[x][y]);

			glTexCoord3f(x * ESP * 0.001, (y + 1) * ESP * 0.001, altura[x][y + 1] * 0.001);
			glVertex3i(x * ESP, (y + 1) * ESP, altura[x][y + 1]);
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
		SOIL_FLAG_INVERT_Y);

	if (imgTextura == 0)
	{
		//printf("Erro do SOIL: '%s'\n", SOIL_last_result());
		cout << "Imagem da textura nao foi carregada";
	}

	bzero(altura, sizeof(LIN * COL)); // zera a matriz de alura

	// Efeito vazado nos triangulos
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

//Posicao do observador e projecao

void teclado(unsigned char key, int x, int y)
{
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

	float delta_time = 1.5f;
	switch (key)
	{
	case GLUT_KEY_LEFT:
		// cameraToLeft(posXCamera, posYCamera);
		camera.ProcessKeyboard(LEFT, delta_time);
		break;
	case GLUT_KEY_RIGHT:
		// cameraToRight(posXCamera, posYCamera);
		camera.ProcessKeyboard(RIGHT, delta_time);
		break;
	case GLUT_KEY_UP:
		camera.ProcessKeyboard(FORWARD, delta_time);
		break;
	case GLUT_KEY_DOWN:
		camera.ProcessKeyboard(BACKWARD, delta_time);
		break;
	}
	glutPostRedisplay();
}

// Main
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(LARGURA, ALTURA);
	glutCreateWindow("Geracao de terrano");

	srand(time(NULL));

	inicializa();
	// observador();
	pontosZ();
	glutDisplayFunc(desenhaPontos);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
}