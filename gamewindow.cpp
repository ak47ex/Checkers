    #include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    piece temporary[2][12];
    for(int i=0; i<2; i++)
        for(int j=0; j<12; j++){
            temporary[i][j].king=0;
        }
    temporary[0][0].x=0;
    temporary[0][0].y=0;
    temporary[0][1].x=2;
    temporary[0][1].y=0;
    temporary[0][2].x=4;
    temporary[0][2].y=0;
    temporary[0][3].x=6;
    temporary[0][3].y=0;
    temporary[0][4].x=1;
    temporary[0][4].y=1;
    temporary[0][5].x=3;
    temporary[0][5].y=1;
    temporary[0][6].x=5;
    temporary[0][6].y=1;
    temporary[0][7].x=7;
    temporary[0][7].y=1;
    temporary[0][8].x=0;
    temporary[0][8].y=2;
    temporary[0][9].x=2;
    temporary[0][9].y=2;
    temporary[0][10].x=4;
    temporary[0][10].y=2;
    temporary[0][11].x=6;
    temporary[0][11].y=2;

    temporary[1][0].x=1;
    temporary[1][0].y=5;
    temporary[1][1].x=3;
    temporary[1][1].y=5;
    temporary[1][2].x=5;
    temporary[1][2].y=5;
    temporary[1][3].x=7;
    temporary[1][3].y=5;
    temporary[1][4].x=0;
    temporary[1][4].y=6;
    temporary[1][5].x=2;
    temporary[1][5].y=6;
    temporary[1][6].x=4;
    temporary[1][6].y=6;
    temporary[1][7].x=6;
    temporary[1][7].y=6;
    temporary[1][8].x=1;
    temporary[1][8].y=7;
    temporary[1][9].x=3;
    temporary[1][9].y=7;
    temporary[1][10].x=5;
    temporary[1][10].y=7;
    temporary[1][11].x=7;
    temporary[1][11].y=7;

    ui->openGLWidget->updateField(temporary);
}

GameWindow::~GameWindow()
{
    delete ui;
}
