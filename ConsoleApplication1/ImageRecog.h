#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <Kinect.h>
#include <iostream>
#include <stdio.h>
#include "KinectInit.h"

using namespace std;
using namespace cv;

class detect {
private:
	String cascade_name;
	String cascade_name_O;
	CascadeClassifier cascade;
	CascadeClassifier cascadeO;
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	String window_name = "Capture-detection";

public:
	detect() {
		cascade_name = "D:/nus/UROP/TrainingData/CascadeTrain/TargetCascade/cascade.xml";
		if (!cascade.load(cascade_name)) { 
			printf("--(!)Error loading cascade\n");
			return;
		};
		cascade_name_O= "D:/nus/UROP/TrainingData/CascadeTrain/Object1Cascade/cascade.xml";
		if (!cascadeO.load(cascade_name_O)) {
			printf("--(!)Error loading cascade\n");
			return;
		};
	}
	detect(String cascade_name) {
		this->cascade_name = cascade_name;
		if (!cascade.load(cascade_name)) { 
			printf("--(!)Error loading cascade\n"); 
			return; 
		};

	}
	void recog(UINT32 *Frame_ext)
	{
		
		Mat frame=Mat(CIMG_H, CIMG_W, CV_8UC4, Frame_ext);
		//-- 1. Load the cascades
		if (frame.empty()) {
			return ;
		}
		detectAndDisplay(frame);
	}
	void detectAndDisplay(Mat frame)
	{
		std::vector<Rect> detect;
		std::vector<Rect> detect2;
		Mat frame_gray;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		//-- Detect faces
		this->p1=Point(-1,-1);
		this->p2 = Point(-1, -1);
		this->p3 = Point(-1, -1); 
		this->p4 = Point(-1, -1);
		cascade.detectMultiScale(frame_gray, detect, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		cascadeO.detectMultiScale(frame_gray, detect2, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, Size(20, 20));
			for (size_t i = 0; i < detect.size(); i++)
			{
				Point p1(detect[i].x, detect[i].y);
				Point p2(detect[i].x + detect[i].width , detect[i].y + detect[i].height );
				this->p1 = p1;
				this->p2 = p2;
				rectangle(frame, p1, p2, Scalar(255, 0, 255));
				//printf("%d %d ", detect[i].x, detect[i].y);
			}
			for (size_t i = 0; i <detect2.size(); i++)
			{
				Point p3(detect2[i].x, detect2[i].y);
				Point p4(detect2[i].x + detect2[i].width, detect2[i].y + detect2[i].height);
				rectangle(frame, p3, p4, Scalar(255, 255, 0));
				this->p3 = p3;
				this->p4 = p4;
				//printf("-- %d %d || ", detect2[i].x, detect2[i].y);
			}
			imshow(window_name, frame);
			//imshow("blob", frame_gray);	
	}
	Point ret_P1() {
		return p1;
	}
	Point ret_P2() {
		return p2;
	}
	Point ret_P3() {
		return p3;

	}
	Point ret_P4() {
		return p4;
	}
};
