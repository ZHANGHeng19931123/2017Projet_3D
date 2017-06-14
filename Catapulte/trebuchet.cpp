#include "trebuchet.h"

Trebuchet::Trebuchet()
{
}

void Trebuchet::drawTrebuchet()
{
    stand = glGenLists(1);
    // stand
    // xie zhi cheng jia
    glColor3f(1.0f, 0.69f, 0.26f);
    glNewList(stand, GL_COMPILE);
    glPushMatrix();
    glTranslatef(-2, -2, 3.3);
    glRotatef(30, 0, 1, 0);
    glScalef(0.5, 0.5, 8);
    toolOpenGL.drawBoxWithTexture("wood1");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2, -2, 3.3);
    glRotatef(150, 0, 1, 0);
    glScalef(0.5, 0.5, 8);
    toolOpenGL.drawBoxWithTexture("wood1");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2, 2, 3.3);
    glRotatef(30, 0, 1, 0);
    glScalef(0.5, 0.5, 8);
    toolOpenGL.drawBoxWithTexture("wood1");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2, 2, 3.3);
    glRotatef(150, 0, 1, 0);
    glScalef(0.5, 0.5, 8);
    toolOpenGL.drawBoxWithTexture("wood1");
    glPopMatrix();
    // di zuo
    glColor3f(1.0f, 0.69f, 0.26f);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(8, 4, 0.5);
    toolOpenGL.drawBoxWithTexture("wood1");
    glPopMatrix();
    if(cheat == true){
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();
        glTranslatef(-75, 0, 0);
        glScalef(150, 0.1, 0.1);
        toolOpenGL.drawBox();
        glPopMatrix();
    }

    // lun zi
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(3, 2.7, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(2, 2, 0.5);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3, 2.7, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(2, 2, 0.5);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3, -2.2, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(2, 2, 0.5);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3, -2.2, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(2, 2, 0.5);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    // lun zhou
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(3, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.28, 0.28, 6);
    toolOpenGL.drawBox();
    glPopMatrix();
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(-3, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.28, 0.28, 6);
    toolOpenGL.drawBox();
    glPopMatrix();
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(0, -2, 4);
    glScalef(3, 0.3, 0.3);
    toolOpenGL.drawBox();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 2, 4);
    glScalef(3, 0.3, 0.3);
    toolOpenGL.drawBox();
    glPopMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0, 2, 3.3);
    glScalef(0.4, 0.4, 6);
    toolOpenGL.drawBox();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -2, 3.3);
    glScalef(0.4, 0.4, 6);
    toolOpenGL.drawBox();
    glPopMatrix();
    // jiao di zhi cheng jia
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(3.2, 0, 1.2);
    glScalef(0.3, 3.8, 0.3);
    toolOpenGL.drawBox();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3.2, 0, 1.2);
    glScalef(0.3, 3.8, 0.3);
    toolOpenGL.drawBox();
    glPopMatrix();
    // ding bu zhou
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(0, 0, 6.5);
    glScalef(0.2, 5, 0.2);
    toolOpenGL.drawBox();
    glPopMatrix();
    glEndList();

    // swingArm
    swingArm = glGenLists(1);
    glNewList(swingArm, GL_COMPILE);
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(3, 0, 0);
    glScalef(12, 0.5, 0.5);
    toolOpenGL.drawBox();
    glPopMatrix();
    glEndList();

    // weight
    weight = glGenLists(1);
    glNewList(weight, GL_COMPILE);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-3*cos(swingArmAngle*PI/180), 0, 6.5+3*sin(swingArmAngle*PI/180)-2);
    glScalef(1.5, 1, 1.5);
    toolOpenGL.drawBoxWithTexture("wood");
    glPopMatrix();
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(-3*cos(swingArmAngle*PI/180), 0, 6.5+3*sin(swingArmAngle*PI/180)-1);
    glScalef(0.1, 0.1, 2);
    toolOpenGL.drawBox();
    glPopMatrix();
    glEndList();

    // sling
    sling = glGenLists(1);
    glNewList(sling, GL_COMPILE);
    if(swingArmAngle <= 0 && swingArmAngle >= -112.5){
        glPushMatrix();
        slingAngle = 90 - swingArmAngle*0.8;
        glTranslatef(9*cos(swingArmAngle*PI/180)+3.25*sin((slingAngle-swingArmAngle-90)*PI/180), 0, 6.5-9*sin(swingArmAngle*PI/180)-3.25*cos((slingAngle-swingArmAngle-90)*PI/180));
        glRotatef(180-slingAngle+swingArmAngle, 0, 1, 0);
        glScalef(6.5, 0.1, 0.1);
        toolOpenGL.drawBox();
        glPopMatrix();
    } else if(swingArmAngle > 0 && swingArmAngle < 47){
        float tempAngle = (90-swingArmAngle)*PI/180;
        float temp0 = 6.5-9*cos(tempAngle);
        float temp1 = sqrt(6.5*6.5-temp0*temp0);
        float pos = 9*sin(tempAngle) - temp1;
        glPushMatrix();
        glTranslatef(pos+temp1/2, 0, temp0/2);
        glRotatef(-asin(temp0/6.5)/PI*180, 0, 1, 0);
        glScalef(6.5, 0.1, 0.1);
        toolOpenGL.drawBox();
        glPopMatrix();
    } else if(swingArmAngle >= 133 && swingArmAngle <= 156){
        glPushMatrix();
        float length1 = 6.5/cos((swingArmAngle-90)*PI/180)-9;
        glTranslatef(-(9*sin((swingArmAngle-90)*PI/180)+6.5*tan((swingArmAngle-90)*PI/180))/2, 0, (6.5-9*cos((swingArmAngle-90)*PI/180))/2);
        glRotatef(swingArmAngle, 0, 1, 0);
        glScalef(length1, 0.1, 0.1);
        toolOpenGL.drawBox();
        glPopMatrix();

        glPushMatrix();
        float length2 = 6.5 - length1;
        glTranslatef(-6.5*tan((swingArmAngle-90)*PI/180)-length2/2, 0, 0);
        glScalef(length2, 0.1, 0.1);
        toolOpenGL.drawBox();
        glPopMatrix();
    } else {
        glPushMatrix();
        slingAngle = 180;
        glTranslatef(9*cos(swingArmAngle*PI/180)+3.25*sin((slingAngle-swingArmAngle-90)*PI/180), 0, 6.5-9*sin(swingArmAngle*PI/180)-3.25*cos((slingAngle-swingArmAngle-90)*PI/180));
        glRotatef(180-slingAngle+swingArmAngle, 0, 1, 0);
        glScalef(6.5, 0.1, 0.1);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glEndList();

    // ball
    ball = glGenLists(1);
    glNewList(ball, GL_COMPILE);
    glColor3f(0.392f, 0.329f, 0.329f);
    glPushMatrix();
    if(swingArmAngle <= 0 && swingArmAngle >= -100){
        ballX = 9*cos(swingArmAngle*PI/180)+6.5*sin((slingAngle-swingArmAngle-90)*PI/180);
        ballY = 0;
        ballZ = 6.5-9*sin(swingArmAngle*PI/180)-6.5*cos((slingAngle-swingArmAngle-90)*PI/180);
    }else if(swingArmAngle >0 && swingArmAngle < 47){
        float tempAngle = (90-swingArmAngle)*PI/180;
        float temp0 = 6.5-9*cos(tempAngle);
        float temp1 = sqrt(6.5*6.5-temp0*temp0);
        float pos = 9*sin(tempAngle) - temp1;
        ballX = pos;
        ballY = 0;
        ballZ = 0;
    } else if((swingArmAngle < -100 && swingArmAngle > -180) || (swingArmAngle <= 180 && swingArmAngle >= 133)) {
        float t = 0;
        if(swingArmAngle < 0){
            t = -100-swingArmAngle;
        }else{
            t = 260-swingArmAngle;
        }
        float a = -0.001355527;
        float h = a*t*t+21.8633;
        float x = -1.56283 - v*t;
        ballX = x;
        ballY = 0;
        ballZ = h;
    }
    glTranslatef(ballX, ballY, ballZ);
    glScalef(1, 1, 1);
    toolOpenGL.drawSphere();
    glPopMatrix();
    glEndList();

    // draw the display list
    glTranslatef(standX, standY, standZ);
    glRotatef(standAngle, 0, 0, 1);
    glScalef(standScaleX, standScaleY, standScaleZ);
    glCallList(stand);
    glCallList(sling);
    glCallList(weight);
    glCallList(ball);
    glTranslatef(0, 0, 6.5);
    glRotatef(swingArmAngle, 0, 1, 0);
    glCallList(swingArm);

    glDeleteLists(stand,1);
    glDeleteLists(ball,1);
    glDeleteLists(weight,1);
    glDeleteLists(sling,1);
    glDeleteLists(swingArm,1);
}

void Trebuchet::setSwingArmAngle(float angle)
{
    while(angle > 180){
        angle -= 360;
    }
    while(angle < -180){
        angle += 360;
    }
    if((angle > 133)||(angle < 47))
    {
        swingArmAngle = angle;
    }
}

void Trebuchet::setStandAngle(float angle)
{
    angle -= 180;
    standAngle = angle;
}
