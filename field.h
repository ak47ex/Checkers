#ifndef FIELD_H
#define FIELD_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <cell.h>
#include <QMouseEvent>
class field : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = 0);
private:
    void drawPieces();
    void drawCells();
    void drawMen();
    void drawKing();
    cell gameField[4][8];
    int currentActive[2];
signals:

public slots:
    void updateField(cell gameField[4][8]);
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent * event);
    //void mouseMoveEvent(QMouseEvent * event);
};

#endif // FIELD_H
