#ifndef OBJETO_H
#define OBJETO_H
#include<vector>
#include "stdio.h"
#include "v3.h"
#include "face.h"
#include "esfera.h"
#include "operacoes.h"
#include "material.h"
#include <fstream>

class Objeto
{
public:
    Objeto();
    Objeto(char* Caminho);
        //void addPoint(Point P);
        //void addFace(Point p1, Point p2, Point p3, Material M);
        //void addFace2(Face F);

    void addPoint(float x, float y, float z);
    void addFace(int iP1, int iP2, int iP3, Material *M);
    void addFace2(int iP1, int iP2, int iP3);
    float Inter(Point Pint, int *ind);
    void calc_Esfera();
    // bool Interseccao();
    void Transforoma(float** A);

    Esfera Esf;
    std::vector<Point*> points;
    std::vector<Face*> faces;

};

#endif // OBJETO_H
