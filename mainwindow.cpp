#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transformacoes.h"
#include "QImage"
#define PI 3.14159265

RGB G(0.4196,0.5568,0.1372);
RGB Pis(0.3235, 0.3823, 0.4450);
RGB PisT(205/255,184/255,180/255);
RGB Arv(0.4196,0.7568,0.1372);
RGB C1(0.1843, 0.3098, 0.3098);
RGB C2(0.8235, 0.4118, 0.1176);
RGB C3(0.8235, 0.7059, 0.5490);
RGB C4(0.4120, 0.2529, 0.8039);
RGB C5(0.9569, 0.6431, 0.3765);
RGB C6(0.9608, 0.9608, 0.8627);
RGB Az(72/255,118/255,1); //72 118 255
RGB J(1,1,1);
RGB P1(1,0,0);
RGB P2(0,1,0);
RGB P3(0,0,1);

RGB Esp(0,0,0);

Material *Casa1 = new Material(C1,C1,C1,1);
Material *Casa2 = new Material(C2,C2,C2,1);
Material *Casa3 = new Material(C3,C3,C3,1);
Material *Casa4 = new Material(C4,C4,C4,1);
Material *Casa5 = new Material(C5,C5,C5,1);
Material *Casa6 = new Material(C6,C6,C6,1);


Material* Telha = new Material(C6,C6,C6,1);
Material* Telha1 = new Material(C1,C1,C1,1);
Material* Telha2 = new Material(Az,Az,Az,1);

Material* Porta1 = new Material(P1,P1,P1,1);
Material* Porta2 = new Material(P2,P2,P2,1);
Material* Porta3 = new Material(P3,P3,P3,1);
Material* Janela = new Material(J,J,J,1);


