#include "header/geradorMontanha.hpp"
#include <iostream>
#include <string> //bzero
#include <time.h> // srand(time(NULL));

GeradorMontanha::GeradorMontanha(int ordem, int alturaMax) {
    matrizDeAlturas = new int[ordem*ordem];
    bzero(this->matrizDeAlturas, sizeof(ordem*ordem));
    this->ordem = ordem;
    this->alturaMax = alturaMax;

    srand(time(NULL));
}

void GeradorMontanha::setTexture(const char* path) {
    this->textura = 
        SOIL_load_OGL_texture(
            path,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
        );
    
    if( this->textura == 0) {
        std::cout << "Imagem \"" << path << "\" não foi carregada.\n";
        exit(-1);
    }
}

GLuint GeradorMontanha::getTexture()
{
    return this->textura;
}

int GeradorMontanha::getOrdem()
{
	return this->ordem;
}

void GeradorMontanha::drawNivel(const int x, const int y, const int limitX, const int limitY, const int valMin, const int valMax)
{
	// draw superior line
	for (int i = y; i < limitY; ++i)
	{
        matrizDeAlturas[getPos(x, i)] = numberRandom(valMin, valMax);
	}

	// draw right column
	for (int i = x; i < limitX; ++i)
	{
        matrizDeAlturas[getPos(i, limitY - 1)] = numberRandom(valMin, valMax);
	}

	// draw down line
	for (int i = y; i < limitY; ++i)
	{
        matrizDeAlturas[getPos(limitX - 1, i)] = numberRandom(valMin, valMax);
	}

	// draw left column
	for (int i = x; i < limitX; ++i)
	{
        matrizDeAlturas[getPos(i, y)] = numberRandom(valMin, valMax);
	}
}

void GeradorMontanha::gerarAlturas()
{
	int meio = this->ordem / 2;
	int next_jump = this->alturaMax / meio;
	int altura_min = 0;
	int altura_max = next_jump;
	
	for (int i = 0, limite = this->ordem-1; i < meio; i++, limite--)
	{
		drawNivel(i, i, limite, limite, altura_min, altura_max);
		altura_min += next_jump;
		altura_max += next_jump;
	}
}

glm::vec3 GeradorMontanha::getTexCoord(int x, int y)
{
    return glm::vec3(x * ESP * 0.001, y * ESP * 0.001, matrizDeAlturas[getPos(x, y)] * 0.001);
}

glm::vec3 GeradorMontanha::getVertexCoord(int x, int y)
{
    return glm::vec3(x * ESP, y * ESP, matrizDeAlturas[getPos(x, y)]);
}

int GeradorMontanha::getPos(int x, int y)
{
    return x*this->ordem + y;
}

int GeradorMontanha::numberRandom(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}