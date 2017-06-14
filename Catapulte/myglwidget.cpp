#include "myglwidget.h"


MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    floor.setHeight(100);
    floor.setLength(220);
    floor.setWidth(60);
    floor.setTrePosLength(180);
    floor.setTrePosWidth(30);
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat lightAmbient[] = {0.8, 1.0, 1.0, 1.0};
    GLfloat lightDiffuse[] = {0.5, 0.0, 0.0, 1.0};
    GLfloat lightSpecular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightPosition[] = {50, 50, 50, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float treLength = trebuchet.getBallX();

    if(treLength < 50){
        // first param - right/left
        // second param - up/down
        // third param -
        glTranslatef(0.6, -1.2, -3);
        glRotatef(-90, 1, 0, 0);
        glRotatef(20, 1, 0, 0);
        glRotatef(-90, 0, 0, 1);
        glRotatef(10, 0, 0, 1);
        glScalef(0.045, 0.045, 0.045);
    }else{
        glTranslatef(0.009*treLength+0.15,
                     -0.013*treLength-0.55,
                     -3);
        glRotatef(-90, 1, 0, 0);
        glRotatef(20, 1, 0, 0);
        glRotatef(-90, 0, 0, 1);
        glRotatef(10, 0, 0, 1);
        glScalef(0.00025*treLength+0.0325,
                 0.00025*treLength+0.0325,
                 0.00025*treLength+0.0325);
    }

    floor.drawFloor();
    glTranslatef(0, 0, 1);
    glRotatef(180, 0, 0, 1);
    trebuchet.drawTrebuchet();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}
