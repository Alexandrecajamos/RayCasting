#ifndef CENARIO_H
#define CENARIO_H
#include "observador.h"
#include "operacoes.h"
#include "objeto.h"
#include "camera.h"
#include "luz.h"
#include "point.h"

class Cenario
{
public:
    Cenario();
    Cenario(Observador *_Obs, Camera *_Cam);
    void addObjeto(Objeto *O);
    void addFonte(luz *L);
    void Word_Cam(float **A);
    float Inter(Point Pij, int &iObj, int &iFace);

    Observador *Obs;
    Camera *Cam;
    std::vector<Objeto*> Objetos;
    std::vector<luz*> fontes_luminosas;

};

#endif // CENARIO_H
