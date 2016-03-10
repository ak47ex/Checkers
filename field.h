#ifndef FIELD_H
#define FIELD_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <piece.h>
#include <QMouseEvent>
class field : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = 0);
private:
    void drawPieces();
    void drawField();
    void drawPiece(bool, int);
    void replacePieceByCoords(int x, int y, piece replace);
    piece readPieceByCoords(int x, int y);
    piece pieces[2][12];
    int iter;
    piece temp;
signals:

public slots:
    void updateField(piece array[2][12]);
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
};

#endif // FIELD_H
