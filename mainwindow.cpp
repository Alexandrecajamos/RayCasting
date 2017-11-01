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


    Point Eye(25,25,25);
    Point LA(0,0,0);
    Point VUp(0,50,0);

    Observador *Obs = new Observador(Eye,LA,VUp);
    float** WC = Obs->Word_Cam();
    Camera *Cam = new Camera(0.5,0.5,-0.7,sizeX,sizeY,*Obs);
    Cenario* scene = new Cenario(Obs, Cam);

    RGB C(0.5,0.5,0.5);
    RGB C2(0.3295,0.5451,0.3295);
    RGB C3(0.5450,0.3529,0.1686);
    RGB C5(0.5,0.5,0.5);

    Material *M = new Material(C,C,C,0.5);
    Material *M2 = new Material(C2,C2,C2,0.5);
    Material *M3 = new Material(C3,C3,C3,0.5);
    Material *M5 = new Material(C5,C5,C5,0.5);
    Material *M6 = new Material(C2,C3,C5,0.5);

    /*Tetraedro Regular
    Objeto *obj = new Objeto();
    obj->addPoint(0,0,0);
    obj->addPoint(7.071,0,0);
    obj->addPoint(0,7.071,0);
    obj->addPoint(0,0,7.071);
    obj->addFace(0,1,2,M);
    obj->addFace(3,0,2,M2);
    obj->addFace(0,3,1,M3);
    obj->addFace(3,1,2, M4);
    */

    Objeto *cubo = new Objeto();

    cubo->addPoint(-0.5,-0.5,0.5);
    cubo->addPoint(0.5,-0.5,0.5);
    cubo->addPoint(0.5,-0.5,-0.5);
    cubo->addPoint(-0.5,-0.5,-0.5);
    cubo->addPoint(-0.5,0.5,0.5);
    cubo->addPoint(0.5,0.5,0.5);
    cubo->addPoint(0.5,0.5,-0.5);
    cubo->addPoint(-0.5,0.5,-0.5);

    cubo->addFace(0,3,1,M);
    cubo->addFace(1,3,2,M);
    cubo->addFace(4,0,1,M2);
    cubo->addFace(1,5,4,M2);
    cubo->addFace(5,1,2,M3);
    cubo->addFace(2,6,5,M3);
    cubo->addFace(6,2,3,M3);
    cubo->addFace(3,7,6,M3);
    cubo->addFace(3,0,4,M5);
    cubo->addFace(4,7,3,M5);
    cubo->addFace(4,5,7,M6);
    cubo->addFace(5,6,7,M6);

    scene->addObjeto(cubo);

    Operacoes Op;
    float v[4]={20,20,0.5,1};
    float **A = Op.Escala(4,v);//Op.Rotacao(3,1,90);
    float **R = Op.Rotacao(3,1,-35);

    scene->Objetos.at(0)->Transforoma(A);
    scene->Objetos.at(0)->Transforoma(R);
    scene->Word_Cam(WC);

    RGB RL(0.7,0.7,0.7);
    Point *P = new Point(50,0,50);
    luz* Luz = new luz(RL,P);
    scene->addFonte(Luz);

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
