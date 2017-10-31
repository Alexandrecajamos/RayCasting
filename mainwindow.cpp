#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "point.h"
#include "material.h"
#include "face.h"
#include "rgb.h"
#include "observador.h"
#include "operacoes.h"
#include "objeto.h"
#include "camera.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int sizeX = 400;
    int sizeY = 400;

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

    Point Eye(7,1.8,2.5);
    Point LA(5,0.75,2.5);
    Point VUp(5,1.75,2.5);
    Observador Obs(Eye,LA,VUp);
    Camera Cam(0.5,0.5,-0.7,sizeX,sizeY,Obs);

    Objeto *obj = new Objeto();
    obj->addPoint(4,0,3);
    obj->addPoint(4,0,2);
    obj->addPoint(4,1,2.5);
    RGB C(0.5,1,0);
    Material M(C,C,C,2);
    obj->addFace(0,1,2,M);

    Operacoes Op;
    float **A = Op.Rotacao(3,2,15);
    float** WC = Obs.Word_Cam();

    obj->Transforoma(A);

    obj->Transforoma(WC);
    obj->calc_Esfera();


    //Ray Casting :

    for( int i=0; i<sizeX; i++)
    {

        float Yi= (Cam.h/2)-(Cam.DY/2)-(i*Cam.DY);
        for( int j=0; j<sizeY; j++ )
        {
            float Xj = (-Cam.w/2)+(Cam.DX/2)+(j*Cam.DX);
            float t=0;
            Point px(Xj,Yi,Cam.d);
            int ind;
            t = obj->Inter(px, &ind);//obj->faces.at(0)->Inter(px);
            //Point n = obj->faces.at(ind)->calcNormal();

            if(t != -1 && t>0.7){
                image.setPixel(i, j, qRgb(obj->faces.at(0)->M.A.R* 255, obj->faces.at(0)->M.D.G * 255, obj->faces.at(0)->M.E.B* 255) );

            }else
                image.setPixel( i, j, qRgb(54, 54, 54));

        }
    }


    QGraphicsScene * graphic = new QGraphicsScene( this );

    graphic->addPixmap( QPixmap::fromImage( image ) );

    ui->graphicsView->setScene(graphic);
}
