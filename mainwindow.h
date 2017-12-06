#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cenario.h"
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
#include "rgb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    bool solo = false;
    bool pistas = false;
    bool casas = false;
    bool telhados = false;
    bool arvores = false;
    bool portas = false;
    bool janelas = false;


    int sizeX = 200;
    int sizeY = 200;
    float W = 0.5;
    float H = 0.5;
    float d = 2;

    float Ex, Ey, Ez;
    float Lox, Loy, Loz;
    float Avx, Avy, Avz;

    Observador *Obs;
    Camera *Cam;

    RGB* Bg;//(0.250980, 0.87843137, 0.815686275);
    RGB* Amb;
    Cenario* scene;

    Point *pF1;
    Point *pF2;
    Point *pF3;
    Point *pF4;
    Point *pF5;

    float rF1=0, rF2=0, rF3=0, rF4=0, rF5=0;
    float gF1=0, gF2=0, gF3=0, gF4=0, gF5=0;
    float bF1=0, bF2=0, bF3=0, bF4=0, bF5=0;

    Objeto* CuboUni3(Material *M);
    Objeto* Prisma_Triangular_Uni3(Material *M);
    void cWord();

private:
    Ui::MainWindow *ui;

public slots:
    void Render();
    void MontaCena();
    void CamT();
    void Sair();

    void setPF1x(double);
    void setPF2x(double);
    void setPF3x(double);
    void setPF4x(double);
    void setPF5x(double);

    void setPF1y(double);
    void setPF2y(double);
    void setPF3y(double);
    void setPF4y(double);
    void setPF5y(double);

    void setPF1z(double);
    void setPF2z(double);
    void setPF3z(double);
    void setPF4z(double);
    void setPF5z(double);


    void setF1r(int);
    void setF1g(int);
    void setF1b(int);
    void setF2r(int);
    void setF2g(int);
    void setF2b(int);
    void setF3r(int);
    void setF3g(int);
    void setF3b(int);
    void setF4r(int);
    void setF4g(int);
    void setF4b(int);
    void setF5r(int);
    void setF5g(int);
    void setF5b(int);

    void setBG_R(int);
    void setBG_G(int);
    void setBG_B(int);
    void IA_R(int);
    void IA_G(int);
    void IA_B(int);

    void setSolo(bool);
    void setPistas(bool);
    void setCasas(bool);
    void setTelhas(bool);
    void setArv(bool);
    void setPortas(bool);
    void setJan(bool);

    void Eye_X(double);
    void Eye_Y(double);
    void Eye_Z(double);

    void Lo_X(double);
    void Lo_Y(double);
    void Lo_Z(double);

    void Av_X(double);
    void Av_Y(double);
    void Av_Z(double);

    void setW(double);
    void setH(double);
    void setD(double);
    void setSX(double);
    void setSY(double);

};

#endif // MAINWINDOW_H