Material *Grama = new Material(G,G,Esp,1);
Material *Pista = new Material(Pis,Pis,Pis,1);
Material *Terra = new Material(PisT,PisT,PisT,1);
Material *Arvore = new Material(Arv,Arv,Arv,1);

  float E[4][4], T[4][4], MT[4][4];
  float ve[4],vt[4];
  Objeto *O;

 transformacoes t;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Ex=-150; Ey=150;Ez=-150;
    Lox=50; Loy=0;Loz=50;
    Avx=50; Avy=100; Avz=50;
    Bg = new RGB(0.22,0.22,0.22);//(0.250980, 0.87843137, 0.815686275);
    Amb = new RGB(0.4, 0.4, 0.4);


    connect(ui->P1_Fuga, SIGNAL(pressed()),this, SLOT(Fuga_1P()));
    connect(ui->P2_Fuga, SIGNAL(pressed()),this, SLOT(Fuga_2P()));
    connect(ui->P3_Fuga, SIGNAL(pressed()),this, SLOT(Fuga_3P()));


    connect(ui->render,SIGNAL(pressed()),this,SLOT(Render()));
    connect(ui->render_2,SIGNAL(pressed()),this,SLOT(Obq()));
    //connect(ui->montar,SIGNAL(pressed()),this,SLOT(MontaCena()));
    //connect(ui->Cam,SIGNAL(pressed()),this,SLOT(CamT()));
    connect(ui->Sair,SIGNAL(pressed()),this,SLOT(Sair()));
    connect(ui->Pad,SIGNAL(pressed()),this,SLOT(Pad()));



    connect(ui->solo,SIGNAL(toggled(bool)), this, SLOT(setSolo(bool)));
    connect(ui->pistas,SIGNAL(toggled(bool)), this, SLOT(setPistas(bool)));
    connect(ui->portas,SIGNAL(toggled(bool)), this, SLOT(setPortas(bool)));
    connect(ui->paredes,SIGNAL(toggled(bool)), this, SLOT(setCasas(bool)));
    connect(ui->arvores,SIGNAL(toggled(bool)), this, SLOT(setArv(bool)));
    connect(ui->janelas,SIGNAL(toggled(bool)), this, SLOT(setJan(bool)));
    connect(ui->telhados,SIGNAL(toggled(bool)), this, SLOT(setTelhas(bool)));
    connect(ui->Postes,SIGNAL(toggled(bool)), this, SLOT(setPostes(bool)));
    connect(ui->Poste1,SIGNAL(toggled(bool)), this, SLOT(setP1(bool)));
    connect(ui->Poste2,SIGNAL(toggled(bool)), this, SLOT(setP2(bool)));
    connect(ui->Poste3,SIGNAL(toggled(bool)), this, SLOT(setP3(bool)));
    connect(ui->Poste4,SIGNAL(toggled(bool)), this, SLOT(setP4(bool)));

    connect(ui->sombras,SIGNAL(toggled(bool)), this, SLOT(sombras_rend(bool)));

    connect(ui->Eye_x,SIGNAL(valueChanged(double)), this, SLOT(Eye_X(double)));
    connect(ui->Eye_y,SIGNAL(valueChanged(double)), this, SLOT(Eye_Y(double)));
    connect(ui->Eye_z,SIGNAL(valueChanged(double)), this, SLOT(Eye_Z(double)));



    connect(ui->La_x,SIGNAL(valueChanged(double)), this, SLOT(Lo_X(double)));
    connect(ui->La_y,SIGNAL(valueChanged(double)), this, SLOT(Lo_Y(double)));
    connect(ui->La_z,SIGNAL(valueChanged(double)), this, SLOT(Lo_Z(double)));



    connect(ui->Av_x,SIGNAL(valueChanged(double)), this, SLOT(Av_X(double)));
    connect(ui->Av_y,SIGNAL(valueChanged(double)), this, SLOT(Av_Y(double)));
    connect(ui->Av_z,SIGNAL(valueChanged(double)), this, SLOT(Av_Z(double)));


    connect(ui->Teta,SIGNAL(valueChanged(double)), this, SLOT(setTeta(double)));
    connect(ui->Fator,SIGNAL(valueChanged(double)), this, SLOT(setFator(double)));


    connect(ui->w,SIGNAL(valueChanged(double)), this, SLOT(setW(double)));
    connect(ui->h,SIGNAL(valueChanged(double)), this, SLOT(setH(double)));
    connect(ui->d,SIGNAL(valueChanged(double)), this, SLOT(setD(double)));
    connect(ui->sizeX,SIGNAL(valueChanged(double)), this, SLOT(setSX(double)));
    connect(ui->sizeY,SIGNAL(valueChanged(double)), this, SLOT(setSY(double)));

    connect(ui->bgR,SIGNAL(valueChanged(int)), this, SLOT(setBG_R(int)));
    connect(ui->bgG,SIGNAL(valueChanged(int)), this, SLOT(setBG_G(int)));
    connect(ui->bgB,SIGNAL(valueChanged(int)), this, SLOT(setBG_B(int)));

    connect(ui->iaR,SIGNAL(valueChanged(int)), this, SLOT(IA_R(int)));
    connect(ui->iaG,SIGNAL(valueChanged(int)), this, SLOT(IA_G(int)));
    connect(ui->iaB,SIGNAL(valueChanged(int)), this, SLOT(IA_B(int)));


    connect(ui->Lp1_R,SIGNAL(valueChanged(int)), this, SLOT(set_rSp1(int)));
    connect(ui->Lp1_G,SIGNAL(valueChanged(int)), this, SLOT(set_gSp1(int)));
    connect(ui->Lp1_B,SIGNAL(valueChanged(int)), this, SLOT(set_bSp1(int)));

    connect(ui->Lp2_R,SIGNAL(valueChanged(int)), this, SLOT(set_rSp2(int)));
    connect(ui->Lp2_G,SIGNAL(valueChanged(int)), this, SLOT(set_gSp2(int)));
    connect(ui->Lp2_B,SIGNAL(valueChanged(int)), this, SLOT(set_bSp2(int)));

    connect(ui->Lp3_R,SIGNAL(valueChanged(int)), this, SLOT(set_rSp3(int)));
    connect(ui->Lp3_G,SIGNAL(valueChanged(int)), this, SLOT(set_gSp3(int)));
    connect(ui->Lp3_B,SIGNAL(valueChanged(int)), this, SLOT(set_bSp3(int)));

    connect(ui->Lp4_R,SIGNAL(valueChanged(int)), this, SLOT(set_rSp4(int)));
    connect(ui->Lp4_G,SIGNAL(valueChanged(int)), this, SLOT(set_gSp4(int)));
    connect(ui->Lp4_B,SIGNAL(valueChanged(int)), this, SLOT(set_bSp4(int)));


    connect(ui->rF1,SIGNAL(valueChanged(int)), this, SLOT(setF1r(int)));
    connect(ui->gF1,SIGNAL(valueChanged(int)), this, SLOT(setF1g(int)));
    connect(ui->bF1,SIGNAL(valueChanged(int)), this, SLOT(setF1b(int)));
    connect(ui->rF2,SIGNAL(valueChanged(int)), this, SLOT(setF2r(int)));
    connect(ui->gF2,SIGNAL(valueChanged(int)), this, SLOT(setF2g(int)));
    connect(ui->bF2,SIGNAL(valueChanged(int)), this, SLOT(setF2b(int)));
    connect(ui->rF3,SIGNAL(valueChanged(int)), this, SLOT(setF3r(int)));
    connect(ui->gF3,SIGNAL(valueChanged(int)), this, SLOT(setF3g(int)));
    connect(ui->bF3,SIGNAL(valueChanged(int)), this, SLOT(setF3b(int)));
    connect(ui->rF4,SIGNAL(valueChanged(int)), this, SLOT(setF4r(int)));
    connect(ui->gF4,SIGNAL(valueChanged(int)), this, SLOT(setF4g(int)));
    connect(ui->bF4,SIGNAL(valueChanged(int)), this, SLOT(setF4b(int)));
    connect(ui->rF5,SIGNAL(valueChanged(int)), this, SLOT(setF5r(int)));
    connect(ui->gF5,SIGNAL(valueChanged(int)), this, SLOT(setF5g(int)));
    connect(ui->bF5,SIGNAL(valueChanged(int)), this, SLOT(setF5b(int)));

    connect(ui->xF1,SIGNAL(valueChanged(double)), this, SLOT(setPF1x(double)));
    connect(ui->yF1,SIGNAL(valueChanged(double)), this, SLOT(setPF1y(double)));
    connect(ui->zF1,SIGNAL(valueChanged(double)), this, SLOT(setPF1z(double)));
    connect(ui->xF2,SIGNAL(valueChanged(double)), this, SLOT(setPF2x(double)));
    connect(ui->yF2,SIGNAL(valueChanged(double)), this, SLOT(setPF2y(double)));
    connect(ui->zF2,SIGNAL(valueChanged(double)), this, SLOT(setPF2z(double)));
    connect(ui->xF3,SIGNAL(valueChanged(double)), this, SLOT(setPF3x(double)));
    connect(ui->yF3,SIGNAL(valueChanged(double)), this, SLOT(setPF3y(double)));
    connect(ui->zF3,SIGNAL(valueChanged(double)), this, SLOT(setPF3z(double)));
    connect(ui->xF4,SIGNAL(valueChanged(double)), this, SLOT(setPF4x(double)));
    connect(ui->yF4,SIGNAL(valueChanged(double)), this, SLOT(setPF4y(double)));
    connect(ui->zF4,SIGNAL(valueChanged(double)), this, SLOT(setPF4z(double)));
    connect(ui->xF5,SIGNAL(valueChanged(double)), this, SLOT(setPF5x(double)));
    connect(ui->yF5,SIGNAL(valueChanged(double)), this, SLOT(setPF5y(double)));
    connect(ui->zF5,SIGNAL(valueChanged(double)), this, SLOT(setPF5z(double)));

    Point Eye(Ex, Ey, Ez);
    Point LA(Lox,Loy,Loz);
    Point AVUp(Avx,Avy,Avz);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(W,H,-d,sizeX,sizeY);

    scene = new Cenario(Cam, Amb, Bg, Obs);

    pF1 = new Point(pF1x,pF1y,pF1z);
    pF2 = new Point(pF2x,pF2y,pF2z);
    pF3 = new Point(pF3x,pF3y,pF3z);
    pF4 = new Point(pF4x,pF4y,pF4z);
    pF5 = new Point(pF5x,pF5y,pF5z);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Render(){
    CamT();
    MontaCena();





    scene->Word_Cam();
    Point Po(0,0,0);
    QImage image = QImage( sizeX, sizeY, QImage::Format_RGB32 );
    //scene->fontes_luminosas.at(0)->P->ImpPoint();
    //Ray Casting :
    //#pragma omp parallel for
    for( int i=0; i<sizeX; i++)
    {

        float Yi= (scene->Cam->h/2)-(scene->Cam->DY/2)-(i*scene->Cam->DY);

       // #pragma omp parallel for
        for( int j=0; j<sizeY; j++ )
        {
            //if((i < 100 || i > 150)  || (j < 100 || j > 150))
              // continue;

            float Xj = (-scene->Cam->w/2)+(scene->Cam->DX/2)+(j*scene->Cam->DX);
            Point Pij(Xj,Yi,scene->Cam->d);
            Pij.normalize();

                RGB* print = scene->Ray_Pix_Ilm(Po, Pij);
                image.setPixel( j, i, qRgb(print->R*255, print->G*255, print->B*255));
        }
    }

    QGraphicsScene * graphic = new QGraphicsScene( this );
    graphic->addPixmap( QPixmap::fromImage( image ) );
    ui->graphicsView->setScene(graphic);

    scene->Libera();
    free(scene);
}
void MainWindow::MontaCena(){

    ve[3] = 1; vt[3]=1;
    int iobj =-1;
    if(solo){
            O = CuboUni3(Grama);
            ve[0] = 100;ve[1] = 0.8; ve[2] = 95;
            t.Escala(E,ve);
            O->Transforoma(E);
            scene->Objetos.push_back(O);
            iobj++;
        }
        if(pistas){
            O = CuboUni3(Pista);


            ve[0]=10;ve[1]=0.2;ve[2]=55;
            vt[0]=45;vt[1]=0.8;vt[2]=0;
            t.Escala(E,ve);
            t.Translacao(T,vt);
            t.MxM(T,E,MT);;
            O->Transforoma(MT);
            scene->Objetos.push_back(O);
            iobj++;

            O = CuboUni3(Pista);
            ve[0]=100;ve[1]=0.2;ve[2]=10;
            vt[0]=0;vt[1]=0.8;vt[2]=55;
            t.Escala(E,ve);
            t.Translacao(T,vt);
            t.MxM(T,E,MT);
            O->Transforoma(MT);
            scene->Objetos.push_back(O);
            iobj++;

            O = CuboUni3(Pista);
            ve[0]=30;ve[1]=0.2;ve[2]=5;
            vt[0]=55;vt[1]=0.8;vt[2]=25;
            t.Escala(E,ve);
            t.Translacao(T,vt);
            t.MxM(T,E,MT);
            O->Transforoma(MT);
            scene->Objetos.push_back(O);
            //WObj.push_back(O);
            //free(O);
            iobj++;

            O = CuboUni3(Pista);
            ve[0]=15;ve[1]=0.2;ve[2]=4;
            vt[0]=30;vt[1]=0.8;vt[2]=28;
            t.Escala(E,ve);
            t.Translacao(T,vt);
            t.MxM(T,E,MT);
            O->Transforoma(MT);
            scene->Objetos.push_back(O);
            //WObj.push_back(O);
            //free(O);
            iobj++;

            float vx[4] ={7, 27, 55,85};
            for(int i=0; i<4; i++){
                O = CuboUni3(Terra);
                ve[0]=4;ve[1]=0.1; ve[2]=6;
                if(i==1)
                    ve[2]=11;
                vt[0]=vx[i];vt[1]=0.8;vt[2]=65;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                //WObj.push_back(O);
                //free(O);
                iobj++;
            }



        }
        if(casas){


                O = CuboUni3(Casa1);
                ve[0]=20;ve[1]=2.5;ve[2]=20;
                vt[0]=70;vt[1]=0.8;vt[2]=5;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                //free(O);
                iobj++;

                O = CuboUni3(Casa2);
                ve[0]=20;ve[1]=2.5;ve[2]=20;
                vt[0]=70;vt[1]=0.8;vt[2]=30;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                //free(O);
                iobj++;

                O = CuboUni3(Casa3);
                ve[0]=20;ve[1]=2.5;ve[2]=20;
                vt[0]=75;vt[1]=0.8;vt[2]=70;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = CuboUni3(Casa4);
                ve[0]=20;ve[1]=20;ve[2]=20;
                vt[0]=50;vt[1]=0.8;vt[2]=70;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = CuboUni3(Casa5);
                ve[0]=15;ve[1]=3;ve[2]=15;
                vt[0]=21;vt[1]=0.8;vt[2]=75;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = CuboUni3(Casa5);
                ve[0]=20;ve[1]=20;ve[2]=20;
                vt[0]=2;vt[1]=0.8;vt[2]=70;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = CuboUni3(Casa6);
                ve[0]=25;ve[1]=3;ve[2]=20;
                vt[0]=5;vt[1]=0.8;vt[2]=20;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = CuboUni3(Casa6);
                ve[0]=15;ve[1]=3;ve[2]=15;
                vt[0]=5;vt[1]=0.8;vt[2]=6;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

            }
        if(telhados){
                O = Prisma_Triangular_Uni3(Telha);
                ve[0]=20;ve[1]=2;ve[2]=20;
                vt[0]=70;vt[1]=3.3;vt[2]=5;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = Prisma_Triangular_Uni3(Telha2);
                ve[0]=20;ve[1]=2;ve[2]=20;
                vt[0]=70;vt[1]=3.3;vt[2]=30;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = Prisma_Triangular_Uni3(Telha1);
                ve[0]=20;ve[1]=2;ve[2]=20;
                vt[0]=75;vt[1]=3.3;vt[2]=70;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = Prisma_Triangular_Uni3(Telha1);
                ve[0]=20;ve[1]=3;ve[2]=20;
                vt[0]=50;vt[1]=20.7;vt[2]=70;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;


                O = Prisma_Triangular_Uni3(Telha2);
                ve[0]=15;ve[1]=2;ve[2]=15;
                vt[0]=21;vt[1]=3.8;vt[2]=75;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = Prisma_Triangular_Uni3(Telha2);
                ve[0]=20;ve[1]=3;ve[2]=20;
                vt[0]=2;vt[1]=20.8;vt[2]=70;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = Prisma_Triangular_Uni3(Telha1);
                ve[0]=25;ve[1]=3;ve[2]=20;
                vt[0]=5;vt[1]=3.8;vt[2]=20;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                O = Prisma_Triangular_Uni3(Telha1);
                ve[0]=15;ve[1]=3;ve[2]=15;
                vt[0]=5;vt[1]=3.8;vt[2]=6;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;


            }
        if(arvores){

               float z[4] = {8,14,40,60};
               for(int i=0; i<3; i++){
                   for(int j=0; j<4;j++){
                       O = CuboUni3(Arvore);
                       ve[0]=1.5;ve[1]=7;ve[2]=1.5;
                       vt[0]=z[j];vt[1]=0.8;vt[2]=(i*5)+42;
                       t.Escala(E,ve);
                       t.Translacao(T,vt);
                       t.MxM(T,E,MT);
                       O->Transforoma(MT);
                       scene->Objetos.push_back(O);
                       iobj++;
                   }
                   O = CuboUni3(Arvore);
                   ve[0]=1.5;ve[1]=7;ve[2]=1.5;
                   vt[0]=72;vt[1]=0.8;vt[2]=(i*5)+75;
                   t.Escala(E,ve);
                   t.Translacao(T,vt);
                   t.MxM(T,E,MT);
                   O->Transforoma(MT);
                   scene->Objetos.push_back(O);
                   iobj++;

                   O = CuboUni3(Arvore);
                   ve[0]=1.5;ve[1]=2;ve[2]=1.5;
                   vt[0]=40;vt[1]=0.8;vt[2]=(i*5)+75;
                   t.Escala(E,ve);
                   t.Translacao(T,vt);
                   t.MxM(T,E,MT);
                   O->Transforoma(MT);
                   scene->Objetos.push_back(O);
                   iobj++;

                   for(int j=0; j<2;j++){
                       O = CuboUni3(Arvore);
                       ve[0]=1.5;ve[1]=2;ve[2]=1.5;
                       vt[0]=(j*20)+40;vt[1]=0.8;vt[2]=(i*5)+5;
                       t.Escala(E,ve);
                       t.Translacao(T,vt);
                       t.MxM(T,E,MT);
                       O->Transforoma(MT);
                       scene->Objetos.push_back(O);
                       iobj++;
                   }


               }

           }
        if(portas){
             O = CuboUni3(Porta1);
             ve[0]=1;ve[1]=2;ve[2]=0.1;
             vt[0]=80;vt[1]=0.8;vt[2]=25;
             t.Escala(E,ve);
             t.Translacao(T,vt);
             t.MxM(T,E,MT);
             O->Transforoma(MT);
             scene->Objetos.push_back(O);
             iobj++;

             O = CuboUni3(Porta1);
             ve[0]=1;ve[1]=2;ve[2]=0.1;
             vt[0]=80;vt[1]=0.8;vt[2]=29.8;
             t.Escala(E,ve);
             t.Translacao(T,vt);
             t.MxM(T,E,MT);
             O->Transforoma(MT);
             scene->Objetos.push_back(O);
             iobj++;

             O = CuboUni3(Porta1);
             ve[0]=2;ve[1]=2;ve[2]=0.1;
             vt[0]=85;vt[1]=0.8;vt[2]=69.8;
             t.Escala(E,ve);
             t.Translacao(T,vt);
             t.MxM(T,E,MT);
             O->Transforoma(MT);
             scene->Objetos.push_back(O);
             iobj++;

             O = CuboUni3(Porta1);
             ve[0]=4;ve[1]=2.5;ve[2]=0.1;
             vt[0]=55;vt[1]=0.8;vt[2]=69.8;
             t.Escala(E,ve);
             t.Translacao(T,vt);
             t.MxM(T,E,MT);
             O->Transforoma(MT);
             scene->Objetos.push_back(O);
             iobj++;

             O = CuboUni3(Porta1);
             ve[0]=3;ve[1]=2;ve[2]=0.1;
             vt[0]=27;vt[1]=0.8;vt[2]=74.8;
             t.Escala(E,ve);
             t.Translacao(T,vt);
             t.MxM(T,E,MT);
             O->Transforoma(MT);
             scene->Objetos.push_back(O);
             iobj++;

             O = CuboUni3(Porta2);
             ve[0]=4;ve[1]=2.5;ve[2]=0.1;
             vt[0]=7;vt[1]=0.8;vt[2]=69.8;
             t.Escala(E,ve);
             t.Translacao(T,vt);
             t.MxM(T,E,MT);
             O->Transforoma(MT);
            scene->Objetos.push_back(O);
             iobj++;

             O = CuboUni3(Porta3);
             ve[0]=0.1;ve[1]=2;ve[2]=1.5;
             vt[0]=30;vt[1]=0.8;vt[2]=30;
             t.Escala(E,ve);
             t.Translacao(T,vt);
             t.MxM(T,E,MT);
             O->Transforoma(MT);
            scene->Objetos.push_back(O);
             iobj++;



         }
        if(janelas){

                for(int i=0; i<3;i++){
                    for(int j=0; j<4;j++){

                        O = CuboUni3(Janela);
                        ve[0]=2;ve[1]=2;ve[2]=0.1;
                        vt[0]=(i*5)+6;vt[1]=(j*3)+6.8;vt[2]=69.8;
                        t.Escala(E,ve);
                        t.Translacao(T,vt);
                        t.MxM(T,E,MT);
                        O->Transforoma(MT);
                        scene->Objetos.push_back(O);
                        iobj++;

                        O = CuboUni3(Janela);
                        ve[0]=0.1;ve[1]=2;ve[2]=1;
                        vt[0]=70;vt[1]=(j*3)+6.8;vt[2]=(i*5)+72;
                        t.Escala(E,ve);
                        t.Translacao(T,vt);
                        t.MxM(T,E,MT);
                        O->Transforoma(MT);
                        scene->Objetos.push_back(O);
                        iobj++;

                    }

                    O = CuboUni3(Janela);
                    ve[0]=0.1;ve[1]=1;ve[2]=1;
                    vt[0]=90;vt[1]=1.8;vt[2]=(i*5)+10;
                    t.Escala(E,ve);
                    t.Translacao(T,vt);
                    t.MxM(T,E,MT);
                    O->Transforoma(MT);
                   scene->Objetos.push_back(O);
                    iobj++;

                    O = CuboUni3(Janela);
                    vt[2]=(i*5)+35;
                    t.Escala(E,ve);
                    t.Translacao(T,vt);
                    t.MxM(T,E,MT);
                    O->Transforoma(MT);
                    scene->Objetos.push_back(O);
                    iobj++;

                    O = CuboUni3(Janela);
                    vt[0]=95;vt[2]=(i*5)+75;
                    t.Escala(E,ve);
                    t.Translacao(T,vt);
                    t.MxM(T,E,MT);
                    O->Transforoma(MT);
                   scene->Objetos.push_back(O);
                    iobj++;

                    O = CuboUni3(Porta1);
                    ve[0]=2;ve[1]=2;ve[2]=0.1;
                    vt[0]=(i*5)+6;vt[1]=1.8;vt[2]=5.9;
                    t.Escala(E,ve);
                    t.Translacao(T,vt);
                    t.MxM(T,E,MT);
                    O->Transforoma(MT);
                   scene->Objetos.push_back(O);
                    iobj++;
                }
            }

       if(postes){
        O = CuboUni3(Pista);
        ve[0]=0.5;ve[1]=15;ve[2]=0.5;
        vt[0]=43;vt[1]=0.8;vt[2]=25;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;
        O = CuboUni3(Pista);
        ve[0]=2.5;ve[1]=0.5;ve[2]=0.5;
        vt[1]=15.8;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;


        O = CuboUni3(Pista);
        ve[0]=0.5;ve[1]=15;ve[2]=0.5;
        vt[0]=61;vt[1]=0.8;vt[2]=35;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;
        O = CuboUni3(Pista);
        ve[0]=2.5;ve[1]=0.5;ve[2]=0.5;
        vt[0]=59;vt[1]=15.8;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;

        O = CuboUni3(Pista);
        ve[0]=0.5;ve[1]=15;ve[2]=0.5;
        vt[0]=43;vt[1]=0.8;vt[2]=70;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;
        O = CuboUni3(Pista);
        ve[0]=0.5;ve[1]=0.5;ve[2]=2.5;
        vt[2]=68;vt[1]=15.8;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;


        O = CuboUni3(Pista);
        ve[0]=0.5;ve[1]=15;ve[2]=0.5;
        vt[0]=72;vt[1]=0.8;vt[2]=70;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;
        O = CuboUni3(Pista);
        ve[0]=0.5;ve[1]=0.5;ve[2]=2.5;
        vt[2]=68;vt[1]=15.8;
        t.Escala(E,ve);
        t.Translacao(T,vt);
        t.MxM(T,E,MT);
        O->Transforoma(MT);
        scene->Objetos.push_back(O);
        iobj++;



    }
}
void MainWindow::CamT(){

    Point Eye(Ex, Ey, Ez);
    Point LA(Lox,Loy,Loz);
    Point AVUp(Avx,Avy,Avz);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(W,H,-d,sizeX,sizeY);
    scene = new Cenario(Cam, Amb, Bg, Obs);

    scene->Renderiza_somb = this->Renderiza_sombras;

    RGB iF1(rF1,gF1,bF1);
    RGB iF2(rF2,gF2,bF2);
    RGB iF3(rF3,gF3,bF3);
    RGB iF4(rF4,gF4,bF4);
    RGB iF5(rF5,gF5,bF5);

    RGB iSp1(rSp1, gSp1, bSp1);
    RGB iSp2(rSp2, gSp2, bSp2);
    RGB iSp3(rSp3, gSp3, bSp3);
    RGB iSp4(rSp4, gSp4, bSp4);

    pF1 = new Point(pF1x,pF1y,pF1z);
    pF2 = new Point(pF2x,pF2y,pF2z);
    pF3 = new Point(pF3x,pF3y,pF3z);
    pF4 = new Point(pF4x,pF4y,pF4z);
    pF5 = new Point(pF5x,pF5y,pF5z);


    if(rF1!=0||gF1!=0||bF1!=0)
        scene->addFonte2(pF1,iF1);
    if(rF2!=0||gF2!=0||bF2!=0)
        scene->addFonte2(pF2,iF2);
    if(rF3!=0||gF3!=0||bF3!=0)
        scene->addFonte2(pF3,iF3);
    if(rF4!=0||gF4!=0||bF4!=0)
        scene->addFonte2(pF4,iF4);
    if(rF5!=0||gF5!=0||bF5!=0)
        scene->addFonte2(pF5,iF5);

    float iz, jz, kz;

    iz = - Obs->i.y;
    jz = - Obs->j.y;
    kz = - Obs->k.y;

    if(p1 && postes){

        Point *PosSp1 = new Point(47,15,26);
        Point *D = new Point(iz,jz,kz);
        scene->addSpot2(PosSp1,D,iSp1,30);

    }
    if(p2 && postes){

        Point *PosSp2 = new Point(58,15,35);
        Point *D = new Point(iz,jz,kz);
        scene->addSpot2(PosSp2,D,iSp2,30);

    }
    if(p3 && postes){

        Point *PosSp3 = new Point(43,15,67);
        Point *D = new Point(iz,jz,kz);
        scene->addSpot2(PosSp3,D,iSp3,30);

    }
    if(p4 && postes){

        Point *PosSp4 = new Point(72,15,67);
        Point *D = new Point(iz,jz,kz);
        scene->addSpot2(PosSp4,D,iSp4,30);

    }


}
void MainWindow::Obq(){

/*
    //Teste Cubo Unitário:

    Point Eye(2.5, 2.5, 2.5);
    Point LA(1,1,1);
    Point AVUp(1,5,1);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(10,10,-0.00001,300,300);
    RGB *Back = new RGB(0.1, 0.1, 0.1);
    RGB *iA = new RGB(0.5, 0.5, 0.5);
    Cenario *scene = new Cenario(Cam, iA, Back,Obs);
    Objeto *O;
    O = CuboUni3(Casa6);
    O->faces.at(2)->M=Casa3;
    O->faces.at(3)->M=Casa3;
    O->faces.at(4)->M=Casa2;
    O->faces.at(5)->M=Casa2;

    scene->Objetos.push_back(O);
   // O->ImpPoints();
    */
    //FIm Teste

     CamT();
    MontaCena();
    scene->Word_Cam();

    float FcT = FOb*cos(Teta*PI/180);
    float FsT = FOb*sin(Teta*PI/180);
   // Point po(0,0,0);
    Point D(FcT, FsT, -1);
   // D.ImpPoint();


    QImage image = QImage( sizeX, sizeY, QImage::Format_RGB32 );

    for( int i=0; i<sizeX; i++)
    {

        float Yi= (scene->Cam->h/2)-(scene->Cam->DY/2)-(i*scene->Cam->DY);
        for( int j=0; j<sizeY; j++ )
        {

            float Xj = (-scene->Cam->w/2)+(scene->Cam->DX/2)+(j*scene->Cam->DX);
            Point Po(Xj,Yi,scene->Cam->d);
                RGB* print = scene->Ray_Pix_Ilm(Po, D);
                image.setPixel( j, i, qRgb(print->R*255, print->G*255, print->B*255));
        }
    }

    QGraphicsScene * graphic = new QGraphicsScene( this );
    graphic->addPixmap( QPixmap::fromImage( image ) );
    ui->graphicsView->setScene(graphic);

    scene->Libera();
    free(scene);
}

