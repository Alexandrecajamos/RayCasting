#ifndef OBSERVADOR_H
#define OBSERVADOR_H
#include "point.h"
#include "operacoes.h"

class Observador
{
public:
    Observador();
    Observador(Point Pos, Point Look_At, Point A_View_UP);
    Point Pos,i,j,k;
    float** Word_Cam();
    float** Cam_Word();
};

#endif // OBSERVADOR_H
