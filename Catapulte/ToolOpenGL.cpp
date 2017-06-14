#include "ToolOpenGL.h"

ToolOpenGL::ToolOpenGL(){
    chargerImage("./texture/grass.bmp",0);
    chargerImage("./texture/tse.bmp",1);
    chargerImage("./texture/wood.bmp",2);
    chargerImage("./texture/wood1.bmp",3);
}

void ToolOpenGL::chargerImage(QString image,int num){
    QPixmap buf1=QPixmap(image);
    QImage buf=buf1.toImage();
    //buf.load(Image);
    tex[num]=QGLWidget::convertToGLFormat(buf);
}

unsigned int ToolOpenGL::loadTex(int num){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tex[num].width(), tex[num].height(),GL_RGBA, GL_UNSIGNED_BYTE, tex[num].bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return texture;
}

unsigned int ToolOpenGL::loadTex(QString image){
    int num = -1;
    if(image == "grass"){
        num = 0;
    } else if(image == "tse"){
        num = 1;
    } else if(image == "wood"){
        num = 2;
    } else if(image == "wood1"){
        num = 3;
    }
    return loadTex(num);
}

//unsigned int ToolOpenGL::loadTexture(string image){
//    GLuint texture;
//    FILE* img = NULL;
//    img = fopen(image.c_str(),"rb");
//    unsigned long bWidth = 0;
//    unsigned long bHeight = 0;
//    unsigned long size = 0;
//    fseek(img,18,SEEK_SET);
//    fread(&bWidth,4,1,img);
//    fread(&bHeight,4,1,img);
//    fseek(img,0,SEEK_END);
//    size = int(ftell(img)) - 54;
//    unsigned char *data = (unsigned char*)malloc(size);
//    fseek(img,54,SEEK_SET);    // image data
//    fread(data,size,1,img);
//    fclose(img);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bWidth, bHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    if (data){
//        free(data);
//    }
//    return texture;
//}

void ToolOpenGL::drawSphere(){
    glutSolidSphere(1.0, 50, 50);
}

void ToolOpenGL::drawCylinder(){
    GLUquadricObj *quadratic;
    quadratic=gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);
    gluCylinder(quadratic,0.5,0.5,1,50,50);
    drawCircleArea(0.0, 0.0, 0.0, 0.5, 50);
    drawCircleArea(0.0,0.0,1,0.5,50);
}

void ToolOpenGL::drawCircleArea(float cx, float cy, float cz, float r, int num_segments){
    GLfloat vertex[4];
    const GLfloat delta_angle = 2.0*3.1415926/num_segments;
    glBegin(GL_TRIANGLE_FAN);
    vertex[0] = cx;
    vertex[1] = cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    //draw the vertex on the contour of the circle
    for(int i = 0; i < num_segments ; i++){

        vertex[0] = std::cos(delta_angle*i) * r + cx;
        vertex[1] = std::sin(delta_angle*i) * r + cy;
        vertex[2] = cz;
        vertex[3] = 1.0;
        glVertex4fv(vertex);
    }
    vertex[0] = 1.0 * r + cx;
    vertex[1] = 0.0 * r + cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    glEnd();
}

void ToolOpenGL::drawSquare( float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l){
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( a, b, c);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( d, e, f);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( g, h, i);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( j, k, l);
    glEnd();
}

void ToolOpenGL::drawSquareWithTexture(QString image, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l){
    GLuint texture = loadTex(image);
    glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( a, b, c);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( d, e, f);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( g, h, i);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( j, k, l);
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glDeleteTextures(1, &texture);
}


void ToolOpenGL::drawBox(){
    glutSolidCube(1);
}

void ToolOpenGL::drawBoxWithTexture(QString image){
    GLuint texture = loadTex(image);
    glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( -0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( 0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( 0.5, 0.5, -0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( -0.5, 0.5, -0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( -0.5, -0.5, 0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( 0.5, -0.5, 0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( 0.5, 0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( -0.5, 0.5, 0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( -0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( 0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( 0.5, -0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( -0.5, -0.5, 0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( -0.5, 0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( 0.5, 0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( 0.5, 0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( -0.5, 0.5, 0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( -0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( -0.5, 0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( -0.5, 0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( -0.5, -0.5, 0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);glVertex3f( 0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);glVertex3f( 0.5, 0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);glVertex3f( 0.5, 0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);glVertex3f( 0.5, -0.5, 0.5);
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glDeleteTextures(1, &texture);
}