void MainWindow::Sair(){
    free(Casa1);
    free(Casa2);
    free(Casa3);
    free(Casa4);
    free(Casa5);
    free(Casa6);
    free(Telha);
    free(Telha1);
    free(Telha2);
    free(Porta1);
    free(Porta2);
    free(Porta3);
    free(Janela);
    free(Grama);
    free(Pista);
    free(Terra);
    free(Arvore);
    free(Bg);
    free(Amb);
    exit(0);

}
void MainWindow::Pad(){
    sizeX = 200;
    sizeY = 200;
    W = 0.5;
    H = 0.5;
    d = 1.5;
    rF1=0, rF2=0, rF3=0, rF4=0, rF5=0;
    gF1=0, gF2=0, gF3=0, gF4=0, gF5=0;
    bF1=0, bF2=0, bF3=0, bF4=0, bF5=0;

    Ex=250; Ey=200;Ez=-250;
    Lox=50; Loy=0;Loz=50;
    Avx=0; Avy=0; Avz=0;

    Amb->R=0.4;Amb->G=0.4;Amb->B=0.4;
    Bg->R=0.22;Bg->R=0.22;Bg->B=0.22;

}


void MainWindow::RenderPFuga(Cenario *Cena){


    QImage image = QImage( 400, 400, QImage::Format_RGB32 );

    for( int i=0; i<400; i++)
    {

        float Yi= (Cena->Cam->h/2)-(Cena->Cam->DY/2)-(i*Cena->Cam->DY);
        for( int j=0; j<400; j++ )
        {

            float Xj = (-Cena->Cam->w/2)+(Cena->Cam->DX/2)+(j*Cena->Cam->DX);
            Point Pij(Xj,Yi,Cena->Cam->d);
            Pij.normalize();
                Point Po(0,0,0);
                RGB* print = Cena->Ray_Pix_Ilm(Po, Pij);
                image.setPixel( j, i, qRgb(print->R*255, print->G*255, print->B*255));
        }
    }

    QGraphicsScene * graphic = new QGraphicsScene( this );
    graphic->addPixmap( QPixmap::fromImage( image ) );
    ui->graphicsModel->setScene(graphic);

    Cena->Libera();
    free(Cena);
}

