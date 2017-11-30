#include "mainwindow.h"
#include "ui_mainwindow.h"

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

Material *Casa1 = new Material(C1,C1,C1,1);
Material *Casa2 = new Material(C2,C2,C2,1);
Material *Casa3 = new Material(C3,C3,C3,1);
Material *Casa4 = new Material(C4,C4,C4,1);
Material *Casa5 = new Material(C5,C5,C5,1);
Material *Casa6 = new Material(C6,C6,C6,1);


Material* Telha = new Material(C6,C6,C6,1);//(Te,Te,Te,1);
Material* Telha1 = new Material(C1,C1,C1,1);
Material* Telha2 = new Material(Az,Az,Az,1);

Material* Porta1 = new Material(P1,P1,P1,1);
Material* Porta2 = new Material(P2,P2,P2,1);
Material* Porta3 = new Material(P3,P3,P3,1);
Material* Janela = new Material(J,J,J,1);


Material *Grama = new Material(G,G,G,1);
Material *Pista = new Material(Pis,Pis,Pis,1);
Material *Terra = new Material(PisT,PisT,PisT,1);
Material *Arvore = new Material(Arv,Arv,Arv,1);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Ex=350; Ey=300;Ez=-350;
    Lox=100; Loy=5;Loz=50;
    Avx=50; Avy=0; Avz=0;
    Bg = new RGB(0.22,0.22,0.22);//(0.250980, 0.87843137, 0.815686275);
    Amb = new RGB(0.4, 0.4, 0.4);




    connect(ui->render,SIGNAL(pressed()),this,SLOT(Render()));
    connect(ui->montar,SIGNAL(pressed()),this,SLOT(MontaCena()));
    connect(ui->Cam,SIGNAL(pressed()),this,SLOT(CamT()));
    connect(ui->Sair,SIGNAL(pressed()),this,SLOT(Sair()));


    connect(ui->solo,SIGNAL(toggled(bool)), this, SLOT(setSolo(bool)));
    connect(ui->pistas,SIGNAL(toggled(bool)), this, SLOT(setPistas(bool)));
    connect(ui->portas,SIGNAL(toggled(bool)), this, SLOT(setPortas(bool)));
    connect(ui->paredes,SIGNAL(toggled(bool)), this, SLOT(setCasas(bool)));
    connect(ui->arvores,SIGNAL(toggled(bool)), this, SLOT(setArv(bool)));
    connect(ui->janelas,SIGNAL(toggled(bool)), this, SLOT(setJan(bool)));
    connect(ui->telhados,SIGNAL(toggled(bool)), this, SLOT(setTelhas(bool)));


    connect(ui->Eye_x,SIGNAL(valueChanged(double)), this, SLOT(Eye_X(double)));
    connect(ui->Eye_y,SIGNAL(valueChanged(double)), this, SLOT(Eye_Y(double)));
    connect(ui->Eye_z,SIGNAL(valueChanged(double)), this, SLOT(Eye_Z(double)));

    connect(ui->La_x,SIGNAL(valueChanged(double)), this, SLOT(Lo_X(double)));
    connect(ui->La_y,SIGNAL(valueChanged(double)), this, SLOT(Lo_Y(double)));
    connect(ui->La_z,SIGNAL(valueChanged(double)), this, SLOT(Lo_Z(double)));

    connect(ui->Av_x,SIGNAL(valueChanged(double)), this, SLOT(Av_X(double)));
    connect(ui->Av_y,SIGNAL(valueChanged(double)), this, SLOT(Av_Y(double)));
    connect(ui->Av_z,SIGNAL(valueChanged(double)), this, SLOT(Av_Z(double)));

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

    Point Eye(Ex, Ey, Ez);
    Point LA(Lox,Loy,Loz);
    Point AVUp(Avx,Avy,Avz);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(W,H,-d,sizeX,sizeY,*Obs);

    scene = new Cenario(Obs, Cam, Amb, Bg);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Render(){

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
void MainWindow::MontaCena(){

    RGB RL(0.6,0.6,0.6);
    Point *P = new Point(100,80,100);
    scene->addFonte2(P,RL);
    Operacoes Opr;
    //RGB Te(0.5054,0.2705,0.0745);
    float **E, **T, **MT;
    int iobj=0;
    float ve[4],vt[4];
    ve[3] = 1; vt[3]=1;

    if(solo){
        scene->CuboUni3(Grama);
        ve[0] = 100;ve[1] = 0.8; ve[2] = 95;
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
        float vx[4] ={7, 27, 55,85};
        for(int i=0; i<4; i++){
            scene->CuboUni3(Terra);
            ve[0]=4;ve[1]=0.1; ve[2]=6;
            if(i==1)
                ve[2]=11;
            vt[0]=vx[i];vt[1]=0.8;vt[2]=65;
            E = Opr.Escala(4,ve);
            T = Opr.Translacao(4,vt);
            MT = Opr.mult(4,4,4,T,E);
            scene->Objetos.at(iobj)->Transforoma(MT);
            iobj++;
        }



    }
    if(casas){


        scene->CuboUni3(Casa1);
        ve[0]=20;ve[1]=2.5;ve[2]=20;
        vt[0]=70;vt[1]=0.8;vt[2]=5;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa2);
        ve[0]=20;ve[1]=2.5;ve[2]=20;
        vt[0]=70;vt[1]=0.8;vt[2]=30;
        T = Opr.Translacao(4,vt);
        E = Opr.Escala(4, ve);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Casa3);
        ve[0]=20;ve[1]=2.5;ve[2]=20;
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
        ve[0]=15;ve[1]=3;ve[2]=15;
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
        vt[0]=5;vt[1]=0.8;vt[2]=6;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

    }
    if(telhados){
        scene->Prisma_Triangular_Uni3(Telha);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=70;vt[1]=3.3;vt[2]=5;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha2);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=70;vt[1]=3.3;vt[2]=30;
        T = Opr.Translacao(4,vt);
        E = Opr.Escala(4, ve);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->Prisma_Triangular_Uni3(Telha1);
        ve[0]=20;ve[1]=2;ve[2]=20;
        vt[0]=75;vt[1]=3.3;vt[2]=70;
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
        ve[0]=15;ve[1]=2;ve[2]=15;
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
        vt[0]=5;vt[1]=3.8;vt[2]=6;
        E = Opr.Escala(4, ve);
        T = Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;


    }
    if(arvores){

        float z[4] = {8,14,40,60};
        for(int i=0; i<3; i++){
            for(int j=0; j<4;j++){
                scene->CuboUni3(Arvore);
                ve[0]=1.5;ve[1]=7;ve[2]=1.5;
                vt[0]=z[j];vt[1]=0.8;vt[2]=(i*5)+42;
                E = Opr.Escala(4, ve);
                T= Opr.Translacao(4,vt);
                MT = Opr.mult(4,4,4,T,E);
                scene->Objetos.at(iobj)->Transforoma(MT);
                iobj++;
            }
            scene->CuboUni3(Arvore);
            ve[0]=1.5;ve[1]=7;ve[2]=1.5;
            vt[0]=72;vt[1]=0.8;vt[2]=(i*5)+75;
            E = Opr.Escala(4, ve);
            T= Opr.Translacao(4,vt);
            MT = Opr.mult(4,4,4,T,E);
            scene->Objetos.at(iobj)->Transforoma(MT);
            iobj++;

            scene->CuboUni3(Arvore);
            ve[0]=1.5;ve[1]=2;ve[2]=1.5;
            vt[0]=40;vt[1]=0.8;vt[2]=(i*5)+75;
            E = Opr.Escala(4, ve);
            T= Opr.Translacao(4,vt);
            MT = Opr.mult(4,4,4,T,E);
            scene->Objetos.at(iobj)->Transforoma(MT);
            iobj++;

            for(int j=0; j<2;j++){
                scene->CuboUni3(Arvore);
                ve[0]=1.5;ve[1]=2;ve[2]=1.5;
                vt[0]=(j*20)+40;vt[1]=0.8;vt[2]=(i*5)+5;
                E = Opr.Escala(4, ve);
                T= Opr.Translacao(4,vt);
                MT = Opr.mult(4,4,4,T,E);
                scene->Objetos.at(iobj)->Transforoma(MT);
                iobj++;
            }


        }

    }
    if(portas){
        scene->CuboUni3(Porta1);
        ve[0]=1;ve[1]=2;ve[2]=0.1;
        vt[0]=80;vt[1]=0.8;vt[2]=25;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Porta1);
        ve[0]=1;ve[1]=2;ve[2]=0.1;
        vt[0]=80;vt[1]=0.8;vt[2]=29.8;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Porta1);
        ve[0]=2;ve[1]=2;ve[2]=0.1;
        vt[0]=85;vt[1]=0.8;vt[2]=69.8;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Porta1);
        ve[0]=4;ve[1]=2.5;ve[2]=0.1;
        vt[0]=55;vt[1]=0.8;vt[2]=69.8;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Porta1);
        ve[0]=3;ve[1]=2;ve[2]=0.1;
        vt[0]=27;vt[1]=0.8;vt[2]=74.8;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Porta2);
        ve[0]=4;ve[1]=2.5;ve[2]=0.1;
        vt[0]=7;vt[1]=0.8;vt[2]=69.8;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;

        scene->CuboUni3(Porta3);
        ve[0]=0.1;ve[1]=2;ve[2]=1.5;
        vt[0]=30;vt[1]=0.8;vt[2]=30;
        E = Opr.Escala(4, ve);
        T= Opr.Translacao(4,vt);
        MT = Opr.mult(4,4,4,T,E);
        scene->Objetos.at(iobj)->Transforoma(MT);
        iobj++;



    }
    if(janelas){

        for(int i=0; i<3;i++){
            for(int j=0; j<4;j++){

                scene->CuboUni3(Janela);
                ve[0]=2;ve[1]=2;ve[2]=0.1;
                vt[0]=(i*5)+6;vt[1]=(j*3)+6.8;vt[2]=69.8;
                E = Opr.Escala(4, ve);
                T= Opr.Translacao(4,vt);
                MT = Opr.mult(4,4,4,T,E);
                scene->Objetos.at(iobj)->Transforoma(MT);
                iobj++;

                scene->CuboUni3(Janela);
                ve[0]=0.1;ve[1]=2;ve[2]=1;
                vt[0]=70;vt[1]=(j*3)+6.8;vt[2]=(i*5)+72;
                E = Opr.Escala(4, ve);
                T= Opr.Translacao(4,vt);
                MT = Opr.mult(4,4,4,T,E);
                scene->Objetos.at(iobj)->Transforoma(MT);
                iobj++;

            }

            scene->CuboUni3(Janela);
            ve[0]=0.1;ve[1]=1;ve[2]=1;
            vt[0]=90;vt[1]=1.8;vt[2]=(i*5)+10;
            E = Opr.Escala(4, ve);
            T= Opr.Translacao(4,vt);
            MT = Opr.mult(4,4,4,T,E);
            scene->Objetos.at(iobj)->Transforoma(MT);
            iobj++;

            scene->CuboUni3(Janela);
            vt[2]=(i*5)+35;
            E = Opr.Escala(4, ve);
            T= Opr.Translacao(4,vt);
            MT = Opr.mult(4,4,4,T,E);
            scene->Objetos.at(iobj)->Transforoma(MT);
            iobj++;

            scene->CuboUni3(Janela);
            vt[0]=95;vt[2]=(i*5)+75;
            E = Opr.Escala(4, ve);
            T= Opr.Translacao(4,vt);
            MT = Opr.mult(4,4,4,T,E);
            scene->Objetos.at(iobj)->Transforoma(MT);
            iobj++;

            scene->CuboUni3(Porta1);
            ve[0]=2;ve[1]=2;ve[2]=0.1;
            vt[0]=(i*5)+6;vt[1]=1.8;vt[2]=5.9;
            E = Opr.Escala(4, ve);
            T= Opr.Translacao(4,vt);
            MT = Opr.mult(4,4,4,T,E);
            scene->Objetos.at(iobj)->Transforoma(MT);
            iobj++;
        }
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
    scene->Word_Cam();
    //Opr.freeMat(4,E);
    //Opr.freeMat(4,T);

}
void MainWindow::CamT(){
    free(Obs);
    free(Cam);
    free(scene);

    Point Eye(Ex, Ey, Ez);
    Point LA(Lox,Loy,Loz);
    Point AVUp(Avx,Avy,Avz);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(W,H,-d,sizeX,sizeY,*Obs);

    scene = new Cenario(Obs, Cam, Amb, Bg);
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
    free(Cam);
    free(Obs);
    free(scene);
    exit(0);

}


void MainWindow::setBG_R(int I){
    Bg->R=I/255;
}
void MainWindow::setBG_G(int I){
    Bg->G=I/255;
}
void MainWindow::setBG_B(int I){
    Bg->B=I/255;
}

void MainWindow::IA_R(int I){
    Amb->R= I/255;
    std::cout<<"\n t = : " << Amb->R;
}
void MainWindow::IA_G(int I){
    Amb->G= I/255;
}
void MainWindow::IA_B(int I){
    Amb->B= I/255;
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
