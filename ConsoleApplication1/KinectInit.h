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
	int feature;
	int height=0;
	int width=0;
protected:
	IKinectSensor * Kinect = nullptr;
	IDepthFrameReader * DepthFrameReader = nullptr;
	IDepthFrameSource * DepthFrameSource = nullptr;
	IDepthFrame * DepthFrame = nullptr;
	IColorFrame * ColorFrame = nullptr;
	IColorFrameSource * ColorFrameSource = nullptr;
	IColorFrameReader *ColorFrameReader = nullptr;
	UINT16 *DepthBuffer = nullptr;
	UINT32 *ColorBuffer = nullptr;
	UINT32 *m_PixelBuffer = nullptr;
public:
	void SetPixelBuffer(UINT32 *PixelBuffer) {
		m_PixelBuffer = PixelBuffer;
	}
	

	void init();
	void init(int feature);
	UINT16* getBuffer();
	void colordraw();
	void copycolor();
	void draw();
	void end();
	void copy();
	UINT32 greyscale(UINT16 val);
};