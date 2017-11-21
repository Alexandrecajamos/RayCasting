#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "v3.h"
#include "material.h"
#include "face.h"
#include "rgb.h"
#include "observador.h"
#include "operacoes.h"
#include "objeto.h"
#include "camera.h"
#include "luz.h"
#include "cenario.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int sizeX = 800;
    int sizeY = 800;
    float W = 8;
    float H = 8;
    float d = 3;

    float A,B,C,D,E,F;
    A=7; B = 8; C = 5; D = 1; E = 0; F = 4;
    //A=4;  B=0; C=0; D=1;  E=5;  F=7;
    //initialize random seed
    srand (time(NULL));
    float L = A+B+C+D+E+F;
    float LR3 =(L*std::sqrt(3));
    float LR6s6 = (L* std::sqrt(6))/6;
    float LR6s12 = (L* std::sqrt(6))/12;

    RGB Ka(A/50,B/50,C/50);
    std::cout <<"\nIluminacao Amb: " << Ka.R << ", " << Ka.G <<", " << Ka.B<< ";";

    RGB Kds(3*Ka.R,3*Ka.G,3*Ka.B);

    std::cout <<"\nIluminacao Amb: " << Kds.R << ", " << Kds.G <<", " << Kds.B<< ";";

    Material* MF = new Material(Ka,Kds,Kds,1);


    Point Eye(A-5,B+L,LR6s6);//((A+D+2)*4,(B+E+3)*4,(C+F+5)*4);
    std::cout << "\nEye: ";
    Eye.ImpPoint();
    Point LA((A+10)+(L/2),(B+5)+(LR3/6),0);
    std::cout << "\nLa: ";
    LA.ImpPoint();
    Point AVUp((A+10)+(L/2),(B+5)+(LR3/6),LR6s6);
    std::cout << "\nAvup: ";
    AVUp.ImpPoint();
    Operacoes Op;
    Observador *Obs = new Observador(Eye,LA,AVUp);
    Camera *Cam = new Camera(W,H,-d,sizeX,sizeY,*Obs);

    RGB* Bg = new RGB(0.22,0.22,0.22);
    RGB* Amb = new RGB(0.4, 0.4, 0.4);

    //std::cout <<"\nIluminacao Amb: " << Amb->R << ", " << Amb->G <<", " << Amb->B<< ";";

    Cenario* scene = new Cenario(Obs, Cam, Amb, Bg);
    //Tetraedro Regular
        Objeto *obj = new Objeto();
        obj->addPoint(A+10,B+5,0);
        obj->addPoint((A+10)+L,B+5,0);
        obj->addPoint((A+10)+(L/2),(B+5)+(LR3/2),0);
        obj->addPoint((A+10)+(L/2),(B+5)+(LR3/6),LR6s6);

        obj->addFace(2,1,0,MF);
        obj->addFace(0,1,3,MF);
        obj->addFace(1,2,3,MF);
        obj->addFace(0,3,2,MF);

        obj->ImpPoints();
    Point *px = new Point(obj->points.at(3)->x,obj->points.at(3)->y, obj->points.at(3)->z-LR6s12);

    scene->addObjeto(obj);

    float** CW = scene->Obs->Cam_Word();
    float** WC = scene->Obs->Word_Cam();

    std::cout << "\nVetor i";
    Obs->i.ImpPoint();
    std::cout << "\nVetor j";
    Obs->j.ImpPoint();
    std::cout << "\nVetor K";
    Obs->k.ImpPoint();

    std::cout << "\nMatriz Camera para mundo";
    Op.ImprimeMat(4,4,CW);
    std::cout << "\nMatriz Mundo para camera";
    Op.ImprimeMat(4,4,WC);

    std::cout << "\n\nIluminacao da Luz pontual:";
    RGB RL(0.7,0.7,0.7);
    std::cout << "\n" << RL.R << ", " << RL.G << ", " << RL.B;

    std::cout << "\nPosicao da Luz:";
    Point *P = new Point(A+10,B+L,2*L);

    scene->addFonte2(P,RL);
    std::cout << "\n\n\nTransformando Cenario em coord. de câmera\n";

    scene->Word_Cam(WC);

    std::cout << "\nObjeto em coord. de câmera";

    obj->ImpPoints();
    //scene->Objetos.at(0)->ImpPoints();

    std::cout << "\nEye em coord. de câmera";
    scene->Obs->Pos.ImpPoint();


    std::cout << "\nFonte em coord. de câmera";
    scene->fontes_luminosas.at(0)->P->ImpPoint();

    //MontaCena(scene);

    //float i=2;float j=4;
    //float Yi= (scene->Cam->h/2)-(scene->Cam->DY/2)-(i*scene->Cam->DY);
    //float Xj = (-scene->Cam->w/2)+(scene->Cam->DX/2)+(j*scene->Cam->DX);
    std::cout << "\nPij";

    px->ImpPoint();

    float** Px = Op.VetorColuna(px);
    float** pij = Op.mult(4,4,1,WC,Px);

    //std::cout << "\nVetor Pij sendo i: "<< i << ",j: " << j;

    //Pij.normalize();
    //Pij.ImpPoint();
