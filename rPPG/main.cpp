// rPPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "ImageProcessingFunctions.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/tracking.hpp"
#include <thread>
#include <math.h>
#include <boost/thread.hpp>
#include "plplot\plstream.h"
#include "RealTimePlot.h"
#include <opencv2/core/utility.hpp>

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
using namespace std;
using namespace cv;

int main()
{
	

	Rect2d roi1;
	Mat frame;
	Mat frame_r;
	int n = 0;
	Mat copyM;
	Ptr<Tracker> tracker1 = TrackerKCF::create();
	RealTimePlot plot = RealTimePlot();
	VideoCapture cap("C:/Users/Haider/source/repos/rPPG/videos/face.mp4");
	cap.set(CAP_PROP_POS_FRAMES,100);
	cap >> frame;
	resize(frame, frame_r, Size(600, 600));
	roi1 = selectROI("tracker", frame_r);
	ImageProcessing tool;

	if (roi1.width == 0 || roi1.height == 0)
		return 0;
	
	
	tracker1->init(frame, roi1);


	for (n = 0;; n++) {

		cap >> frame;

		resize(frame, frame_r, Size(600, 600));

		if (frame.rows == 0 || frame.cols == 0)
			break;

		tracker1->update(frame_r, roi1);

		copyM = frame_r.clone();

		rectangle(frame_r, roi1, Scalar(255, 0, 0), 2, 1);

		imshow("tracker", frame_r);

		plot.plot(n, tool.AveragePixelChannel(copyM(roi1), "red"),
			tool.AveragePixelChannel(copyM(roi1), "blue"),
			tool.AveragePixelChannel(copyM(roi1), "green"));



		if (waitKey(1) == 27) break;
	}



	return 0;
}

