#include "cenario.h"
#define PI 3.14159265
Cenario::Cenario()
{

}

Cenario::Cenario(Observador *_Obs, Camera *_Cam, RGB*_Amb, RGB *_BG){
    this->Obs=_Obs;
    this->Cam=_Cam;
    this->Amb=_Amb;
    this->BG=_BG;
}
void Cenario::addObjeto(Objeto *O){
    this->Objetos.push_back(O);
}
void Cenario::addFonte(luz *L){
    this->fontes_luminosas.push_back(L);
}
void Cenario::addSpot(Spot *S){
    this->fontes_spot.push_back(S);
}
void Cenario::addFonte2(Point *P, RGB I){
    luz* L = new luz(I,P);
    this->fontes_luminosas.push_back(L);
}
void Cenario::Word_Cam(float **A){

    Operacoes Op;
    for(std::vector<Objeto*>::iterator i = this->Objetos.begin(); i!= this->Objetos.end(); i++){
        (*i)->Transforoma(A);
    }
    for(std::vector<luz*>::iterator i = this->fontes_luminosas.begin();i!= this->fontes_luminosas.end();i++){

        Point *P = (*i)->P;
        float** V = Op.VetorColuna(P);
        float** r = Op.mult(4,4,1,A,V);
        (*i)->P->x=r[0][0];
        (*i)->P->y=r[1][0];
        (*i)->P->z=r[2][0];

    }

    for(std::vector<Spot*>::iterator i = this->fontes_spot.begin();i!=this->fontes_spot.end();i++){
        Point *P = (*i)->Luz->P;
        float** V = Op.VetorColuna(P);
        float** r = Op.mult(4,4,1,A,V);
        (*i)->Luz->P->x=r[0][0];
        (*i)->Luz->P->y=r[1][0];
        (*i)->Luz->P->z=r[2][0];
    }

    Point *temp = new Point(Obs->Pos.x, Obs->Pos.y, Obs->Pos.z);
    float** obs = Op.VetorColuna(temp);
    float** r = Op.mult(4,4,1,A,obs);
    Obs->Pos.x=r[0][0];
    Obs->Pos.y=r[1][0];
    Obs->Pos.z=r[2][0];

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
    RGB* RayPix = new RGB(this->BG->R, this->BG->G, this->BG->B); //Inicializa com background color;

    int iObj,iFace;
    float t = this->Inter(px, iObj,iFace);

    if(t!=-1 && t>1){
        Point Pint = px;
        Pint.operator *=(t);
        Face* F = this->Objetos.at(iObj)->faces.at(iFace);
        Point nFace = F->calcNormal();
        nFace.normalize();

        RGB A(F->M->A.R*this->Amb->R,F->M->A.G*this->Amb->G,F->M->A.B*this->Amb->B);

        float Dr=0, Dg=0, Db=0, Er=0, Eg=0, Eb=0;

        for(std::vector<luz*>::iterator i=this->fontes_luminosas.begin();i!=fontes_luminosas.end();i++){

            luz* Luz = (*i);
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();
            float xDif = nFace.ProdutoEscalar(Fonte);

            Point v = this->Obs->Pos;  //Luz->P;
            v.operator -=(Pint);
            v.normalize();
            Point r = nFace;
            r.operator *=(2*xDif);
            r.operator -=(Fonte);
            r.normalize();
            float xEsp=v.ProdutoEscalar(r);
            xEsp=pow(xEsp,F->M->m);

            if(xDif > 0){
                Dr += Luz->F.R*xDif;
                Dg += Luz->F.G*xDif;
                Db += Luz->F.B*xDif;
            }
            if(xEsp > 0){
                Er += Luz->F.R*xEsp;
                Eg += Luz->F.G*xEsp;
                Eb += Luz->F.B*xEsp;
            }
        }

        for(std::vector<Spot*>::iterator i=this->fontes_spot.begin();i!=fontes_spot.end();i++){

            luz* Luz = (*i)->Luz;
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();

            Point *D = (*i)->Direcao;
            D->x = -D->x; D->y = -D->y; D->z = -D->z;
            float cos = Fonte.ProdutoEscalar(*D);

            if(cos>0){

                float Teta = acos (cos) * 180.0 / PI;

                if(Teta < (*i)->Abertura){

                    float R = Luz->F.R*cos;
                    float G = Luz->F.G*cos;
                    float B = Luz->F.B*cos;

                    float xDif = nFace.ProdutoEscalar(Fonte);

                    Point v = this->Obs->Pos;  //Luz->P;
                    v.operator -=(Pint);
                    v.normalize();
                    Point r = nFace;
                    r.operator *=(2*xDif);
                    r.operator -=(Fonte);
                    r.normalize();
                    float xEsp=v.ProdutoEscalar(r);
                    xEsp=pow(xEsp,F->M->m);

                    if(xDif > 0){
                        Dr += R*xDif;
                        Dg += G*xDif;
                        Db += B*xDif;
                    }
                    if(xEsp > 0){
                        Er += R*xEsp;
                        Eg += G*xEsp;
                        Eb += B*xEsp;
                    }
                }
            }



        }


        RGB D(F->M->D.R*(Dr),F->M->D.G*(Dg),F->M->D.B*(Db));
        RGB E(F->M->E.R*(Er),F->M->E.G*(Eg),F->M->E.B*(Eb));

        RayPix->R = A.R + D.R + E.R;
        RayPix->G = A.G + D.G + E.G;
        RayPix->B = A.B + D.B + E.B;
        RayPix->Normalize();
    }

    return RayPix;
}

