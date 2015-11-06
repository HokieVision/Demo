#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>
#include "opencv2/stitching/detail/util.hpp"
#include <iostream>

#include <QDebug>


using namespace cv;
using namespace std;

Mat stitch(Mat frame1, Mat frame2) {
    Mat ret; // The resulting image

    // Frame2 is the only valid frame:
    if (frame1.empty() && !frame2.empty()) {
        return frame2;
    }
    // Frame1 is the only valid frame:
    if (!frame1.empty() && frame2.empty()) {
        return frame1;
    }
    // Frame1 and Frame2 are invalid:
    if (frame1.empty() && frame2.empty()) {
        return ret;
    }

    Stitcher stitcher = Stitcher::createDefault(true);
    // Resolution parameters:
    //    stitcher.setCompositingResol(0.1);
    //    stitcher.setSeamEstimationResol(0.1);
    //    stitcher.setRegistrationResol(0.1);
    //    stitcher.setPanoConfidenceThresh(0.1);

    vector<Mat> vImg; // Stitcher.stitch takes a vector of images as args

    vImg.push_back(frame1);
    vImg.push_back(frame2);

    Stitcher::Status status = stitcher.stitch(vImg, ret);

    if (Stitcher::OK == status) {
        return ret;
    }

    qDebug() << "stitch failed";
    return ret;
}

int main() {
    Mat a = imread("/home/james/Desktop/stitching/stitching/test1.png");
    Mat b = imread("/home/james/Desktop/stitching/stitching/test2.png");
    Mat c = imread("/home/james/Desktop/stitching/stitching/test3.png");
    Mat d = imread("/home/james/Desktop/stitching/stitching/test4.png");
    Mat e = imread("/home/james/Desktop/stitching/stitching/test0.png");

    namedWindow("MyImage",CV_WINDOW_NORMAL);

    // Setup a rectangle to define your region of interest
    cv::Rect myROI(0, 0, 1200, 690); // hard code
    cv::Rect myROI2(0, 0, 1200, 600); // hard code

    // Crop the full image to that image contained by the rectangle myROI
    // Note that this doesn't copy the data
    a = a(myROI);
    b = b(myROI);
    c = c(myROI2);
    d = d(myROI2);

    Mat ret1 = stitch(a,b); // stitch test1 && test2
    Mat ret2 = stitch(c,d); // stitch test3 && test4
    Mat ret3 = stitch(ret1,ret2); // stitch test1-4 together
    Mat res = stitch(ret3, e); // stitch test0-test4 together

    imshow("MyImage",res);
    waitKey(0); // wait for user input interrupt
    imwrite("result1.jpg", res);

    return 0;

}
