#ifndef FLOOR_H
#define FLOOR_H

#include <ToolOpenGL.h>

class Floor
{
public:
    Floor();
    Floor(float width, float length, float height, float trePosWidth, float trePosLength,float targetPosWidth,float targetPosLength,float targetHeight);
    void drawFloor();
    void setAngle(float angle){this->angle = angle;}
    void setTargetHeight(float targetHeight){this->targetHeight = targetHeight;}
    void setTargetPosWidth(float targetPosWidth){this->targetPosWidth = targetPosWidth;}
    void setTargetPosLength(float targetPosLength){this->targetPosLength = targetPosLength;}
    void setWidth(float width){this->width = width;}
    void setLength(float length){this->length = length;}
    void setHeight(float height){this->height = height;}
    void setTrePosWidth(float trePosWidth){this->trePosWidth = trePosWidth;}
    void setTrePosLength(float trePosLength){this->trePosLength = trePosLength;}

private:
    GLuint ground;
    GLuint leftWall;
    GLuint frontWall;
    GLuint rightWall;
    GLuint backWall;
    GLuint fence;
    GLuint target;
    GLuint logo;
    ToolOpenGL toolOpenGL;
    GLuint tseLogoTexture;

    float size;
    float width, length, height, trePosWidth, trePosLength;
    float targetHeight, targetPosWidth, targetPosLength;
    float angle = 0;
};

#endif // FLOOR_H
