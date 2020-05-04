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
#include <mlpack/core.hpp>
#include "MathSignal.h"
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
	int size_buffer = 0;
	Mat copyM;
	Ptr<Tracker> tracker1 = TrackerKCF::create();
	RealTimePlot plot1 = RealTimePlot();
	
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

		size_buffer += 1;
		cap >> frame;

		resize(frame, frame_r, Size(600, 600));

		if (frame.rows == 0 || frame.cols == 0)
			break;

		tracker1->update(frame_r, roi1);

		copyM = frame_r.clone();

		rectangle(frame_r, roi1, Scalar(255, 0, 0), 2, 1);

		imshow("tracker", frame_r);
		
		
		//plot1.plot(n,f.filter(tool.AveragePixelChannel(copyM(roi1), "red")), tool.AveragePixelChannel(copyM(roi1), "red"),
		 //	tool.AveragePixelChannel(copyM(roi1), "blue"),
		 // tool.AveragePixelChannel(copyM(roi1), "green"));

		if (size_buffer > 100) {
			
			float detrendred = MathSignal::DetrendData(tool.AveragePixelChannel(copyM(roi1), "red"));
			plot1.plot(n, detrendred, tool.AveragePixelChannel(copyM(roi1), "red"),
				tool.AveragePixelChannel(copyM(roi1), "blue"),
				tool.AveragePixelChannel(copyM(roi1), "green"));
			std::cout << "detrend: " << detrendred << std::endl;
			std::cout << "red: " <<tool.AveragePixelChannel(copyM(roi1), "red") << std::endl;

		}
		

		if (waitKey(1) == 27) break;
	}



	return 0;
}

