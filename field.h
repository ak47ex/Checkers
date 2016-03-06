#ifndef FIELD_H
#define FIELD_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <cell.h>
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
signals:

public slots:
    void updateField(cell gameField[4][8]);
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int nWidth, int nHeight) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
};

#endif // FIELD_H
