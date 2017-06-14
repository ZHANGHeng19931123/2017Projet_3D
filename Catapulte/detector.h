#ifndef DETECTOR_H
#define DETECTOR_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;
using namespace std;

class Detector
{
public:
    Detector(String path);
    void open(String path);
    void detect(Mat frame, int (&data)[2]);
    bool isOpened(){return opened;}
private:
    CascadeClassifier myDetector;
    Mat frame;
    String xmlPath;
    bool opened = false;
};


#endif // DETECTOR_H
