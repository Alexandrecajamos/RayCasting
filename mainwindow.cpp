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
    obj->addPoint(-0.5,-0.5045,-5.5020);
    obj->addPoint(0.5,-0.4852,-5.7969);
    obj->addPoint(0,1.0034,-5.2977);
    RGB C(0.5,1,0);
    Material M(C,C,C,2);
    obj->addFace(0,1,2,M);

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
            t = obj->faces.at(0)->Inter(px);
            if(t != -1 && t>1)
                image.setPixel(i, j, qRgb(obj->faces.at(0)->M.A.R* 255, obj->faces.at(0)->M.D.G * 255, obj->faces.at(0)->M.E.B* 255) );
            else
                image.setPixel( i, j, qRgb(54, 54, 54));

        }
    }


    QGraphicsScene * graphic = new QGraphicsScene( this );

    graphic->addPixmap( QPixmap::fromImage( image ) );

    ui->graphicsView->setScene(graphic);
}