RGB* Cenario::Ilm_Pint(Point Pint, Face *F){
    RGB* RayPix = new RGB(this->BG->R, this->BG->G, this->BG->B); //Inicializa com background color;

    Point nFace = F->calcNormal();
    nFace.normalize();

    RGB A(F->M->A.R*this->Amb->R,F->M->A.G*this->Amb->G,F->M->A.B*this->Amb->B);

    float Dr=0, Dg=0, Db=0, Er=0, Eg=0, Eb=0;

        for(std::vector<luz*>::iterator i=this->fontes_luminosas.begin();i!=fontes_luminosas.end();i++){

            luz* Luz = (*i);
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();
            float xDif = nFace.ProdutoEscalar(Fonte);

            Point v = this->Obs->Pos;  //Luz->P;
            v.operator -=(Pint);
            v.normalize();
            Point r = nFace;
            r.operator *=(2*xDif);
            r.operator -=(Fonte);
            r.normalize();
            float xEsp=v.ProdutoEscalar(r);
            xEsp=pow(xEsp,F->M->m);

            if(xDif > 0){
                Dr += Luz->F.R*xDif;
                Dg += Luz->F.G*xDif;
                Db += Luz->F.B*xDif;
            }
            if(xEsp > 0){
                Er += Luz->F.R*xEsp;
                Eg += Luz->F.G*xEsp;
                Eb += Luz->F.B*xEsp;
            }
        }

        //std::cout << "\n Dr: " << Dr<< ", Dg: " << Dg << ", Db: " << Db;
        for(std::vector<Spot*>::iterator i=this->fontes_spot.begin();i!=fontes_spot.end();i++){

            luz* Luz = (*i)->Luz;
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();

            Point *D = (*i)->Direcao;
            D->x = -D->x; D->y = -D->y; D->z = -D->z;
            float cos = Fonte.ProdutoEscalar(*D);

            if(cos>0){
                float Teta = acos (cos) * 180.0 / PI;
                std::cout << "Teta: " << Teta;
                if(Teta < (*i)->Abertura){

                    float R = Luz->F.R*cos;
                    float G = Luz->F.G*cos;
                    float B = Luz->F.B*cos;

                    float xDif = nFace.ProdutoEscalar(Fonte);

                    Point v = this->Obs->Pos;  //Luz->P;
                    v.operator -=(Pint);
                    v.normalize();
                    Point r = nFace;
                    r.operator *=(2*xDif);
                    r.operator -=(Fonte);
                    r.normalize();
                    float xEsp=v.ProdutoEscalar(r);
                    xEsp=pow(xEsp,F->M->m);

                    if(xDif > 0){
                        Dr += R*xDif;
                        Dg += G*xDif;
                        Db += B*xDif;
                    }
                    if(xEsp > 0){
                        Er += R*xEsp;
                        Eg += G*xEsp;
                        Eb += B*xEsp;
                    }
                }


            }



        }
        //std::cout << "\n Dr: " << Dr<< ", Dg: " << Dg << ", Db: " << Db;

        RGB D(F->M->D.R*(Dr),F->M->D.G*(Dg),F->M->D.B*(Db));
        RGB E(F->M->E.R*(Er),F->M->E.G*(Eg),F->M->E.B*(Eb));

        RayPix->R = A.R + D.R + E.R;
        RayPix->G = A.G + D.G + E.G;
        RayPix->B = A.B + D.B + E.B;
        RayPix->Normalize();

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
void Cenario::Prisma_Triangular_Uni(){
    Objeto *prism = new Objeto();
    prism->addPoint(-0.5,0,0.5);
    prism->addPoint(0.5,0,0.5);
    prism->addPoint(0.5,0,-0.5);
    prism->addPoint(-0.5,0,-0.5);
    prism->addPoint(-0.5,1,0);
    prism->addPoint(0.5,1,0);

    prism->addFace2(1,2,5);
    prism->addFace2(3,0,4);
    prism->addFace2(3,2,1);
    prism->addFace2(1,0,3);

    prism->addFace2(4,0,1);
    prism->addFace2(5,4,1);
    prism->addFace2(5,2,3);
    prism->addFace2(4,5,3);

    this->addObjeto(prism);

}
void Cenario::Prisma_Triangular_Uni2(Material *M1,Material *M2,Material *M3,Material *M4,Material *M5){
    Objeto *prism = new Objeto();
    prism->addPoint(-0.5,0,0.5);
    prism->addPoint(0.5,0,0.5);
    prism->addPoint(0.5,0,-0.5);
    prism->addPoint(-0.5,0,-0.5);
    prism->addPoint(-0.5,1,0);
    prism->addPoint(0.5,1,0);


    prism->addFace(3,2,1, M1);
    prism->addFace(1,0,3, M1);
    prism->addFace(3,0,4, M2);
    prism->addFace(1,2,5, M3);
    prism->addFace(4,0,1, M4);
    prism->addFace(5,4,1, M4);
    prism->addFace(5,2,3, M5);
    prism->addFace(4,5,3, M5);

    this->addObjeto(prism);

}
