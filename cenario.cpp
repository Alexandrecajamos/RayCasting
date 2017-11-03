#include "cenario.h"

Cenario::Cenario()
{

}

Cenario::Cenario(Observador *_Obs, Camera *_Cam, RGB *_BG){
    this->Obs=_Obs;
    this->Cam=_Cam;
    this->BG=_BG;
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

RGB* Cenario::Ray_Pix_Ilm(Point px){
    RGB* RayPix = new RGB(this->BG->R, this->BG->G, this->BG->B); //(0.73,1,1); //Inicializa com background color;

    int iObj,iFace;
    float t = this->Inter(px, iObj,iFace);

    if(t!=-1 && t>1){
        Point Pint = px;
        Pint.operator *=(t);

        Face* F = this->Objetos.at(iObj)->faces.at(iFace); //obj->faces.at(ind);
        luz* Luz = this->fontes_luminosas.at(0);

        Point nFace = F->calcNormal();
        nFace.normalize();
        Point Fonte = (*Luz->P);
        // Já que não estou transformando a posição da luz W_to_Cam;
        Fonte.operator -=(Pint);
        Fonte.normalize();
        float xDif = nFace.ProdutoEscalar(Fonte);

        Point v =*Luz->P;
        v.operator -=(Pint);
        v.normalize();
        Point r = nFace;
        r.operator *=(2*xDif);
        r.operator -=(Fonte);
        r.normalize();
        float xEsp=v.ProdutoEscalar(r);
        xEsp=pow(xEsp,F->M->m);


        RGB A(F->M->A.R*Luz->F.R,F->M->A.G*Luz->F.G,F->M->A.B*Luz->F.B);
        RGB D(F->M->D.R*(Luz->F.R*xDif),F->M->D.G*(Luz->F.G*xDif),F->M->D.B*(Luz->F.B*xDif));
        RGB E (F->M->E.R*(Luz->F.R*xEsp),F->M->E.G*(Luz->F.G*xEsp),F->M->E.B*(Luz->F.B*xEsp));

        RayPix->R = A.R + D.R + E.R;
        RayPix->G = A.G + D.G + E.G;
        RayPix->B = A.B + D.B + E.B;
        RayPix->Normalize();
    }

    return RayPix;
}



void Cenario::CuboUni(){
    Objeto *cubo = new Objeto();

    cubo->addPoint(-0.5,-0.5,0.5);
    cubo->addPoint(0.5,-0.5,0.5);
    cubo->addPoint(0.5,-0.5,-0.5);
    cubo->addPoint(-0.5,-0.5,-0.5);
    cubo->addPoint(-0.5,0.5,0.5);
    cubo->addPoint(0.5,0.5,0.5);
    cubo->addPoint(0.5,0.5,-0.5);
    cubo->addPoint(-0.5,0.5,-0.5);

    cubo->addFace2(0,3,1);
    cubo->addFace2(1,3,2);
    cubo->addFace2(4,0,1);
    cubo->addFace2(1,5,4);
    cubo->addFace2(5,1,2);
    cubo->addFace2(2,6,5);
    cubo->addFace2(6,2,3);
    cubo->addFace2(3,7,6);
    cubo->addFace2(3,0,4);
    cubo->addFace2(4,7,3);
    cubo->addFace2(4,5,7);
    cubo->addFace2(5,6,7);

    this->addObjeto(cubo);
}

void Cenario::CuboUni2(Material *M1,Material *M2,Material *M3,Material *M4,Material *M5,Material *M6) {
    Objeto *cubo = new Objeto();

    cubo->addPoint(-0.5,-0.5,0.5);
    cubo->addPoint(0.5,-0.5,0.5);
    cubo->addPoint(0.5,-0.5,-0.5);
    cubo->addPoint(-0.5,-0.5,-0.5);
    cubo->addPoint(-0.5,0.5,0.5);
    cubo->addPoint(0.5,0.5,0.5);
    cubo->addPoint(0.5,0.5,-0.5);
    cubo->addPoint(-0.5,0.5,-0.5);

    cubo->addFace(0,3,1,M1);
    cubo->addFace(1,3,2,M1);
    cubo->addFace(4,0,1,M2);
    cubo->addFace(1,5,4,M2);
    cubo->addFace(5,1,2,M3);
    cubo->addFace(2,6,5,M3);
    cubo->addFace(6,2,3,M4);
    cubo->addFace(3,7,6,M4);
    cubo->addFace(3,0,4,M5);
    cubo->addFace(4,7,3,M5);
    cubo->addFace(4,5,7,M6);
    cubo->addFace(5,6,7,M6);

    this->addObjeto(cubo);


}
