#include "ImageProcessingFunctions.h"


 float ImageProcessing::AveragePixelChannel(Mat ROI, std::string color)
{
	float total = 0;
	int intcolor = 0;
	if (color == " blue") intcolor = 0;
	if (color == "red") intcolor = 2;
	if (color == "green") intcolor = 1;
	
	for (int i = 0; i < ROI.rows; i++)
	{
		for (int j = 0; j < ROI.cols; j++)
		{

			total += ROI.at<Vec3b>(i, j)[intcolor];
			
		}
	}

	return (total / (ROI.size().width *ROI.size().height));
}

 Rect2d ImageProcessing::GetInitROI(Mat resize_frame) {

	 Mat frame_gray;
	 cvtColor(resize_frame, frame_gray, COLOR_BGR2GRAY);
	 equalizeHist(frame_gray, frame_gray);
	 std::vector<Rect> faces;
	 Rect scaled;
	 Mat ROI;
	 Mat copy_resize = resize_frame.clone();

	 face_cascade.detectMultiScale(frame_gray, faces);
	 if (faces.size() > 0)
	 {
		 for (size_t i = 0; i < faces.size(); i++)
		 {

			 scaled = faces.at(i);
			 scaled.y -= 20;
			 scaled.height /= 3.7;
			 scaled.width -= 210;
			 scaled.x += 120;
			 //rectangle(resize_frame, scaled, Scalar(255, 255, 255), 4);
		 }

		 return Rect(scaled.x, scaled.y, 90, 100);

	 }
	 else {
		 return Rect(0, 0, 0, 0);
	 }


 }