#pragma once


//some often used C standard library header files
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<conio.h>

//some often used STL header files
#include <iostream>
#include <memory>
#include <vector>


#include<Kinect.h>

# define IMG_W 512
# define IMG_H 424
# define CIMG_W 1920
# define CIMG_H 1080

template<typename T>
void ReleasePTR(T &ptr) {
	if (ptr != nullptr) {
		ptr->Release();
		ptr = nullptr;
	}
}
class KinectSensor {
private:
	
	//gets required feature
	int feature;

	//heright and width of frame
	int height=0;
	int width=0; 

	//depth height and width
	int heightd;
	int widthd;


protected:
	//kinect sensor pointer
	IKinectSensor * Kinect = nullptr;
	
	//depth frame reader
	IDepthFrameReader * DepthFrameReader = nullptr;
	
	//depth frame source
	IDepthFrameSource * DepthFrameSource = nullptr;
	
	//depth frame
	IDepthFrame * DepthFrame = nullptr;
	
	//color frame
	IColorFrame * ColorFrame = nullptr;
	
	//color frame source
	IColorFrameSource * ColorFrameSource = nullptr;
	
	//color frame reader
	IColorFrameReader *ColorFrameReader = nullptr;
	
	//depth buffer
	UINT16 *DepthBuffer = nullptr;
	
	//color buffer
	UINT32 *ColorBuffer = nullptr;
	
	//pixel buffer
	UINT32 *m_PixelBuffer = nullptr;
	
	//coordinate mappetr
	ICoordinateMapper *mapper = nullptr;
	
	//positions of the pixels in color frame in camera space 
	CameraSpacePoint *Position=nullptr;
	
public:

	//pixel buffer init
	void SetPixelBuffer(UINT32 *PixelBuffer) {
		m_PixelBuffer = PixelBuffer;
	}
	
	//Description in KinitInitClassFunc.cpp
	void init();

	void init(int feature);
	
	UINT16* getBuffer();
	
	USHORT DepthBufferMaxActual;
	
	USHORT DepthBufferMinActual;
	
	bool colordraw(UINT16 *DepthBuffer);
	
	void copycolor();

	void draw();

	void end();

	void copy();

	UINT32 greyscale(UINT16 val);
	
	//Camera space point initialiation
	void InitCameraSpacePoint(CameraSpacePoint *p) {
		Position = p;
	}

};