void MainWindow::Fuga_1P(){

    Point Eye(-25, 5, 5);
    Point LA(5,5,5);
    Point AVUp(5,10,5);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(0.5,0.5,-1,400,400);
    RGB *Back = new RGB(0.1, 0.1, 0.1);
    RGB *iA = new RGB(0.7, 0.7, 0.7);
    Cenario *Cena = new Cenario(Cam, iA, Back, Obs);

    Objeto *cubo =  new Objeto();

    cubo->addPoint(0,0,0);
    cubo->addPoint(10,0,0);
    cubo->addPoint(0,10,0);
    cubo->addPoint(10,10,0);
    cubo->addPoint(0,0,10);
    cubo->addPoint(10,0,10);
    cubo->addPoint(0,10,10);
    cubo->addPoint(10,10,10);

    //cubo->addFace(0,6,4,Casa3);
    //cubo->addFace(0,2,6,Casa3);

    cubo->addFace(0,1,3,Pista);
    cubo->addFace(0,3,2,Pista);

    cubo->addFace(4,7,5,Pista);
    cubo->addFace(4,6,7,Pista);

    cubo->addFace(0,4,5,Casa3);
    cubo->addFace(0,5,1,Casa3);

    cubo->addFace(2,7,6,Casa3);
    cubo->addFace(2,3,7,Casa3);

    Cena->Objetos.push_back(cubo);
    Cena->Word_Cam();
    RenderPFuga(Cena);


}

