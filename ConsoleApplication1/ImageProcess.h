#pragma once
//HEADER for entering the pixel matrices into OpenCV processing files

//Cpp librarires
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<conio.h>

#include <iostream>
#include <memory>
#include <vector>
#include <Kinect.h>

#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"

#include"KinectInit.h"
#include<string.h>
using namespace cv;
using namespace std;

class ImageProcess {
	
private:
	UINT32 *pixelbuffer;
	Mat img;
	char WindowName[10];
public:
	ImageProcess() {
		img = Mat(CIMG_H, CIMG_W, CV_8UC4, Scalar(0, 0, 0, 0));
		char s[] = "DisplayW1";
		strncpy_s(WindowName, s,sizeof(s));
		namedWindow(WindowName, WINDOW_AUTOSIZE); // Create a window for display.
		imshow(WindowName, img); // Show our image inside it.
	}
	void convert() {
		img = Mat(CIMG_H, CIMG_W, CV_8UC4, pixelbuffer);
		Point p1(300, 0);
		Point p2(840, 810);
		//rectangle(img, p1, p2, Scalar(255, 0, 255));
		imshow(WindowName, img);
	}

	void bufferInit(UINT32 *pixelbuffer) {
		this->pixelbuffer = pixelbuffer;
	}
};
