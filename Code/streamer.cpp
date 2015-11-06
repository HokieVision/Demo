#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>
#include "opencv2/stitching/detail/util.hpp"
#include <iostream>

#include <QDebug>

using namespace cv;
using namespace std;

// Function used to capture a streamed video
void stream() {
    Mat ret;
    namedWindow("stream",CV_WINDOW_NORMAL);

    QVector<Mat> all;

    VideoCapture cap;

    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    // We have been streaming using the Android application 'IP Webcam'
    if(!cap.open("http://192.168.1.138:8080/video?action=stream?dummy=param.mjpg"))
        return;

    // Extract each video frame:
    for(;;)
    {
          Mat frame;
          cap >> frame;
          all << frame;
          if( frame.empty() ) break; // end of video stream
          imshow("stream", frame);
          if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC
    }

    // Iterate through each video frame:
    for (int i = 0; i < all.size(); i+=1) {
        imshow("stream", all[i]);
        waitKey(0);
        s(ret, all[i]);
    }

    // the camera will be closed automatically upon exit
    // cap.close();
}
