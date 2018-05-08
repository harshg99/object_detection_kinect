#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <Kinect.h>
#include <iostream>

using namespace cv;
class DepthAnalysis{
private:
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	UINT32 *pixelBuffer;
public:
	float x_rel;
	float y_rel;
	float z_rel;
	DepthAnalysis() {
		p1 = Point(0, 0);
		p2 = Point(0, 0);
		p3 = Point(0, 0);
		p4 = Point(0, 0);
	}
	DepthAnalysis(Point p1, Point p2, Point p3, Point p4) {
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;
	}
	void convertDepth() {
		float fac1=3.75;
		float fac2=2.54717;
		p1.x /= fac1;
		p2.x /= fac1;
		p3.x /= fac1;
		p4.x /= fac1;
		p1.y /= fac2;
		p2.y /= fac2;
		p3.y /= fac2;
		p4.y /= fac2;
		
	}
	void rectangulate(UINT32 *pixelbuffer) {
		pixelBuffer = pixelbuffer;
		int startx = p1.y;
		int starty = p1.x;
		int width = fabs(p2.y-p1.y);
		int length = fabs(p2.x - p1.x);
		if (width == 0 || length == 0) {
			return;
		}
		printf("RECTANGULATED %d %d %d %d\n",width,length,p1.x,p1.y);
		
		printf("\n\n\n\n");
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				int x = startx + i;
				int y = starty + j;
				if (x == startx || y == starty || x == (startx + width-1) || y == (starty + length-1))
				{
					pixelBuffer[x * 512+ y] = 255;
				}
				//printf("%d ", pixelBuffer[x * 512 + y]);
			}
		}
		startx = p3.y;
		starty = p3.x;
		width = fabs(p4.y - p3.y);
		length = fabs(p4.x - p3.x);
		if (width == 0 || length == 0) {
			return;
		}
		printf("RECTANGULATED2 %d %d %d %d\n", width, length,p3.x,p3.y);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				int x = startx + i;
				int y = starty + j;
				if (x == startx || y == starty || x == (startx + width - 1) || y == (starty + length - 1))
				{
					pixelBuffer[x * 512 + y] = 255;
				}
				//printf("%d ", pixelBuffer[x * 512 + y]);
			}
		}
	}
};