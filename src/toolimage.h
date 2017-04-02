#ifndef TOOLIMAGE_H
#define TOOLIMAGE_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;
using namespace std;

class toolimage
{
public:
    void resizeImage(Mat img, Mat &dst, int rows, int cols);
    void flipImage(Mat img, Mat &dst, String way);
};

#endif // TOOLIMAGE_H
