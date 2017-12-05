#include "face.h"
#include "operacoes.h"

Face::Face()
{

}
Face::Face(Point _P1, Point _P2, Point _P3, Material *_M){
    this->P1=&_P1;
    this->P2=&_P2;
    this->P3=&_P3;
    this->M =_M;
    this->atNormal();
}


Face::Face(Point *_P1, Point *_P2, Point *_P3, Material *_M){
    this->P1=_P1;
    this->P2=_P2;
    this->P3=_P3;
    this->M =_M;
    this->atNormal();
}

Face::Face(Point *_P1, Point *_P2, Point *_P3)
{
    this->P1=_P1;
    this->P2=_P2;
    this->P3=_P3;
    RGB pad(0.81176,0.81176,0.81176);
    this->M = new Material(pad,pad,pad,0.5);
    this->atNormal();

}
Point Face::calcNormal(){

    Point p1=*(this->P1);
    Point a=*(this->P2);
    Point b=*(this->P3);
    a.operator -=(p1);
    b.operator -=(p1);

    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);

    return p1;

}

float Face::Inter(Point P){
    Operacoes Op;
    Point p1,p2,p3;
    p1= *(this->P1);
    p2= *(this->P2);
    p3= *(this->P3);
    float t = -1;
    Point nF = this->calcNormal();
    nF.normalize();
    Point Pint = P;
    Pint.normalize();
    float PE = Pint.ProdutoEscalar(nF);

    if(PE<0){
        Point v1 = p3;
        Point v2 = p3;
        v1.operator -=(p1);
        v2.operator -=(p2);
        float** A = Op.Identidade(3);
        float *C_1 = Op.Vetor(v1);
        float *C_2 = Op.Vetor(v2);
        float *C_3 = Op.Vetor(P);
        for(int k = 0; k<3; k++){
            A[k][0]=C_1[k];
            A[k][1]=C_2[k];
            A[k][2]=C_3[k];
        }
        float* B = Op.Vetor(p3);
        float* lamb = Op.Gauss(3,A,B);
        if(lamb[2]>=0){
            float l3 = 1-(lamb[0]+lamb[1]);
            if(lamb[0]>=0 && lamb[0]<=1 && lamb[1]>=0 && lamb[1]<=1 && l3>=0 && l3<=1){
                t=lamb[2];
            }
        }

        Op.freeMat(3, A);
        free(C_1);
        free(C_2);
        free(C_3);
        free(B);
        free(lamb);

    }
    return t;

}

void Face::atNormal(){
    Point Norm = this->calcNormal();
    this->N = &Norm;
}
