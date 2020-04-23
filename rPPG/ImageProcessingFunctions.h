#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <thread>
#include <math.h>
using namespace cv;

class ImageProcessing {
public:

	  float AveragePixelChannel(Mat image,std::string color);
	  Rect2d GetInitROI(Mat resize_frame);
	  ImageProcessing() {
		  face_cascade.load("C:/Users/Haider/Desktop/haarcascade_frontalface_alt.xml");
	  }
	




public:
	cv::CascadeClassifier face_cascade;
};

