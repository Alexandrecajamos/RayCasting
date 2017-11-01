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

    Point Eye(25,25,25);
    Point LA(0,0,0);
    Point VUp(0,25,0);
    Observador *Obs = new Observador(Eye,LA,VUp);
    Camera *Cam = new Camera(0.5,0.5,-0.7,sizeX,sizeY,*Obs);
    Cenario scene(Obs, Cam);

    Objeto *obj = new Objeto();
    obj->addPoint(0,0,0);
    obj->addPoint(7.071,0,0);
    obj->addPoint(0,7.071,0);
    obj->addPoint(0,0,7.071);


    RGB C(0.5,0.5,0.5);
    RGB C2(0.8,0.01,0.01);
    RGB C3(0.01,0.8,0.01);
    RGB C4(0.01,0.01,0.8);

    Material *M = new Material(C,C,C,0.5);
    Material *M2 = new Material(C2,C2,C2,0.5);
    Material *M3 = new Material(C3,C3,C3,0.5);
    Material *M4 = new Material(C4,C4,C4,0.5);

    obj->addFace(0,1,2,M);
    obj->addFace(3,0,2,M2);
    obj->addFace(0,3,1,M3);
    obj->addFace(3,1,2, M4);

    scene.addObjeto(obj);

    Operacoes Op;
    float **A = Op.Rotacao(3,0,90);
    float** WC = Obs->Word_Cam();

    scene.Objetos.at(0)->Transforoma(A);
    scene.Word_Cam(WC);
    //obj->Transforoma(WC);
    obj->calc_Esfera();

    RGB RL(0.7,0.7,0.7);
    Point *P = new Point(-200,35,175);
    luz* Luz = new luz(RL,P);
    scene.addFonte(Luz);
    //Ray Casting :

    for( int i=0; i<sizeX; i++)
    {

        float Yi= (scene.Cam->h/2)-(scene.Cam->DY/2)-(i*scene.Cam->DY);
        for( int j=0; j<sizeY; j++ )
        {
            float Xj = (-scene.Cam->w/2)+(scene.Cam->DX/2)+(j*scene.Cam->DX);
            float t=0;
            Point px(Xj,Yi,scene.Cam->d);
            int iFace;
            int iObj;
            t = scene.Inter(px,iObj,iFace);

            if(t != -1 && t>1){

                Point Pint = px;
                Pint.operator *=(t);

                Face* F = scene.Objetos.at(iObj)->faces.at(iFace); //obj->faces.at(ind);

                Point nFace = F->calcNormal();
                nFace.normalize();
                Point Fonte = (*Luz->P);
                // Já que não estou transformando a posição da luz W_to_Cam;
                Fonte.operator -=(Pint);
                Fonte.normalize();
                float xDif = nFace.ProdutoEscalar(Fonte);

                Point v =(*scene.fontes_luminosas.at(0)->P);
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

                float rrr = A.R + D.R + E.R;
                float ggg = A.G + D.G + E.G;
                float bbb = A.B + D.B + E.B;
                RGB print(rrr,ggg,bbb);
                print.Normalize();

                image.setPixel( i, j, qRgb(print.R*255, print.G*255, print.B*255)); //54 54 54
            }else
                image.setPixel( i, j, qRgb(10, 10, 10)); //54 54 54

        }
    }


    QGraphicsScene * graphic = new QGraphicsScene( this );

    graphic->addPixmap( QPixmap::fromImage( image ) );

    ui->graphicsView->setScene(graphic);
}
