// ModelTrainingAlgos.cpp : Defines the entry point for the console application.


//Standard include directories for the kinect images
#include<opencv2\core.hpp>
#include<Kinect.h>
#include<opencv2\highgui.hpp>
#include<opencv2\imgcodecs.hpp>

//standard  libraries
#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<fstream>

#define CIMG_W 1920
#define CIMG_H 1080

using namespace cv;
using namespace std;

ofstream file;
ofstream filep;
template<typename T>
void ReleasePTR(T &ptr) {
	if (ptr != nullptr) {
		ptr->Release();
		ptr = nullptr;
	}
}


class TrainModel{
public:
	Mat img;
	char WindowName[10];
	TrainModel() {
		img = Mat(CIMG_H, CIMG_W, CV_8UC4, Scalar(0, 0, 0, 0));
		char s[] = "DisplayW1";
		strncpy_s(WindowName, s, sizeof(s));
		namedWindow(WindowName, WINDOW_AUTOSIZE); // Create a window for display.
		imshow(WindowName, img); // Show our image inside it.
		printf("%s", WindowName);
		waitKey(25);
	
	}
	void initimg(UINT32 *pixelbuffer) {
		img = Mat(CIMG_H, CIMG_W, CV_8UC4, pixelbuffer);
		imshow(WindowName, img);
		waitKey(25);
	}
	
	void trainnegative(int j) {
		if (img.empty()) {
			return;
		}
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(100);
		String f_name = "D:/nus/UROP/TrainingData/NegativeObj/" + to_string(j) + ".jpg";
		String ft_name= "D:/nus/UROP/TrainingData/NegativeObj/" + to_string(j) + ".jpg";
		try{
			imwrite(f_name, img,compression_params);
			file << ft_name << endl;
		}
		catch (runtime_error& ex) {
			fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
			return;
		}
	}
	void trainpositive(int j) {
		if (img.empty()) {
			return;
		}
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(100);
		String f_name = "D:/nus/UROP/TrainingData/Positive/"+to_string(j)+".jpg";
		String ft_name= "Positive/"+to_string(j)+".jpg";
		try {
			imwrite(f_name, img,compression_params);
			ft_name = ft_name + " 1 30 12 90 72";
			filep << ft_name << endl;

		}
		catch (runtime_error& ex) {
			fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
			return;
		}
	}
};
class Kinect
{
public:

	int height;
	int width;
	IKinectSensor * kinect;
	IColorFrame * ColorFrame = nullptr;
	IColorFrameSource * ColorFrameSource = nullptr;
	IColorFrameReader *ColorFrameReader = nullptr;
	UINT32 *ColorBuffer = nullptr;
	UINT32 *m_PixelBuffer = nullptr;

	void SetPixelBuffer(UINT32 *PixelBuffer) {
		m_PixelBuffer = PixelBuffer;
	}
	void init() {
		HRESULT hr = GetDefaultKinectSensor(&kinect); // Pointer reference to kinect to find any kinect device conected 
		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor Recog");
			_getch();
			exit(10);
		}
		printf("kinect\n");
		kinect->Open();//opens the sensor
		hr = kinect->get_ColorFrameSource(&ColorFrameSource);

		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor FrameSource");
			_getch();
			exit(10);
		}
		printf("framesource\n");
		hr = ColorFrameSource->OpenReader(&ColorFrameReader);
		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor Reader");
			_getch();
			exit(10);
		}
		printf("framereader\n");
		IFrameDescription *FrameDesc;
		ColorFrameSource->get_FrameDescription(&FrameDesc);
		FrameDesc->get_Height(&height);
		FrameDesc->get_Width(&width);
		printf("%d %d \n",height,width);
		ColorBuffer = new UINT32[width*height];
		ReleasePTR(ColorFrameSource);

	}
	void colordraw() {
		HRESULT hr;
		hr = ColorFrameReader->AcquireLatestFrame(&ColorFrame);
		if (FAILED(hr)) {
			return;
		}
		hr = ColorFrame->CopyConvertedFrameDataToArray(width *height * 4, (BYTE*)ColorBuffer, ColorImageFormat_Bgra);
		if (FAILED(hr)) {
			ReleasePTR(ColorFrame);
			printf("Copying Failed\n");
			return;
		}
		//printf("Data recieved");
		ReleasePTR(ColorFrame);
		copycolor();
	}
	void copycolor() {
		for (int i = 0; i < width*height; i++) {
			m_PixelBuffer[i] = ColorBuffer[i];
		}
	}
	void end() {
		
		ReleasePTR(kinect);
		ReleasePTR(ColorFrame);
		ReleasePTR(ColorFrameSource);
		ReleasePTR(ColorFrameReader);
		ReleasePTR(kinect);
		delete[] m_PixelBuffer;
		delete[]ColorBuffer;

	}

};

TrainModel model;
int main()
{
	file.open("Neg.txt", ios::out);
	filep.open("Pos.txt", ios::out);
	Kinect k=Kinect();
	k.init();
	UINT32 *CBuffer=new UINT32[CIMG_W * CIMG_H];
	if (CBuffer == nullptr)
		return 4;
	//clear the pixel buffer
	memset(CBuffer, 0, CIMG_W * CIMG_H * 4);
	k.SetPixelBuffer(CBuffer);
	printf("Positive-1 Negative-2\n");
	int opt;
	scanf_s("%d", &opt);
	int j = 0;
	int max;
	if (opt == 1) {
		max = 50;
	}
	else {
		max = 500;
	}
	while (j<max) {
		k.colordraw();
		model.initimg(CBuffer);
		if (opt == 1) {
			model.trainpositive(j);
		}
		else {
			model.trainnegative(j);
		}
		++j;
	}
	k.end();
}

