#include "toolimage.h"

void ToolImage::resizeImage(Mat img, Mat &dst, int rows, int cols){
    Size size(rows,cols);//the dst image size,e.g.100x100
    resize(img,dst,size);//resize image
}

void ToolImage::flipImage(Mat img, Mat &dst, String way)
{
    if (way == "x")
    {
        flip(img, dst, 0);
    }
    else if(way == "y")
    {
        flip(img, dst, 1);
    }
    else if(way == "both")
    {
        flip(img, dst, -1);
    }
}
