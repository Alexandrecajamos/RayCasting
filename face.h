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
    Face(Point *P1, Point *P2, Point *P3);
    Point calcNormal();
    void atNormal();
    float Inter(Point P);
    Point *P1,*P2,*P3, *N;
    Material *M;

};

#endif // FACE_H
