#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cenario.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Render(int sizeX, int sizeY, Cenario *Scene);
    void MontaCena(Cenario *Scene);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
