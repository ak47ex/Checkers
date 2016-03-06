#include "field.h"
#include <math.h>
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
}

void field::paintGL(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,8,0,8,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCells();
    drawPieces();
}
void field::drawPieces(){
    men = genMenList();
    glTranslatef(1,1,0);
    glColor3ub(255,0,0);
    glCallList(men);
}

GLuint field::genMenList(){
    GLuint temp = glGenLists(1);
    glNewList(temp, GL_COMPILE);
        glTranslatef(0.5,0.5,0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(0,0);
        for(int i=0; i<360; i++){
            glVertex2d(cos(i)*0.43,-sin(i)*0.43);
        }
        glEnd();
    glEndList();
    return temp;
}

void field::drawCells(){
    glColor3d(0,0,0);
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
