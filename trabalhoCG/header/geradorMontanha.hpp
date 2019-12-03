#ifndef GERADOR_MONTANHA_HPP
#define GERADOR_MONTANHA_HPP

#include "GL/glut.h"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
//

class GeradorMontanha {
private:
    int ordem;
    int alturaMax;
    GLuint textura;
    int* matrizDeAlturas;
    const int ESP = 10;

    
    int getPos(int x, int y);
    int numberRandom(int min, int max);
    void drawNivel(const int x, const int y, const int limitX, const int limitY, const int valMin, const int valMax);
public:

    GeradorMontanha(int ordem, int alturaMax);

    // carrega a imagem da textura pelo path.
    void setTexture(const char* path);
    GLuint getTexture();
    int getOrdem();
    
    glm::vec3 getTexCoord(int x, int y);
    glm::vec3 getVertexCoord(int x, int y);

    void gerarAlturas();
    

};

#endif
