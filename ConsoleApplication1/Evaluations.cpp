#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<conio.h>

//some often used STL header files
#include <iostream>
#include <memory>
#include <vector>

#include "KinectInit.h"
#include "ImageProcess.h"

using namespace cv;
class DepthStreamDisplay
{
private:
	UINT16 *depthBuffer;
	UINT16 MaxRel;
	UINT16 MinRel;
	BYTE *PixelBuffer;
	int factor;
	Mat depthimg;
public:
	void init(UINT16 *depthBuffer,UINT16 MaxRel,UINT16 MinRel) {
		this->depthBuffer = depthBuffer;
		factor = MaxRel / 256;
		this->MaxRel = MaxRel;
		this->MinRel = MinRel;
		PixelBuffer = new BYTE(512 * 424);
		depthimg = Mat(424, 512, CV_8UC4, Scalar(0, 0, 0, 0));
		namedWindow("MyDepth", WINDOW_AUTOSIZE);
		imshow("MyDepth", depthimg);
	}
	//Test Code for converting depth image 
	/*
	void eval() {
		
		for (int i = 0; i < 512 * 424; i++) {
			//if (depthBuffer[i/4] <= MaxRel && depthBuffer[i/4] >= MinRel) {
				//intensity = depthBuffer[i/4] / factor;
			//}
			PixelBuffer[i] = 0;
		}
		
		depthimg = Mat(424, 512, CV_8U,PixelBuffer);
		imshow("MyDepth", depthimg);
		
	}
		*/
};

//code for printing a test square on the depth image for analysis purpose
inline void printSquare(UINT32 *pixelbuffer) {
	int starty = 251;
	int startx = 207;
	int pwidth = 10;
	printf("\n\n\n\n");
	for (int i = 0; i < pwidth; i++) {
		for (int j = 0; j < pwidth; j++) {
			int x = startx + i;
			int y = starty + j;
			if (x == startx || y == starty || x == (startx + 9) || y == (starty + 9))
			{
				pixelbuffer[x * 512 + y] = 0;
			}
			
		}
		
	}
}

//overloaded function to print sqaure on pixel matrix at some point with some width
inline void printSquare(UINT32 *pixelbuffer,Point p1,int width) {
	int starty = p1.x;
	int startx = p1.y;
	int pwidth = width;
	printf("\n\n\n\n");
	for (int i = 0; i < pwidth; i++) {
		for (int j = 0; j < pwidth; j++) {
			int x = startx + i;
			int y = starty + j;
			if (x == startx || y == starty || x == (startx + width-1) || y == (starty + width-1))
			{
				pixelbuffer[x * 1920 + y] = 0;
			}
			
		}
		
	}
}


//code to ascertain the distance of thee identified object 
inline CameraSpacePoint ApproxCoords(CameraSpacePoint *Buffer1, Point P1, Point P2) {
	
	CameraSpacePoint Avg;
	Avg.X = 0;
	Avg.Y = 0;
	Avg.Z = 0;

	//condition test
	if (Buffer1 == nullptr) {
		return Avg;
	} 
	
	//run through the points in the identified block to analyse the distance

	int count = 0;
	for (int i = P1.y; i < P2.y; i++) {
		for (int j = P1.x; j < P2.x; j++) {

			int pos = 1920 * i + j;
			CameraSpacePoint p = Buffer1[pos];
			
			if (p.X == INFINITY || p.Y == INFINITY || p.Z == INFINITY
				|| p.X == 0 || p.Y == 0 || p.Z == 0
				|| p.X == -INFINITY || p.Y == -INFINITY || p.Z == -INFINITY)
				{
					count++;
					break;
				}
				Avg.X += p.X;
				Avg.Y += p.Y;
				Avg.Z += p.Z;
			}
		}
	
		int w = fabs(P1.y - P2.y);
		int h = fabs(P2.x - P1.x);
		if (count == w * h) {
			printf("Distance not found");
			return {-1,-1,-1};
		}
		Avg.X /= (w*h-count);
		Avg.Y /= (w*h-count);
		Avg.Z /= (w*h-count);
		return Avg;

	//exception handle
	
	return Avg;
}

//overloaded function when two points are not mentioned 
inline CameraSpacePoint ApproxCoords(CameraSpacePoint *Buffer1) {
	Point p1(350, 200);
	Point p2(400, 250);
	return ApproxCoords(Buffer1, p1, p2);
}


inline void stringify(CameraSpacePoint P1, CameraSpacePoint P2,char *data) {
	string Temp = to_string((int)(P1.X)) + "," + to_string((int)(P1.Y)) + "," + to_string((int)(P1.Z))
		+ "," + to_string((int)(P2.X)) + "," + to_string((int)(P2.Y)) + "," + to_string((int)(P2.Z))+",";
	printf("The sent string%s \n", Temp);
	strcpy_s(data,sizeof(Temp),Temp.c_str());
}