void MainWindow::Fuga_2P(){

    Point Eye(5, 0.5, 5);
    Point LA(0.5,0.5,0.5);
    Point AVUp(0.5,5,0.5);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(0.5,0.5,-1,400,400);
    RGB *Back = new RGB(0.1, 0.1, 0.1);
    RGB *iA = new RGB(0.5, 0.5, 0.5);
    Cenario *Cena = new Cenario(Cam, iA, Back, Obs);
    Objeto *O;
    O = CuboUni3(Pista);
    O->faces.at(2)->M=Casa3;
    O->faces.at(3)->M=Casa3;
    Cena->Objetos.push_back(O);
    Cena->Word_Cam();
    RenderPFuga(Cena);

}

void MainWindow::Fuga_3P(){


    Point Eye(15, 10, 15);
    Point LA(0.5,0.5,0.5);
    Point AVUp(0.5,10,0.5);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(0.5,0.5,-3,400,400);
    RGB *Back = new RGB(0.1, 0.1, 0.1);
    RGB *iA = new RGB(0.7, 0.7, 0.7);
    Cenario *Cena = new Cenario(Cam, iA, Back,Obs);
    Objeto *O;
    O = CuboUni3(Pista);

    O->faces.at(2)->M=Grama;
    O->faces.at(3)->M=Grama;
    O->faces.at(4)->M=Casa2;
    O->faces.at(5)->M=Casa2;

    Cena->Objetos.push_back(O);
    Cena->Word_Cam();
    RenderPFuga(Cena);


}

