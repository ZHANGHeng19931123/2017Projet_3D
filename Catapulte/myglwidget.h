#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <floor.h>
#include <trebuchet.h>
#include <ToolOpenGL.h>

#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QWidget>
#include <QWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
    Trebuchet trebuchet;
    Floor floor = Floor();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawTrebuchet();
    void drawFloor();
    float temp = 0;
};

#endif // MYGLWIDGET_H

