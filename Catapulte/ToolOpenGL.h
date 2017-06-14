#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <GL/glut.h>
#include <iostream>
#include <match.h>
#include <QString>
#include <QGLWidget>
#include <QImage>
#include <QPixmap>

using namespace std;

class ToolOpenGL
{
public:
    ToolOpenGL();
//    unsigned int loadTexture(string imagePath);
    void chargerImage(QString image,int num);
    unsigned int loadTex(int num);
    unsigned int loadTex(QString image);
    void drawBoxWithTexture(QString texturePath);
    void drawBox();
    void drawSquareWithTexture(QString texturePath, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l);
    void drawSquare( float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l);
    void drawSphere();
    void drawCylinder();
    void drawCircleArea(float cx, float cy, float cz, float r, int num_segments);
    void deleteTextures();
private:
    QImage tex[4];
};

#endif // GLTOOLS_H