void MainWindow::sombras_rend(bool s){
  Renderiza_sombras = s;
}

void MainWindow::setTeta(double T){
    Teta=T;
}

void MainWindow::setFator(double F){
    FOb = F;
}

void MainWindow::setPF1x(double d){
    pF1x=d;
}
void MainWindow::setPF1y(double d){
    pF1y=d;
}
void MainWindow::setPF1z(double d){
    pF1z=d;
}
void MainWindow::setF1r(int x){
    rF1 = (float)x/255;
}
void MainWindow::setF1g(int x){
    gF1 = (float)x/255;
}
void MainWindow::setF1b(int x){
    bF1 = (float)x/255;
}

void MainWindow::setPF2x(double d){
    pF2x=d;
}
void MainWindow::setPF2y(double d){
    pF2y=d;
}
void MainWindow::setPF2z(double d){
    pF2z=d;
}
void MainWindow::setF2r(int x){
    rF2 = (float)x/255;
}
void MainWindow::setF2g(int x){
    gF2 = (float)x/255;
}
void MainWindow::setF2b(int x){
    bF2 = (float)x/255;
}

void MainWindow::setPF3x(double d){
    pF3x=d;
}
void MainWindow::setPF3y(double d){
    pF3y=d;
}
void MainWindow::setPF3z(double d){
    pF3z=d;
}
void MainWindow::setF3r(int x){
    rF3 = (float)x/255;
}
void MainWindow::setF3g(int x){
    gF3 = (float)x/255;
}
void MainWindow::setF3b(int x){
    bF3 = (float)x/255;
}


