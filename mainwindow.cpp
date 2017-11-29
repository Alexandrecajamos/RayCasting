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

    int sizeX = 500;
    int sizeY = 500;
    float W = 0.5;
    float H = 0.5;
    float d = 3;

    Point Eye(50,1000,50);
    Point LA(50,2,50);
    Point AVUp(50,0,0);

    Observador *Obs = new Observador(Eye,LA,AVUp);
    Camera *Cam = new Camera(W,H,-d,sizeX,sizeY,*Obs);

    RGB* Bg = new RGB(0.250980, 0.87843137, 0.815686275);
    RGB* Amb = new RGB(0.4, 0.4, 0.4);

    Cenario* scene = new Cenario(Obs, Cam, Amb, Bg);
    MontaCena(scene);

    Render(sizeX,sizeY, scene);

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

    Operacoes Opr;



    RGB G(0.4196,0.5568,0.1372);
    RGB Pis(0.3235, 0.3823, 0.4450);
    RGB C1(0.6,0.2,0.2);
    Material *Grama = new Material(G,G,G,1);
    Material *Pista = new Material(Pis,Pis,Pis,1);
    Material *Casa1 = new Material(C1,C1,C1,1);

    scene->CuboUni3(Grama);
    float ve[4] = {100,0.8,100,1};
    float** E = Opr.Escala(4, ve);
    scene->Objetos.at(0)->Transforoma(E);

    scene->CuboUni3(Pista);
    float ve2[4]= {10,0.2,100,1};
    E = Opr.Escala(4, ve2);
    //scene->Objetos.at(1)->Transforoma(E);
    float vt2[4] = {45,0.8,0,1};
    float **T = Opr.Translacao(4,vt2);
    T = Opr.mult(4,4,4,T,E);
    scene->Objetos.at(1)->Transforoma(T);

    scene->CuboUni3(Pista);
    float ve3[4]= {100,0.2,10};
    E = Opr.Escala(4,ve3);
    scene->Objetos.at(2)->Transforoma(E);
    float vt3[4]= {0,0.8,55,1};
    T = Opr.Translacao(4,vt3);
    //T = Opr.mult(4,4,4,T,E);
    scene->Objetos.at(2)->Transforoma(T);

    scene->CuboUni3(Casa1);
    float ve4[4]= {20,2,20,1};
    E = Opr.Escala(4, ve4);
    //scene->Objetos.at(3)->Transforoma(E);
    float vt4[4] = {70,0.8,5,1};
    T = Opr.Translacao(4,vt4);
    T = Opr.mult(4,4,4,T,E);
    scene->Objetos.at(3)->Transforoma(T);

    scene->Prisma_Triangular_Uni3(Casa1);
    vt4[1]=2.8;
    T = Opr.Translacao(4,vt4);
    T = Opr.mult(4,4,4,T,E);
    scene->Objetos.at(4)->Transforoma(T);
    //scene->Objetos.at(4)->ImpPoints();

    scene->CuboUni3(Casa1);
    vt4[1]=0.8;
    vt4[2] = 30;
    T = Opr.Translacao(4,vt4);
    T = Opr.mult(4,4,4,T,E);
    scene->Objetos.at(5)->Transforoma(T);

    scene->Prisma_Triangular_Uni3(Casa1);
    vt4[1]=2.8;
    T = Opr.Translacao(4,vt4);
    T = Opr.mult(4,4,4,T,E);
    scene->Objetos.at(6)->Transforoma(T);

    RGB RL(0.8,0.8,0.8);
    Point *P = new Point(50,80,50);
    scene->addFonte2(P,RL);
/*
    RGB L2(0,1,0);
    Point *P2 = new Point(50,80,50);
    scene->addFonte2(P2, L2);

    RGB L3(0,0,1);
    Point *P3 = new Point(50,80,50);
    scene->addFonte2(P3, L3);


    RGB L4(1,1,1);
    Point *P4 = new Point(50,50,50);
    Point *Dir = new Point(50,5,50);
    Dir->operator -=(*P4);
    Dir->normalize();
    luz *L = new luz(L4, P4);
    Spot *Sp = new Spot(L,Dir,60);
    scene->addSpot(Sp);
*/

    float** WC = scene->Obs->Word_Cam();
    scene->Word_Cam(WC);



}
