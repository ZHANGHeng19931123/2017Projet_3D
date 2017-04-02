#ifndef DETECTOR_H
#define DETECTOR_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;
using namespace std;

class detector
{
private:
    CascadeClassifier myDetector;
    Mat frame;
    String xmlPath;
public:
    detector(String path);
    void detect(Mat frame, int (&data)[3]);
};


#endif // DETECTOR_H