void MainWindow::setPF4x(double d){
    pF4x=d;
}
void MainWindow::setPF4y(double d){
    pF4y=d;
}
void MainWindow::setPF4z(double d){
    pF4z=d;
}
void MainWindow::setF4r(int x){
    rF4 = (float)x/255;
}
void MainWindow::setF4g(int x){
    gF4 = (float)x/255;
}
void MainWindow::setF4b(int x){
    bF4 = (float)x/255;
}


void MainWindow::setPF5x(double d){
    pF5x=d;
}
void MainWindow::setPF5y(double d){
    pF5y=d;
}
void MainWindow::setPF5z(double d){
    pF5z=d;
}
void MainWindow::setF5r(int x){
    rF5 = (float)x/255;
}
void MainWindow::setF5g(int x){
    gF5 = (float)x/255;
}
void MainWindow::setF5b(int x){
    bF5 = (float)x/255;
}



void MainWindow::setBG_R(int I){
    Bg->R=(float)I/255;
}
void MainWindow::setBG_G(int I){
    Bg->G=(float)I/255;
}
void MainWindow::setBG_B(int I){
    Bg->B=(float)I/255;
}

void MainWindow::IA_R(int I){
    Amb->R= (float)I/255;
}
void MainWindow::IA_G(int I){
    Amb->G= (float)I/255;
}
void MainWindow::IA_B(int I){
    Amb->B= (float)I/255;
}

