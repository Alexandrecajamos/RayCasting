#ifndef FACE_H
#define FACE_H
#include "v3.h"
#include "material.h"
class Face
{
public:
    Face();
    Face(Point P1, Point P2, Point P3, Material *M);
    Face(Point *P1, Point *P2, Point *P3, Material *M);
    Point calcNormal();
    float Inter(Point P);
    Point *P1,*P2,*P3;
    Material *M;
};

#endif // FACE_H
