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
    float d = 4;

    float Ex, Ey, Ez;
    float Lox, Loy, Loz;
    float Avx, Avy, Avz;

    Observador *Obs;
    Camera *Cam;

    RGB* Bg;//(0.250980, 0.87843137, 0.815686275);
    RGB* Amb;
    std::vector<Objeto*> WObj;
    Cenario* scene;

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