void MainWindow::set_rSp1(int I){
    rSp1 = (float)I/255;
}
void MainWindow::set_gSp1(int I){
    gSp1 = (float)I/255;
}
void MainWindow::set_bSp1(int I){
    bSp1 = (float)I/255;
}
void MainWindow::set_rSp2(int I){
    rSp2 = (float)I/255;
}
void MainWindow::set_gSp2(int I){
    gSp2 = (float)I/255;
}
void MainWindow::set_bSp2(int I){
    bSp2 = (float)I/255;
}
void MainWindow::set_rSp3(int I){
    rSp3 = (float)I/255;
}
void MainWindow::set_gSp3(int I){
    gSp3 = (float)I/255;
}
void MainWindow::set_bSp3(int I){
    bSp3 = (float)I/255;
}
void MainWindow::set_rSp4(int I){
    rSp4 = (float)I/255;
}
void MainWindow::set_gSp4(int I){
    gSp4 = (float)I/255;
}
void MainWindow::set_bSp4(int I){
    bSp4 = (float)I/255;
}

void MainWindow::setSolo(bool b){
    solo=b;
}
void MainWindow::setPistas(bool b){
    pistas=b;
}
void MainWindow::setCasas(bool b){
    casas=b;
}
void MainWindow::setTelhas(bool b){
    telhados=b;
}
void MainWindow::setArv(bool b){
    arvores=b;
}
void MainWindow::setPortas(bool b){
    portas=b;
}
void MainWindow::setJan(bool b){
    janelas=b;
}
void MainWindow::setPostes(bool b){
    postes=b;
}
void MainWindow::setP1(bool b){
    p1=b;
}
void MainWindow::setP2(bool b){
    p2=b;
}
void MainWindow::setP3(bool b){
    p3=b;
}
void MainWindow::setP4(bool b){
    p4=b;
}

void MainWindow::Eye_X(double x){
    Ex=(float)x;
}
void MainWindow::Eye_Y(double x){
    Ey=(float)x;
}
void MainWindow::Eye_Z(double x){
    Ez=(float)x;
}

void MainWindow::Lo_X(double x){
    Lox=(float)x;
}
void MainWindow::Lo_Y(double x){
    Loy=(float)x;
}
void MainWindow::Lo_Z(double x){
    Loz=(float)x;
}

void MainWindow::Av_X(double x){
    Avx=(float)x;
}
void MainWindow::Av_Y(double x){
    Avy=(float)x;
}
void MainWindow::Av_Z(double x){
    Avz=(float)x;
}

void MainWindow::setW(double x){
    W=(float)x;
}
void MainWindow::setH(double x){
    H=(float)x;
}
void MainWindow::setD(double x){
    d=(float)x;
}
void MainWindow::setSX(double x){
    sizeX=(float)x;
}
void MainWindow::setSY(double x){
    sizeY=(float)x;
}


Objeto* MainWindow::CuboUni3(Material *M){
    Objeto *cubo = new Objeto();

    cubo->addPoint(0,0,0);
    cubo->addPoint(1,0,0);
    cubo->addPoint(0,1,0);
    cubo->addPoint(1,1,0);
    cubo->addPoint(0,0,1);
    cubo->addPoint(1,0,1);
    cubo->addPoint(0,1,1);
    cubo->addPoint(1,1,1);

    cubo->addFace(0,3,1,M);
    cubo->addFace(0,2,3,M);
    cubo->addFace(1,7,5,M);
    cubo->addFace(1,3,7,M);
    cubo->addFace(4,5,7,M);
    cubo->addFace(4,7,6,M);
    cubo->addFace(0,4,6,M);
    cubo->addFace(0,6,2,M);
    cubo->addFace(0,5,4,M);
    cubo->addFace(0,1,5,M);
    cubo->addFace(2,6,7,M);
    cubo->addFace(2,7,3,M);

   return cubo;
}
Objeto* MainWindow::Prisma_Triangular_Uni3(Material *M){

    Objeto *prism = new Objeto();
    prism->addPoint(1,0,0);
    prism->addPoint(1,0,1);
    prism->addPoint(0,0,1);
    prism->addPoint(0,0,0);
    prism->addPoint(1,1,0.5);
    prism->addPoint(0,1,0.5);

    prism->addFace(1,3,0, M);
    prism->addFace(0,4,1, M);
    prism->addFace(4,2,1, M);
    prism->addFace(2,5,3, M);
    prism->addFace(0,5,4, M);
    prism->addFace(1,2,3, M);
    prism->addFace(4,5,2, M);
    prism->addFace(0,3,5, M);

     return prism;

}
