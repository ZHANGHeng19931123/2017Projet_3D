#include "floor.h"

Floor::Floor()
{
}

Floor::Floor(float width, float length, float height, float trePosWidth, float trePosLength,float targetPosWidth,float targetPosLength,float targetHeight)
{
    this->width = width;
    this->length = length;
    this->height = height;
    this->trePosWidth = trePosWidth;
    this->trePosLength = trePosLength;
    this->targetPosWidth = targetPosWidth;
    this->targetPosLength = targetPosLength;
    this->targetHeight = targetHeight;
}

void Floor::drawFloor()
{
    const float fenceHeight = 1.0;
    const float fenceNum = 32;
    const float fenceNum2 = 4;
    const float fenceSize = 0.5;

    // ground
    ground = glGenLists(1);
    glNewList(ground, GL_COMPILE);
    glPushMatrix();
    glRotatef(angle,0,0,1);
    glTranslatef(-trePosLength, -trePosWidth, 0);
    toolOpenGL.drawSquareWithTexture("grass",
                                     0,0,0,
                                     length,0,0,
                                     length,width,0,
                                     0,width,0);
    //    glColor4f(0.337f, 0.69f, 0.0f, 0.3f);
    //    const float stripeNum = 4;

    //    for(float i = 1; i < stripeNum; i ++){
    //        toolOpenGL.drawSquare(0,width/(stripeNum*2-1)*(2*i-1),0.01,
    //                              length,width/(stripeNum*2-1)*(2*i-1),0.01,
    //                              length,width/(stripeNum*2-1)*(2*i),0.01,
    //                              0,width/(stripeNum*2-1)*(2*i),0.01);
    //    }
    //    glColor4f(0.0f, 0.482f, 0.047f, 0.01f);
    //    toolOpenGL.drawSquare(0,0,0.005,
    //                          length,0,0.005,
    //                          length,width,0.005,
    //                          0,width,0.005);
    glPopMatrix();
    glEndList();

    // left
    leftWall = glGenLists(1);
    glNewList(leftWall, GL_COMPILE);
    glPushMatrix();glRotatef(angle,0,0,1);
    glColor3f(0.18f, 0.31f, 0.31f);
    glTranslatef(-trePosLength, -trePosWidth, 0);
    toolOpenGL.drawSquare(0,0,0,
                          length,0,0,
                          length,0,-height,
                          0,0,-height);
    glPopMatrix();
    glColor3f(0.5f, 0.32f, 0.00f);
    for(int i = 1; i < fenceNum2+1; i ++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(length/2, 0, fenceHeight*i);
        glScalef(length, fenceSize, fenceSize);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glColor3f(0.71f, 0.60f, 0.298f);
    for(int i = 0; i <= fenceNum; i ++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(length/fenceNum*i, 0, (fenceHeight*fenceNum2+2)/2);
        glScalef(fenceSize, fenceSize, fenceHeight*fenceNum2+2);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glEndList();

    // right
    rightWall = glGenLists(1);
    glNewList(rightWall, GL_COMPILE);
    glPushMatrix();glRotatef(angle,0,0,1);
    glColor3f(0.45f, 0.847f, 0.93f);
    glTranslatef(-trePosLength, -trePosWidth, 0);
    toolOpenGL.drawSquare(0,width,0,
                          0,width,height,
                          length,width,height,
                          length,width,0);
    glPopMatrix();
    glColor3f(0.5f, 0.32f, 0.00f);
    for(int i = 1; i < fenceNum2+1; i++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(length/2, width, fenceHeight*i);
        glScalef(length, fenceSize, fenceSize);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glColor3f(0.71f, 0.60f, 0.298f);
    for(int i = 0; i <= fenceNum; i ++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(length/fenceNum*i, width, (fenceHeight*fenceNum2+2)/2);
        glScalef(fenceSize, fenceSize, fenceHeight*fenceNum2+2);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glEndList();

    // front
    frontWall = glGenLists(1);
    glNewList(frontWall, GL_COMPILE);
    glPushMatrix();glRotatef(angle,0,0,1);
    glColor3f(0.45f, 0.847f, 0.93f);
    glTranslatef(-trePosLength, -trePosWidth, 0);
    toolOpenGL.drawSquare(0,0,height,
                          0,width,0,
                          0,width,height,
                          0,0,0);
    glPopMatrix();
    glColor3f(0.5f, 0.32f, 0.00f);
    for(int i = 1; i < fenceNum2+1; i++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(0, width/2, fenceHeight*i);
        glScalef(fenceSize, width, fenceSize);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glColor3f(0.71f, 0.60f, 0.298f);
    for(int i = 1; i < fenceNum; i ++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(0, width/fenceNum*i, (fenceHeight*fenceNum2+2)/2);
        glScalef(fenceSize, fenceSize, fenceHeight*fenceNum2+2);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glEndList();

    // back
    backWall = glGenLists(1);
    glNewList(backWall, GL_COMPILE);
    glPushMatrix();glRotatef(angle,0,0,1);
    glColor3f(0.18f, 0.31f, 0.31f);
    glTranslatef(-trePosLength, -trePosWidth, 0);
    toolOpenGL.drawSquare(length,0,0,
                          length,0,-height,
                          length,width,-height,
                          length,width,0);
    glPopMatrix();
    glColor3f(0.5f, 0.32f, 0.00f);
    for(int i = 1; i < fenceNum2+1; i++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(length, width/2, fenceHeight*i);
        glScalef(fenceSize, width, fenceSize);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glColor3f(0.71f, 0.60f, 0.298f);
    for(int i = 1; i < fenceNum; i ++){
        glPushMatrix();glRotatef(angle,0,0,1);
        glTranslatef(-trePosLength, -trePosWidth, 0);
        glTranslatef(length, width/fenceNum*i, (fenceHeight*fenceNum2+2)/2);
        glScalef(fenceSize, fenceSize, fenceHeight*fenceNum2+2);
        toolOpenGL.drawBox();
        glPopMatrix();
    }
    glEndList();

    float targetwidth1 = 0.5;
    float targetwidth2 = 2;
    float targetHeight1 = 0.5;

    // target
    target = glGenLists(1);
    glNewList(target, GL_COMPILE);
    glPushMatrix();
    glRotatef(angle,0,0,1);
    glColor3f(0.7f, 0.5f, 0.3f);
    glTranslatef(-targetPosLength, -targetPosWidth, targetHeight/2);
    glScalef(targetwidth1, targetwidth1, targetHeight);
    toolOpenGL.drawBox();
    glPopMatrix();
    glPushMatrix();
    glRotatef(angle,0,0,1);
    glColor3f(0.7f, 0.5f, 0.3f);
    glTranslatef(-targetPosLength, -targetPosWidth, targetHeight1/2);
    glScalef(targetwidth2, targetwidth2, targetHeight1);
    toolOpenGL.drawBox();
    glPopMatrix();
    glPushMatrix();
    glRotatef(angle,0,0,1);
    glColor3f(0.9f, 0.3f, 0.3f);
    glTranslatef(-targetPosLength, -targetPosWidth, targetHeight);
    glRotatef(90, 0, 1, 0);
    glScalef(7, 7, 1);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    glPushMatrix();glRotatef(angle,0,0,1);
    glColor3f(0.9f, 0.9f, 0.9f);
    glTranslatef(-targetPosLength, -targetPosWidth, targetHeight);
    glRotatef(90, 0, 1, 0);
    glScalef(5, 5, 1.1);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    glPushMatrix();glRotatef(angle,0,0,1);
    glColor3f(0.9f, 0.3f, 0.3f);
    glTranslatef(-targetPosLength, -targetPosWidth, targetHeight);
    glRotatef(90, 0, 1, 0);
    glScalef(3, 3, 1.2);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    glPushMatrix();glRotatef(angle,0,0,1);
    glColor3f(0.9f, 0.9f, 0.9f);
    glTranslatef(-targetPosLength, -targetPosWidth, targetHeight);
    glRotatef(90, 0, 1, 0);
    glScalef(1, 1, 1.3);
    toolOpenGL.drawCylinder();
    glPopMatrix();
    glEndList();

    // logo
    logo = glGenLists(1);
    glNewList(logo, GL_COMPILE);
//    tseLogoTexture = toolOpenGL.loadTexture("tse");
    for(float cor1 = -25; cor1 <= 25; cor1 += 50){
        for(float cor2 = -160; cor2 <= 10; cor2 += 170){
            glColor3f(1.0f, 1.0f, 1.0f);
//            glPushMatrix();
//            glEnable( GL_TEXTURE_2D );
//            glBindTexture(GL_TEXTURE_2D, tseLogoTexture);
//            glBegin(GL_QUADS);
//            glTexCoord2f(0.0f, 0.0f);glVertex3f( cor2, cor1, 5);
//            glTexCoord2f(1.0f, 0.0f);glVertex3f( cor2, cor1+5, 5);
//            glTexCoord2f(1.0f, 1.0f);glVertex3f( cor2, cor1+5, 10);
//            glTexCoord2f(0.0f, 1.0f);glVertex3f( cor2, cor1, 10);
//            glEnd();
//            glDisable( GL_TEXTURE_2D );
//            glDeleteTextures(1, &tseLogoTexture);
//            glPopMatrix();
            toolOpenGL.drawSquareWithTexture("tse",
                                             cor2,cor1,5,
                                             cor2,cor1+5,5,
                                             cor2,cor1+5,10,
                                             cor2,cor1,10);
            glColor3f(0.5f, 0.32f, 0.00f);
            glPushMatrix();
            glTranslatef(cor2, cor1, 5);
            glScalef(0.5, 0.5, 10);
            toolOpenGL.drawBox();
            glPopMatrix();
            glColor3f(0.71f, 0.60f, 0.298f);
            glPushMatrix();
            glTranslatef(cor2, cor1, 0.5);
            glScalef(3, 3, 1);
            toolOpenGL.drawBox();
            glPopMatrix();
            glColor3f(0.5f, 0.32f, 0.00f);
            glPushMatrix();
            glTranslatef(cor2, cor1, 10);
            glScalef(0.5, 0.5, 0.5);
            toolOpenGL.drawSphere();
            glPopMatrix();
        }
    }
    glDeleteTextures(1, &tseLogoTexture);
    glEndList();

    glCallList(ground);
    glCallList(leftWall);
    glCallList(rightWall);
    glCallList(frontWall);
    glCallList(backWall);
    glCallList(target);
    glCallList(logo);

    glDeleteLists(ground,1);
    glDeleteLists(leftWall,1);
    glDeleteLists(rightWall,1);
    glDeleteLists(frontWall,1);
    glDeleteLists(backWall,1);
    glDeleteLists(target,1);
    glDeleteLists(logo,1);
}

