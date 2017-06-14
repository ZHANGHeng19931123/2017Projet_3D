#include "detector.h"

Detector::Detector(String path){
    open(path);
}

void Detector::open(String path){
    if(!this->myDetector.load(path)){
        cout << "--(!)Error loading "+path << endl;
    }else{
        opened = true;
    }
}

void Detector::detect(Mat frame, int (&data)[2])
{
    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    myDetector.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    if(faces.size() != 1){
        data[0] = 0;
        data[1] = 0;
    }else{
        data[0] = faces[0].x;
        data[1] = faces[0].y;
    }
}
