#ifndef TREBUCHET_H
#define TREBUCHET_H

#include <ToolOpenGL.h>
#include <math.h>

#define PI 3.14159265

using namespace std;

class Trebuchet
{
public:
    Trebuchet();
    void drawTrebuchet();
    void setSwingArmAngle(float angle);
    void setStandAngle(float angle);
    float getSwingArmAngle(){return swingArmAngle;}
    float getStandAngle(){return standAngle;}
    float getStandX(){return standX;}
    float getStandY(){return standY;}
    float getStandZ(){return standZ;}
    float getStandScaleX(){return standScaleX;}
    float getStandScaleY(){return standScaleY;}
    float getStandScaleZ(){return standScaleZ;}
    void setSpeed(float v){this->v = v;}
    float getBallX(){return -1*ballX;}
    float getBallY(){return ballY;}
    float getBallZ(){return ballZ;}
    void setCheat(){cheat = !cheat;}
private:
    GLuint stand;
    GLuint swingArm;
    GLuint ball;
    GLuint weight;
    GLuint sling;
    float swingArmAngle = 0;
    float standAngle = 0;
    float slingAngle = 0;
    float standX = 0;
    float standY = 0;
    float standZ = 0;
    float standScaleX = 1;
    float standScaleY = 1;
    float standScaleZ = 1;
    float v = 0;
    ToolOpenGL toolOpenGL;
    float ballX, ballY, ballZ;
    bool cheat = false;
};

#endif // TREBUCHET_H
