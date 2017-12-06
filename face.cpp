#include "face.h"
#include "operacoes.h"
#include "transformacoes.h"
Face::Face()
{

}
Face::Face(Point _P1, Point _P2, Point _P3){
    this->P1=&_P1;
    this->P2=&_P2;
    this->P3=&_P3;
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
    float t = -1;

    Point p1,p2,p3;
    p1= *(this->P1);
    p2= *(this->P2);
    p3= *(this->P3);

    Point nF = this->calcNormal();
    nF.normalize();
    Point Pint = P;
    float PE = Pint.ProdutoEscalar(nF);

    if(PE<0){
        /*
        float temp = (p1.ProdutoEscalar(nF))/PE;
        Pint.normalize();
        Pint.operator *=(temp);
        float u=0,v=0,w=0;
        Barycentric(Pint, p1, p2, p3, u,v,w);

        if(v>=0 && v<=1 && u>=0 && u<=1 && w>=0 && w<=1){
            //std::cout << "\n teste: "<< temp << ", " << u << ", " << v <<", "<< w;
            t = temp;
        }
*/

        Point v1 = p3;
        Point v2 = p3;
        v1.operator -=(p1);
        v2.operator -=(p2);

        transformacoes tr;
        float M[3][3];
        M[0][0] = v1.x; M[1][0] = v1.y; M[2][0] = v1.z;
        M[0][1] = v2.x; M[1][1] = v2.y; M[2][1] = v2.z;
        M[0][2] = P.x;  M[1][2] = P.y;  M[2][2] = P.z;
        float det = tr.Det3x3(M);
        tr.Inv3x3(M,det);
        Point lamb = tr.mxv(M,this->P3);

        float l3 = 1-(lamb.x+lamb.y);
        if(lamb.x>=0 && lamb.x<=1 && lamb.y>=0 && lamb.y<=1 && l3>=0 && l3<=1)
            t = lamb.z;

        //std::cout << t;


   /*
        float temp = (p1.ProdutoEscalar(nF))/PE;
        Pint.normalize();
        Pint.operator *=(temp);

        Face F1(p1, p2, Pint);
        Face F2(p2,p3, Pint);
        Face F3(p3,p1,Pint);
        Point n1 = F1.calcNormal();
        Point n2 = F2.calcNormal();
        Point n3 = F3.calcNormal();
        n1.normalize();
        n2.normalize();
        n3.normalize();

        float s1 = nF.ProdutoEscalar(n1);
        float s2 = nF.ProdutoEscalar(n2);
        float s3 = nF.ProdutoEscalar(n3);

        if(s1>=0 && s1<=1 && s2>=0 && s2<=1 && s3>=0 && s3<=1 )
            t= temp;


        std::cout << "\n T: " << t << " -> " << s1 << ", " << s2 << ", " << s3 << ";";
        std::cout << " - " << (s1+s2+s3);
*/
/*
       Operacoes Op;
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

            Pint.operator *=(lamb[2]);
            float l3 = 1-(lamb[0]+lamb[1]);

            if(lamb[0]>=0 && lamb[0]<=1 && lamb[1]>=0 && lamb[1]<=1 && l3>=0 && l3<=1){
                t=lamb[2];
                std::cout << "\n Matriz: "<< t << ", " << lamb[0] << ", " << lamb[1] <<", "<< l3;
            }
        }

        Op.freeMat(3, A);
        free(C_1);
        free(C_2);
        free(C_3);
        free(B);
        free(lamb);
*/
    }
    return t;

}

void Face::atNormal(){
    Point Norm = this->calcNormal();
    this->N = &Norm;
}


void Face::Barycentric(Point p, Point a, Point b, Point c, float &u, float &v, float &w)
{
    Point v0 = b; Point v1 = c; Point v2 = p;
    v0.operator -=(a); v1.operator -=(a); v2.operator -=(a);

    //Vector v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = v0.ProdutoEscalar(v0);
    float d01 = v0.ProdutoEscalar(v1);
    float d11 = v1.ProdutoEscalar(v1);
    float d20 = v2.ProdutoEscalar(v0);
    float d21 = v2.ProdutoEscalar(v1);

    float denom = (d00 * d11) - (d01 * d01);

    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1-v-w;

}
