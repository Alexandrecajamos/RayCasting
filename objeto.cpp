#include "objeto.h"
#include<cmath>

Objeto::Objeto()
{

}


void Objeto::addPoint(float x, float y, float z){
    Point *p = new Point(x,y,z);
    this->points.push_back(p);

}
void Objeto::addFace(int iP1, int iP2, int iP3, Material M){
    Face *F = new Face(this->points.at(iP1),this->points.at(iP2),this->points.at(iP3),M);
    this->faces.push_back(F);
}
void Objeto::calc_Esfera(){
    float mX=this->points.at(0)->x;
    float mY=this->points.at(0)->y;
    float mZ=this->points.at(0)->z;
    float MX=mX;float MY=mY;float MZ=mZ;
    for(std::vector<Point*>::iterator i = this->points.begin(); i!= this->points.end(); i++)
    {
        float x = (*i)->x;float y = (*i)->y;float z = (*i)->z;
        if(x<mX)
            mX = x;
        if(x>MX)
            MX = x;
        if(y<mY)
            mY = y;
        if(y>MY)
            MY = y;
        if(z<mZ)
            mZ = z;
        if(z>MZ)
            MZ = z;
    }
    Point _centro((MX+mX)/2,(MY+mY)/2,(MZ+mZ)/2);
    this->Esf.centro=_centro;
    float dx = std::abs(MX)+std::abs(mX);
    float dy = std::abs(MY)+std::abs(mY);
    float dz = std::abs(MZ)+std::abs(mZ);


    float d = 0;
    if(dx>dy && dx>dz)
            d = dx;
        else if(dy>dz)
            d = dy;
        else
            d = dz;

    this->Esf.raio=(d/2);

}


/*
void Objeto::addFace(Point P1, Point P2, Point P3, Material M){
    Face *F = new Face(P1,P2,P3, M);
    this->faces.push_back(F);

}
void Objeto::addFace2(Face F){
    this->faces.push_back(&F);
}
void Objeto::addPoint(Point P){
    this->points.push_back(&P);
}*/


