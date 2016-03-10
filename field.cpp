#include "field.h"
#include <math.h>
#include <QOpenGLFunctions>
field::field(QWidget *parent) : QOpenGLWidget(parent)
{
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
void field::updateField(piece array[2][12]){
    for(int i=0; i<2; i++)
        for(int j=0; j<12; j++)
            pieces[i][j] = array[i][j];
    update();
}
void field::mousePressEvent(QMouseEvent *event){
    //далее приводим систему координат окна к клеткам. Т.е. строго определяем координаты клика от 0 до 7 по каждой координате.
    double x = ((double)event->x()/this->width())*8;
    double y = ((double)(this->height()-event->y())/this->height())*8;
    int xx=(int)floor(x);
    int yy=(int)floor(y);
    xmov=xx;
    ymov=yy;
    iter = currentPieceByCoords(xx,yy); //сохранили шашку

    update();
}

void field::mouseMoveEvent(QMouseEvent *event){
    double x = ((double)event->x()/this->width())*8;
    double y = ((double)(this->height()-event->y())/this->height())*8;
    if(event->buttons() & Qt::LeftButton && iter >-1){
        pieces[0][iter].x=x;
        pieces[0][iter].y=y;
        update();
    }
    if (!(event->buttons() & Qt::LeftButton)){
        pieces[0][iter].x=floor(x);
        pieces[0][iter].y=floor(y);
        update();
        iter=-1;
            return;
    }

}
void field::mouseReleaseEvent(QMouseEvent *event){
    if(iter>-1){
        double x = ((double)event->x()/this->width())*8;
        double y = ((double)(this->height()-event->y())/this->height())*8;
        int xx=floor(x);
        int yy=floor(y);
        if(((xx%2==0 && yy%2==0)|| (xx%2!=0 && yy%2!=0)) && checkCell(xx,yy)==0){
            if(abs(xx-xmov) == 1 && (yy-ymov)== 1){
                pieces[0][iter].x=xx;
                pieces[0][iter].y=yy;
            } else if(abs(xx-xmov) == 2 && abs(yy-ymov)==2 && checkCell((xx+xmov)/2,(yy+ymov)/2)==1 && checkCell(xx, yy)==0){
                pieces[0][iter].x=xx;
                pieces[0][iter].y=yy;
                removePieceByCoords((xx+xmov)/2,(yy+ymov)/2);
            }else
            if(yy < ymov && !pieces[0][iter].king){
                pieces[0][iter].x=xmov;
                pieces[0][iter].y=ymov;
                xmov=-1;
                ymov=-1;
            }else{
                pieces[0][iter].x=xmov;
                pieces[0][iter].y=ymov;
                xmov=-1;
                ymov=-1;
            }
        }
        else{
            pieces[0][iter].x=xmov;
            pieces[0][iter].y=ymov;
            xmov=-1;
            ymov=-1;
        }
        if(pieces[0][iter].king >=0){
            //xtmp = xx; ytmp =yy;            //сохранили координаты
            //replacePieceByCoords(xx,yy,piece(),iter); //очистили место
        }
        update();
        iter=-1;
    }
}
void field::removePieceByCoords(int x, int y){
    for(int j = 0; j < 12; j++){
        if(pieces[1][j].x==x && pieces[1][j].y==y){
            pieces[1][j]=piece();
            return;
        }
    }
}

void field::replacePieceByCoords(int x, int y, piece replace, int& iter){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 12; j++)
            if(pieces[i][j].x==x && pieces[i][j].y==y){
                pieces[i][j]=replace;
                iter = i;
            }
}
piece field::readPieceByCoords(int x, int y){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 12; j++)
            if(pieces[i][j].x==x && pieces[i][j].y==y)
                return pieces[i][j];
    return piece();
}
int field::checkCell(int x, int y){
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 12; j++)
            if(pieces[i][j].x==x && pieces[i][j].y==y)
                return 2-i;
    return 0;
}
int field::currentPieceByCoords(int x, int y){
    for(int i = 0; i < 12; i++)
        if(pieces[0][i].x==x && pieces[0][i].y==y)
            return i;
    return -1;
}

void field::drawPieces(){
    for(int i = 1; i >=0; i--){
        for(int j = 0; j < 12; j++){
            if(pieces[i][j].x<0 || pieces[i][j].y<0)
                continue;
            glPushMatrix();
            if(pieces[i][j].x-(int)pieces[i][j].x!=0 && pieces[i][j].y-(int)pieces[i][j].y!=0)
                glTranslatef(pieces[i][j].x, pieces[i][j].y, 0);
            else
                glTranslatef(pieces[i][j].x+0.5, pieces[i][j].y+0.5, 0);
            switch(i){
            case 0:
                drawPiece(0,pieces[i][j].king);
                break;
            case 1:
                drawPiece(1,pieces[i][j].king);
                break;
            }
            glPopMatrix();
        }
    }
}
void field::drawPiece(bool side, int king){
    if(king < 0)
        return;
    if(!side)
        glColor3ub(255,0,0);
    else
        glColor3ub(0,255,0);
    glPushMatrix();
//    glTranslatef(0.5,0.5,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(0,0);
    for(int i=0; i<360; i++){
        glVertex2d(cos(i)*0.43,-sin(i)*0.43);
    }
    glEnd();
    glPopMatrix();
    if(king == 1){
        glColor3ub(0,0,0);
        glPushMatrix();
//            glTranslatef(0.5,0.5,0);
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
