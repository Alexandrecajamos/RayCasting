#ifndef CENARIO_H
#define CENARIO_H
#include "observador.h"
#include "operacoes.h"
#include "objeto.h"
#include "camera.h"
#include "luz.h"
#include "v3.h"
#include "rgb.h"
#include "material.h"
#include "spot.h"
class Cenario
{
public:
    Cenario();
    Cenario(Observador *_Obs, Camera *_Cam,RGB* Ambiente ,RGB* BackGround);
    void addObjeto(Objeto *O);
    void addFonte(luz *L);
    void addFonte2(Point *P, RGB I);
    void addSpot(Spot *S);
    void Word_Cam(float **A);
    float Inter(Point Pij, int &iObj, int &iFace);
    RGB* Ray_Pix_Ilm(Point Pij);
    RGB* Ilm_Pint(Point Pint, Point nFace, Material *MF);
    void CuboUni();
    void CuboUni2(Material *M1,Material *M2,Material *M3,Material *M4,Material *M5,Material *M6);
    void Prisma_Triangular_Uni();
    void Prisma_Triangular_Uni2(Material *M1,Material *M2,Material *M3,Material *M4,Material *M5);

    RGB* Amb;
    RGB* BG;
    Observador *Obs;
    Camera *Cam;
    std::vector<Objeto*> Objetos;
    std::vector<luz*> fontes_luminosas;
    std::vector<Spot*> fontes_spot;
};

#endif // CENARIO_H
