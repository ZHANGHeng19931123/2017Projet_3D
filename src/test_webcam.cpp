#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "toolimage.h"
#include "detector.h"

using namespace cv;
using namespace std;

CascadeClassifier palmDetector;
CascadeClassifier fistDetector;
String palmDetectorPath = "/home/heng/Documents/TSE/FISE2/Semestre 8/Projet 3D/xmlFiles/palm2.xml";
String fistDetectorPath = "/home/heng/Documents/TSE/FISE2/Semestre 8/Projet 3D/xmlFiles/face.xml";

void detectAndDisplay( CascadeClassifier detector, String window_name, Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    detector.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    }
    imshow( window_name, frame );
}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        return -1;
    }
    Mat frame;
    namedWindow("WebCam",WINDOW_AUTOSIZE);
    if( !palmDetector.load( palmDetectorPath ) ){ printf("--(!)Error loading\n"); return -1; };
    if( !fistDetector.load( fistDetectorPath ) ){ printf("--(!)Error loading\n"); return -1; };
    toolimage ti;
    detector d = detector(fistDetectorPath);
    for(;;)
    {
        cap >> frame; // get a new frame from camera
        ti.resizeImage(frame, frame, 320, 240);
        ti.flipImage(frame, frame, "y");
        detectAndDisplay(fistDetector, "WebCam",frame);
        int temp[3] = {0,0,0};
        d.detect(frame, temp);
        cout << temp[0] << temp[1] << temp[2] << endl;

        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
