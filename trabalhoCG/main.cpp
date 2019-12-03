#include "header/camera.hpp"
#include "header/geradorMontanha.hpp"
#include <iostream>

using namespace std;

#define ALTURA_JANELA 600
#define LARGURA_JANELA 600
#define ORDEM 20
#define ALTURA_MAX 150

GLfloat angulo, fAspect;
const string imagemPath = "imagens/imgTextura1.jpg";

Camera camera = Camera(glm::vec3(80.0f, -180.0f, 280.0f));
GeradorMontanha montanha(ORDEM, ALTURA_MAX);

void specialKeys(int key, int x, int y);
void teclado(unsigned char key, int x, int y);
void display(void);
void atualizarCamera(void);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
	glutCreateWindow("Geracao de montanha");

	angulo = 45;
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	montanha.setTexture(imagemPath.c_str());

	montanha.gerarAlturas();

	glutDisplayFunc(display);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
}

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
		camera.ProcessKeyboard(LEFT, delta_time);
		break;
	case GLUT_KEY_RIGHT:
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

void atualizarCamera(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::vec3 position = camera.getPositon();
	gluLookAt(position.x, position.y, position.z, 80, 50, 40, 0, 0, 1);

	glMatrixMode(GL_VIEWPORT);
	glViewport(0, 0, LARGURA_JANELA, ALTURA_JANELA);
	fAspect = (GLfloat)LARGURA_JANELA / (GLfloat)ALTURA_JANELA;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angulo, fAspect, 0.5, 5000);
}

void display(void) 
{
	atualizarCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, montanha.getTexture());

	for (int y = 0; y < montanha.getOrdem(); y++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (int x = 0; x < montanha.getOrdem() - 1; x++)
		{
			glm::vec3 texCoord;
			glm::vec3 vertexCoord;

			texCoord = montanha.getTexCoord(x, y);
			vertexCoord = montanha.getVertexCoord(x, y);
			glTexCoord3f(texCoord.x, texCoord.y, texCoord.z);
			glVertex3i(vertexCoord.x, vertexCoord.y, vertexCoord.z);

			texCoord = montanha.getTexCoord(x, y+1);
			vertexCoord = montanha.getVertexCoord(x, y+1);
			glTexCoord3f(texCoord.x, texCoord.y, texCoord.z);
			glVertex3i(vertexCoord.x, vertexCoord.y, vertexCoord.z);
		}

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}