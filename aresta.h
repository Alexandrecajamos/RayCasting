#ifndef ARESTA_H
#define ARESTA_H
#include "point.h"

class Aresta
{
public:
    Aresta();
    Aresta(Point P1, Point P2);
    Point P1;
    Point P2;
};

#endif // ARESTA_H
