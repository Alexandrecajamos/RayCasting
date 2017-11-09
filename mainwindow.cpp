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

    int sizeX = 650;
    int sizeY = 650;


    //initialize random seed
    srand (time(NULL));

    Point Eye(5,0,0);
    Point LA(0,0,0);
    Point VUp(0,50,0);

    Observador *Obs = new Observador(Eye,LA,VUp);
    Camera *Cam = new Camera(0.5,0.5,-0.7,sizeX,sizeY,*Obs);
    RGB* Bg = new RGB(0.22,0.22,0.22);//(0.73,1,1);
    RGB* Amb = new RGB(0.2,0.2,0.2);
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

    float** WC = scene->Obs->Word_Cam();

    scene->Word_Cam(WC);



}
