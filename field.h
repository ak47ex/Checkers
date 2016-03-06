#ifndef FIELD_H
#define FIELD_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <GL/glu.h>
struct //структура для матрицы описания каждой клетки (чья шашка, её статус и т.д.)
class field : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = 0);
private:
    void drawCells();
    void drawPieces();
    GLuint genMenList();
    GLuint men;         //шашка
    GLuint king;        //дамка
signals:

public slots:
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int nWidth, int nHeight) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
};

#endif // FIELD_H
