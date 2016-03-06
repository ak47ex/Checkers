#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    for(int i=0; i<4; i++)
        for(int j=0; j<8; j++){
            if(j<3)
                gameField[i][j]=cell(0,0);
            else if(j>4)
                gameField[i][j]=cell(0,1);
            else
                gameField[i][j]=cell(0,2);
        }
    ui->openGLWidget->updateField(gameField);
}

GameWindow::~GameWindow()
{
    delete ui;
}
