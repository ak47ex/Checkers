#include "field.h"
#include <math.h>
#include <QOpenGLFunctions>
field::field(QWidget *parent) : QOpenGLWidget(parent)
{
    currentActive[0]=currentActive[1]=10;
    for(int i=0; i<4; i++)
        possibleMove[i][0]=possibleMove[i][1]=-1;
    possibleMoves=0;
}

void field::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(1,1,1,0);
    glShadeModel(GL_FLAT);
}

void field::resizeGL(int nWidth, int nHeight){
    glViewport(0, 0, nWidth, nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,8,0,8,0,1);
}

void field::paintGL(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,8,0,8,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawField();
    drawPieces();
}
void field::updateField(cell gameField[4][8]){
    for(int i=0; i<4; i++)
        for(int j=0; j<8; j++)
            this->gameField[i][j] = gameField[i][j];
}
void field::mousePressEvent(QMouseEvent *event){
    if(currentActive[0]<8){
        gameField[currentActive[0]][currentActive[1]].active=0;
        for(int i=0; i<possibleMoves; i++)
            gameField[possibleMove[i][0]][possibleMove[i][1]].active=0;
        possibleMoves=0;
    }
    double x = ((double)event->x()/this->width())*8;
    double y = ((double)(this->height()-event->y())/this->height())*8;
    int xx=(int)floor(x);
    int yy=(int)floor(y);
    if(yy%2==0){
        if(xx%2==0 && gameField[xx/2][yy].side==0){
            currentActive[0]=xx/2;
            currentActive[1]=yy;
            gameField[xx/2][yy].active=2;
            showPossibleMoves(xx/2,yy);
        }
    }
    else
        if((xx+1)%2==0 && gameField[xx/2][yy].side==0){
            currentActive[0]=xx/2;
            currentActive[1]=yy;
            gameField[xx/2][yy].active=2;
            showPossibleMoves(xx/2,yy);
        }
    update();
}
void field::showPossibleMoves(int x, int y){
    if(x>3 || y>7)//если вышли за пределы доски, выходим из функции
        return;
    if(y%2==0){ //если начинаем с чётной строки
            if(gameField[x][y+1].side==2){
                gameField[x][y+1].active=(char)1;
                possibleMove[possibleMoves][0]=x;
                possibleMove[possibleMoves++][1]=(y+1);
            }
            if(gameField[x-1][y+1].side==2 && x>0){
                gameField[x-1][y+1].active=(char)1;
                possibleMove[possibleMoves][0]=(x-1);
                possibleMove[possibleMoves++][1]=(y+1);
            }
    }
    else{
        if(gameField[x][y+1].side==2){
            gameField[x][y+1].active=(char)1;
            possibleMove[possibleMoves][0]=x;
            possibleMove[possibleMoves++][1]=(y+1);
        }
        if(gameField[x+1][y+1].side==2 && x<3){
            gameField[x+1][y+1].active=(char)1;
            possibleMove[possibleMoves][0]=(x+1);
            possibleMove[possibleMoves++][1]=(y+1);
        }
    }
//    update();
}

void field::drawPieces(){
    for(int j=0; j<8; j++)
        for(int i=0; i<4; i++){
            glPushMatrix();
            glTranslatef(i*2+j%2,j,0);
            switch(gameField[i][j].active){
            case (char)1:
                glColor3ub(130,130,170);
                glBegin(GL_QUADS);
                    glVertex2d(0,0);
                    glVertex2d(0,1);
                    glVertex2d(1,1);
                    glVertex2d(1,0);
                glEnd();
                break;
            case (char)2:
                glColor3ub(125,200,255);
                glBegin(GL_QUADS);
                    glVertex2d(0,0);
                    glVertex2d(0,1);
                    glVertex2d(1,1);
                    glVertex2d(1,0);
                glEnd();
                break;
            }
            glPopMatrix();
            glPushMatrix();
            glTranslatef(i*2+j%2,j,0);

            switch(gameField[i][j].side){
            case (char)0:
                glColor3ub(200,10,20);  //красные
                (gameField[i][j].isKing)?drawKing():drawMen();      //проверяем: дамка или нет?
                break;
            case (char)1:
                glColor3ub(115,200,20); //зелёные
                (gameField[i][j].isKing)?drawKing():drawMen();      //проверяем: дамка или нет?
                break;
            }
            glPopMatrix();
        }
}
void field::drawKing(){
    glPushMatrix();
        drawMen();
    glPopMatrix();
    glColor3ub(0,0,0);
    glPushMatrix();
        glTranslatef(0.5,0.5,0);
        glBegin(GL_LINE_STRIP);
        for(int i=0, k=0; i<=360; i+=4){
            if(k>0)
                glVertex2d(cos(i)*0.4,-sin(i)*0.4);
            else
                glVertex2d(cos(i)*0.29,-sin(i)*0.29);
            k=(k>0?0:1);
        }
        glEnd();
    glPopMatrix();
}

void field::drawMen(){
    glPushMatrix();
    glTranslatef(0.5,0.5,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(0,0);
    for(int i=0; i<360; i++){
        glVertex2d(cos(i)*0.43,-sin(i)*0.43);
    }
    glEnd();
    glPopMatrix();
}

void field::drawField(){
    glColor3d(0.3,0.3,0.3);
    for(int i=0; i<8; i+=2)
        for(int j=0; j<8; j++){
            if(j%2!=0){
                glBegin(GL_QUADS);
                    glVertex2d(i+1,j+0);
                    glVertex2d(i+1,j+1);
                    glVertex2d(i+2,j+1);
                    glVertex2d(i+2,j+0);
                glEnd();
            }
            else{
                glBegin(GL_QUADS);
                    glVertex2d(i+0,j+0);
                    glVertex2d(i+0,j+1);
                    glVertex2d(i+1,j+1);
                    glVertex2d(i+1,j+0);
                glEnd();
            }
        }
}
