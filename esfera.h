#ifndef ESFERA_H
#define ESFERA_H
#include "point.h"

class Esfera
{
public:
    Esfera();
    Esfera(Point c, float r);
    bool Interseccao(Point p);

    Point centro;
    float raio;
};

#endif // ESFERA_H
