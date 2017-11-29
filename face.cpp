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
    //float *v = (float *)malloc(sizeof(float)* 3);
    Point p1=*(this->P1);
    Point a=*(this->P2);
    Point b=*(this->P3);
    a.operator -=(p1);
    b.operator -=(p1);

    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);

    //p1.normalize();
    return p1;

    /*float* Normal(int N, float* A, float* B){
    float* n = (float *)malloc(sizeof(float)* N);
    n[0] = (A[1]*B[2])-(A[2]*B[1]);
    n[1] = (A[2]*B[0])-(A[0]*B[2]);
    n[2] = (A[0]*B[1])-(A[1]*B[0]);
    n[3] = 0;
    float norma = NormaVetor(N,n);
    Escalar(N,n,(1/norma));
    return n;
}*/

}

float Face::Inter(Point P){
    Operacoes Op;
    Point p1,p2,p3;
    p1= *(this->P1);
    p2= *(this->P2);
    p3= *(this->P3);
    float t = -1;
    Point nF = this->calcNormal();//(this->N->x,this->N->y,this->N->z);
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
            if(lamb[0]>=0 && lamb[0]<=1 && lamb[1]>=0 && lamb[1]<=1 && l3>=0 && l3<=1)
            t=lamb[2];
        }

    }
    return t;

}

void Face::atNormal(){
    Point Norm = this->calcNormal();
    this->N = &Norm;
}
