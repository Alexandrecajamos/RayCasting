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

    int sizeX = 200;
    int sizeY = 200;
    float W = 0.5;
    float H = 0.5;
    float d = 2;

    Point Eye(150,400,150);
    Point LA(50,5,50);
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

    bool solo = true;
    bool pistas = true;
    bool casas = true;
    bool telhados = true;
    bool arvores = true;

    RGB RL(0.6,0.6,0.6);
    Point *P = new Point(100,80,100);
    scene->addFonte2(P,RL);

    Operacoes Opr;

    //RGB Te(0.5054,0.2705,0.0745);
    RGB G(0.4196,0.5568,0.1372);
    RGB Pis(0.3235, 0.3823, 0.4450);
    RGB Arv(0.4196,0.7568,0.1372);
    RGB C1(0.1843, 0.3098, 0.3098);
    RGB C2(0.8235, 0.4118, 0.1176);
    RGB C3(0.8235, 0.7059, 0.5490);
    RGB C4(0.4120, 0.2529, 0.8039);
    RGB C5(0.9569, 0.6431, 0.3765);
    RGB C6(0.9608, 0.9608, 0.8627);
    RGB Az(72/255,118/255,1); //72 118 255

    Material *Casa1 = new Material(C1,C1,C1,1);
    Material *Casa2 = new Material(C2,C2,C2,1);
    Material *Casa3 = new Material(C3,C3,C3,1);
    Material *Casa4 = new Material(C4,C4,C4,1);
    Material *Casa5 = new Material(C5,C5,C5,1);
    Material *Casa6 = new Material(C6,C6,C6,1);


    Material* Telha = new Material(C6,C6,C6,1);//(Te,Te,Te,1);
    Material* Telha1 = new Material(C1,C1,C1,1);
    Material* Telha2 = new Material(Az,Az,Az,1);


    Material *Grama = new Material(G,G,G,1);
    Material *Pista = new Material(Pis,Pis,Pis,1);
    Material *Arvore = new Material(Arv,Arv,Arv,1);

    float **E, **T, **MT;
    int iobj=0;
    float ve[4],vt[4];
    ve[3] = 1; vt[3]=1;





    if(solo){
        scene->CuboUni3(Grama);
        ve[0] = 100;ve[1] = 0.8; ve[2] = 100;
        E = Opr.Escala(4, ve);
        scene->Objetos.at(iobj)->Transforoma(E);
        iobj++;
    }
    if(pistas){
        scene->CuboUni3(Pista);
        ve[0]=10;ve[1]=0.2;ve[2]=55;
        vt[0]=45;vt[1]=0.8;vt[2]=0;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Pista);
        ve[0]=100;ve[1]=0.2;ve[2]=10;
        vt[0]=0;vt[1]=0.8;vt[2]=55;
        E = Opr.Escala(4,ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Pista);
        ve[0]=30;ve[1]=0.2;ve[2]=5;
        vt[0]=55;vt[1]=0.8;vt[2]=25;
        E = Opr.Escala(4,ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Pista);
        ve[0]=15;ve[1]=0.2;ve[2]=4;
        vt[0]=30;vt[1]=0.8;vt[2]=28;
        E = Opr.Escala(4,ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;
    }
    if(casas){


        scene->CuboUni3(Casa1);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=70;vt[1]=0.8;vt[2]=5;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa2);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=70;vt[1]=0.8;vt[2]=30;
        T = Opr.Translacao(4,vt);
        E = Opr.Escala(4, ve);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa3);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=75;vt[1]=0.8;vt[2]=70;
        T = Opr.Translacao(4,vt);
        E = Opr.Escala(4, ve);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa4);
        ve[0]=20;ve[1]=20;ve[2]=20;
        vt[0]=50;vt[1]=0.8;vt[2]=70;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa5);
        ve[0]=20;ve[1]=3;ve[2]=15;
        vt[0]=21;vt[1]=0.8;vt[2]=75;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa5);
        ve[0]=20;ve[1]=20;ve[2]=20;
        vt[0]=2;vt[1]=0.8;vt[2]=70;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa6);
        ve[0]=25;ve[1]=3;ve[2]=20;
        vt[0]=5;vt[1]=0.8;vt[2]=20;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa6);
        ve[0]=15;ve[1]=3;ve[2]=15;
        vt[0]=5;vt[1]=0.8;vt[2]=5;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

    }
    if(telhados){
        scene->Prisma_Triangular_Uni3(Telha);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=70;vt[1]=2.8;vt[2]=5;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha2);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=70;vt[1]=2.8;vt[2]=30;
        T = Opr.Translacao(4,vt);
        E = Opr.Escala(4, ve);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha1);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=75;vt[1]=2.8;vt[2]=70;
        T = Opr.Translacao(4,vt);
        E = Opr.Escala(4, ve);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha1);
        ve[0]=20;ve[1]=3;ve[2]=20;
        vt[0]=50;vt[1]=20.7;vt[2]=70;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;


        scene->Prisma_Triangular_Uni3(Telha2);
        ve[0]=20;ve[1]=2;ve[2]=15;
        vt[0]=21;vt[1]=3.8;vt[2]=75;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha2);
        ve[0]=20;ve[1]=3;ve[2]=20;
        vt[0]=2;vt[1]=20.8;vt[2]=70;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha1);
        ve[0]=25;ve[1]=3;ve[2]=20;
        vt[0]=5;vt[1]=3.8;vt[2]=20;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha1);
        ve[0]=15;ve[1]=3;ve[2]=15;
        vt[0]=5;vt[1]=3.8;vt[2]=5;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;


    }
    if(arvores){
        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=8;vt[1]=0.8;vt[2]=42;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=14;vt[1]=0.8;vt[2]=42;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=40;vt[1]=0.8;vt[2]=42;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=8;vt[1]=0.8;vt[2]=47;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=14;vt[1]=0.8;vt[2]=47;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=40;vt[1]=0.8;vt[2]=47;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;


        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=8;vt[1]=0.8;vt[2]=52;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=14;vt[1]=0.8;vt[2]=52;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=40;vt[1]=0.8;vt[2]=52;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;


        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=60;vt[1]=0.8;vt[2]=42;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=60;vt[1]=0.8;vt[2]=47;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=60;vt[1]=0.8;vt[2]=52;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;


        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=72;vt[1]=0.8;vt[2]=75;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=72;vt[1]=0.8;vt[2]=80;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=7;ve[2]=1.5;
        vt[0]=72;vt[1]=0.8;vt[2]=85;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;




        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=2;ve[2]=1.5;
        vt[0]=60;vt[1]=0.8;vt[2]=5;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=2;ve[2]=1.5;
        vt[0]=60;vt[1]=0.8;vt[2]=10;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Arvore);
        ve[0]=1.5;ve[1]=2;ve[2]=1.5;
        vt[0]=60;vt[1]=0.8;vt[2]=15;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;
    }



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
