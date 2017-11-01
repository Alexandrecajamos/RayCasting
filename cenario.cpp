#include "cenario.h"

Cenario::Cenario()
{

}

Cenario::Cenario(Observador *_Obs, Camera *_Cam){
    this->Obs=_Obs;
    this->Cam=_Cam;
}

void Cenario::addObjeto(Objeto *O){
    this->Objetos.push_back(O);
}

void Cenario::addFonte(luz *L){
    this->fontes_luminosas.push_back(L);
}
void Cenario::Word_Cam(float **A){
    for(std::vector<Objeto*>::iterator i = this->Objetos.begin(); i!= this->Objetos.end(); i++){
        (*i)->Transforoma(A);
    }
    for(std::vector<luz*>::iterator i = this->fontes_luminosas.begin();i!= this->fontes_luminosas.end();i++){
        Operacoes Op;
        Point *P = (*i)->P;
        float** V = Op.VetorColuna(P);
        float** r = Op.mult(4,4,1,A,V);
        P->x=r[0][0];
        P->y=r[1][0];
        P->z=r[2][0];

    }
}

float Cenario::Inter(Point Pij, int &Obj, int &Face){

    float Tint=999;
    int iFace, iObj;
    int cont=0;
    for(std::vector<Objeto*>::iterator i=this->Objetos.begin();i!=Objetos.end();i++){
        int iFace_temp;
        float temp = (*i)->Inter(Pij,&iFace_temp);
        if(temp != -1 && temp<Tint){
            Tint=temp;
            iFace=iFace_temp;
            iObj=cont;
        }
        cont++;
    }
    if(Tint != 999){
        Face = iFace;
        Obj = iObj;
    }else
        Tint = -1;
    return Tint;

}
