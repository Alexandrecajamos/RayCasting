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

    Render(sizeX,sizeY);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Render(int sizeX, int sizeY){

    QImage image = QImage( sizeX, sizeY, QImage::Format_RGB32 );

    Point Eye(50,50,50);
    Point LA(0,0,0);
    Point VUp(0,50,0);

    Observador *Obs = new Observador(Eye,LA,VUp);
    float** WC = Obs->Word_Cam();
    Camera *Cam = new Camera(0.5,0.5,-0.7,sizeX,sizeY,*Obs);
    Cenario scene(Obs, Cam);

    RGB C(0.5,0.5,0.5);
    RGB C2(0.8,0.01,0.01);
    RGB C3(0.01,0.8,0.01);
    RGB C4(0.01,0.01,0.8);
    RGB C5(0.5,0.5,0.5);

    Material *M = new Material(C,C,C,0.5);
    Material *M2 = new Material(C2,C2,C2,0.5);
    Material *M3 = new Material(C3,C3,C3,0.5);
    Material *M4 = new Material(C4,C4,C4,0.5);
    Material *M5 = new Material(C5,C5,C5,0.5);

    Objeto *obj = new Objeto();
    obj->addPoint(0,0,0);
    obj->addPoint(7.071,0,0);
    obj->addPoint(0,7.071,0);
    obj->addPoint(0,0,7.071);
    obj->addFace(0,1,2,M);
    obj->addFace(3,0,2,M2);
    obj->addFace(0,3,1,M3);
    obj->addFace(3,1,2, M4);
    scene.addObjeto(obj);

    Objeto *obj2 = new Objeto();
    obj2->addPoint(0,0,0);
    obj2->addPoint(10,0,0);
    obj2->addPoint(0,10,0);
    obj2->addPoint(0,0,10);
    obj2->addFace(1,0,2,M3);
    obj->addFace(3,0,2,M4);
    obj->addFace(0,3,1,M2);
    obj->addFace(3,1,2,M5);
    scene.addObjeto(obj2);

    Operacoes Op;
    float **A = Op.Rotacao(3,1,90);
    float **A2 = Op.Rotacao(3,2,45);
    scene.Objetos.at(0)->Transforoma(A);
    scene.Objetos.at(1)->Transforoma(A2);

    scene.Word_Cam(WC);

    RGB RL(0.7,0.7,0.7);
    Point *P = new Point(50,0,50);
    luz* Luz = new luz(RL,P);
    scene.addFonte(Luz);
    //Ray Casting :

    for( int i=0; i<sizeX; i++)
    {

        float Yi= (scene.Cam->h/2)-(scene.Cam->DY/2)-(i*scene.Cam->DY);
        for( int j=0; j<sizeY; j++ )
        {
            float Xj = (-scene.Cam->w/2)+(scene.Cam->DX/2)+(j*scene.Cam->DX);
            Point px(Xj,Yi,scene.Cam->d);
            RGB* print = scene.Ray_Pix_Ilm(px);
            image.setPixel( i, j, qRgb(print->R*255, print->G*255, print->B*255));

        }
    }


    QGraphicsScene * graphic = new QGraphicsScene( this );

    graphic->addPixmap( QPixmap::fromImage( image ) );

    ui->graphicsView->setScene(graphic);
}
