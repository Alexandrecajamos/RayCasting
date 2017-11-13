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

    int sizeX = 1000;
    int sizeY = 1000;
    int A,B,C,D,E,F;
    A=7; B = 8; C = 5; D = 1; E = 0; F = 4;

    //initialize random seed
    srand (time(NULL));

    Point Eye((A+D+2)*4,(B+E+3)*4,(C+F+5)*4);
    Point LA(D,E,F);
    Point AVUp(A,B,C);


    Observador *Obs = new Observador(Eye,LA,AVUp);
    Camera *Cam = new Camera(10,10,-4,sizeX,sizeY,*Obs);

    RGB* Bg = new RGB(0.22,0.22,0.22);
    RGB* Amb = new RGB(A/10,B/10,C/10);
    Cenario* scene = new Cenario(Obs, Cam, Amb, Bg);
    float** WC = scene->Obs->Word_Cam();
    Operacoes Oper;
    Oper.ImprimeMat(4,4,WC);

    RGB RL(0.8,0.6,0.4);
    Point *P = new Point(10,10,-20);
    scene->addFonte2(P,RL);
    scene->Word_Cam(WC);

    //MontaCena(scene);

    float i=(A+B+C);float j=(D+E+F);
    float Yi= (scene->Cam->h/2)-(scene->Cam->DY/2)-(i*scene->Cam->DY);
    float Xj = (-scene->Cam->w/2)+(scene->Cam->DX/2)+(j*scene->Cam->DX);
    Point px(Xj,Yi,scene->Cam->d);

    px.ImpPoint();

    float t = 20;
    std::cout<<" \nTeste T: " << t;


    if(t!=-1 && t>1){
        Point Pint=px;
        Pint.normalize();
        Pint.operator *=(t);
        Pint.ImpPoint();
        Point nFace(5,5,-4);
        nFace.operator -=(Pint);
        nFace.normalize();

        RGB K(D/10,E/10,F/10);
        Material *MF = new Material(K,K,K,F);

        RGB *Ilm = scene->Ilm_Pint(Pint,nFace,MF);

        std::cout <<"\nIluminacao Pint: " << Ilm->R << ", " << Ilm->G <<", " << Ilm->B<< ";";


        Operacoes Op;
        std::cout<< "\nUltima questão\ns";
        Objeto *O = new Objeto();
        O->addPoint(-5,-5,-4);
        O->addPoint(5,5,-4);
        O->addPoint(0,5,-20);
        O->addPoint(Pint.x, Pint.y,Pint.z);
        O->addFace2(0,1,2);
        O->ImpPoints();
        Point tr = *O->points.at(0);
        float vT[4] = {(0-tr.x),(0-tr.y),(0-tr.z),1};
        float** T = Op.Translacao(4,vT);
        Point n = O->faces.at(0)->calcNormal();
        n.normalize();
        Point *N = new Point(n.x, n.y, n.z);
        float** vEs= Op.VetorColuna(N);
        float** Esp = Op.EspelhoArb(4,vEs);
        float *v2 = Op.Vetor(tr);
        v2[3]=1;
        float** T2 = Op.Translacao(4,v2);
        float** Tran = Op.mult(4,4,4,T2,Esp);
        Tran = Op.mult(4,4,4,Tran,T);
        O->Transforoma(Tran);
        Op.ImprimeMat(4,4,Tran);
        O->ImpPoints();









    }


   // Render(sizeX,sizeY, scene);

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
                if(i==j && j==325)
                     std::cout <<"\nIluminacao Pint: " << print->R << ", " << print->G <<", " << print->B<< ";";

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
