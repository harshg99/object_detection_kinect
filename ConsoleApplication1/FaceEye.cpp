#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<Kinect.h>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
/* Function Headers */
/* Global variables */
class FaceEye {
public:
	String face_cascade_name ;
	String eyes_cascade_name;
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	String window_name = "Capture - Face detection";
	/* @function main */
	FaceEye() {
		face_cascade_name = "F:/Libraries/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
		eyes_cascade_name = "F:/Libraries/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
		
		//-- 1. Load the cascades
		if (!face_cascade.load(face_cascade_name))
		{
			printf("--(!)Error loading face cascade\n");
			return;
		}
		else {
			printf("Success\n");
		}
		if (!eyes_cascade.load(eyes_cascade_name)) {
			printf("--(!)Error loading eyes cascade\n");
			return;
		}
	}
	void detect(UINT32* pixelbuffer)
	{
		Mat frame = Mat(1080, 1920, CV_8UC4, pixelbuffer);
		if (frame.empty()) {
			return;
		}
		//-- 2. Read the video stream
			detectAndDisplay(frame);
			
	}
	/* @function detectAndDisplay */
	void detectAndDisplay(Mat frame)
	{
		std::vector<Rect> faces;
		Mat frame_gray;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		printf("%d\n",&frame_gray);
		//printf("%d",&frame);
		face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			printf("%d %d %d %d", faces[i].x, faces[i].width, faces[i].y, faces[i].height);
			ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
			Mat faceROI = frame_gray(faces[i]);
			std::vector<Rect> eyes;
			//-- In each face, detect eyes
			eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
				int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
				circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
			}
		}
		
		//-- Show what you got
		imshow(window_name, frame);
	}
};