/*
    int cont = 0;
    for(std::vector<Face*>::iterator i = obj->faces.begin(); i!= obj->faces.end(); i++){
        //float x = (*i)->Inter(Pint);
        Point Pij(pij[0][0],pij[1][0],pij[2][0]);
        Pij.normalize();
        Point n = (*i)->calcNormal();
        n.normalize();
        Point P1((*i)->P1->x, (*i)->P1->y, (*i)->P1->z);
        float np1 = n.ProdutoEscalar(P1);
        float nPij =n.ProdutoEscalar(Pij);
        if(nPij>0){
        float x = np1/nPij;
        std::cout << "\n Face : " << cont;
        std::cout << "\nt = " << x;
        Pij.normalize();
        Pij.operator *=(x);
        RGB* Ilm = scene->Ilm_Pint(Pij,n,MF);
        std::cout <<"\nIluminacao Pint: " << Ilm->R << ", " << Ilm->G <<", " << Ilm->B<< ";";

        }
        cont++;
 }
    */
    //t=scene->Inter(Pij,iFace,iObj);
    //std::cout << "\n T = " << t;
    Point Pij(pij[0][0],pij[1][0],pij[2][0]);
    Pij.ImpPoint();
    RGB *Ilm = scene->Ray_Pix_Ilm(Pij);

    std::cout <<"\nIluminacao Pint: " << Ilm->R << ", " << Ilm->G <<", " << Ilm->B<< ";";

    //float t = 0;
    //std::cout<<" \nT: " << t;

    /*
    if(t!=-1 && t>1){

        Point Pint;
        Pint.normalize();
        //Pint.operator *=(t);
         std::cout << "\nPint:";
        Pint.ImpPoint();

        Point nFace(-4,4,-3);
        nFace.operator -=(Pint);
        nFace.normalize();
         std::cout << "\nNormal a Face:";
        nFace.ImpPoint();

        RGB *Ilm = scene->Ilm_Pint(Pint,nFace,MF);

        std::cout <<"\nIluminacao Pint: " << Ilm->R << ", " << Ilm->G <<", " << Ilm->B<< ";";

    }
*/


    //Render(sizeX,sizeY, scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Render(int sizeX, int sizeY,Cenario *scene){

    QImage image = QImage( sizeX, sizeY, QImage::Format_RGB32 );

    //Ray Casting :

    for( int i=0; i<sizeX; i++)
    {

        float Yi= (scene->Cam->h/2)-(scene->Cam->DY/2)-(i*scene->Cam->DY);
        for( int j=0; j<sizeY; j++ )
        {
            float Xj = (-scene->Cam->w/2)+(scene->Cam->DX/2)+(j*scene->Cam->DX);
            Point px(Xj,Yi,scene->Cam->d);

                RGB* print = scene->Ray_Pix_Ilm(px);
                image.setPixel( i, j, qRgb(print->R*255, print->G*255, print->B*255));
                //if(i==j && j==325)
                     //std::cout <<"\nIluminacao Pint: " << print->R << ", " << print->G <<", " << print->B<< ";";

        }
    }


    QGraphicsScene * graphic = new QGraphicsScene( this );

    graphic->addPixmap( QPixmap::fromImage( image ) );

    ui->graphicsView->setScene(graphic);
}
void MainWindow::MontaCena(Cenario *scene){


    /*Tetraedro Regular
    Objeto *obj = new Objeto();
    obj->addPoint(0,0,0);
    obj->addPoint(7.071,0,0);
    obj->addPoint(0,7.071,0);
    obj->addPoint(0,0,7.071);
    obj->addFace(0,1,2,M);
    obs->addFace(3,0,2,M2);
    obj->addFace(0,3,1,M3);
    obj->addFace(3,1,2, M4);
    */
/*
    RGB C(0.5,0.5,0.5);
    RGB C2(0.3295,0.5451,0.3295);
    RGB C3(0.5450,0.3529,0.1686);
    RGB C5(0.5,0.5,0.5);

  //  Material *M1 = new Material(C,C,C,0.5);
    Material *M2 = new Material(C2,C2,C2,0.5);
    Material *M3 = new Material(C3,C3,C3,0.5);
  //  Material *M5 = new Material(C5,C5,C5,0.5);
   // Material *M6 = new Material(C2,C3,C5,0.5);
    scene->CuboUni2(M3,M2,M3,M3,M3,M3);
*/

    RGB C3(0.5450,0.3529,0.1686);
    Material *M3 = new Material(C3,C3,C3,0.5);
    //Operacoes Op;
    scene->CuboUni2(M3,M3,M3,M3,M3,M3);

    //scene->Prisma_Triangular_Uni2(M3, M3,M3,M3,M3);
   // float v[4]={10,10,10,1};
    //float **A = Op.Escala(4,v);
   // scene->Objetos.at(0)->Transforoma(A);

    RGB RL(1,0,0);
    Point *P = new Point(5,5,5);
    scene->addFonte2(P,RL);

    RGB L2(0,1,0);
    Point *P2 = new Point(5,5,5);
    scene->addFonte2(P2, L2);

    RGB L3(0,0,1);
    Point *P3 = new Point(5,5,5);
    scene->addFonte2(P3, L3);

    RGB L4(1,1,1);
    Point *P4 = new Point(5,5,5);
    Point *Dir = new Point(0,0,0);
    Dir->operator -=(*P4);
    Dir->normalize();
    luz *L = new luz(L4, P4);
    Spot *Sp = new Spot(L,Dir,60);
    scene->addSpot(Sp);

    float** WC = scene->Obs->Word_Cam();
    scene->Word_Cam(WC);



}
