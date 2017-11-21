#include "observador.h"

Observador::Observador()
{
    Point _pos(0,0,0);
    this->Pos = _pos;
    Point _i(1,0,0);
    this->i=i;
    Point _j(0,1,0);
    this->j=_j;
    Point _k(0,0,1);
    this->k=_k;

}

Observador::Observador(Point _pos, Point Look_At, Point A_View_UP){
    Operacoes Op;
    this->Pos=_pos;
    Point pk = _pos;
    pk.operator -=(Look_At);
    pk.normalize();
    this->k=pk;
    Point px= A_View_UP;
    px.operator -=(_pos);
    Point _x = Op.normal(px,pk);
    _x.normalize();
    this->i=_x;
    this->j=Op.normal(pk,_x);

}

Observador::Observador(Point _pos, Point Look_At){
    Operacoes Op;
    this->Pos=_pos;
    Point pk = _pos;
    pk.operator -=(Look_At);
    pk.normalize();
    this->k=pk;


}

float** Observador::Cam_Word(){
    Operacoes Op;
    float** A = Op.Identidade(4);
    float* I = Op.Vetor(this->i);
    float* J = Op.Vetor(this->j);
    float* K = Op.Vetor(this->k);
    float* P = Op.Vetor(this->Pos);
    P[3] = 1; // Corrigir Erro;
    for(int i=0;i<4;i++){
        A[i][0]=I[i];
        A[i][1]=J[i];
        A[i][2]=K[i];
        A[i][3]=P[i];

    }

    return A;
}

float** Observador::Word_Cam(){
    Operacoes Op;
    float** A = Op.Identidade(4);
    float* I = Op.Vetor(this->i);
    float* J = Op.Vetor(this->j);
    float* K = Op.Vetor(this->k);
    for(int i=0;i<4;i++){
        A[0][i]=I[i];
        A[1][i]=J[i];
        A[2][i]=K[i];
    }
    float x = this->i.ProdutoEscalar(this->Pos);
    float y = this->j.ProdutoEscalar(this->Pos);
    float z = this->k.ProdutoEscalar(this->Pos);
    A[0][3]=-x;
    A[1][3]=-y;
    A[2][3]=-z;
    return A;
}
