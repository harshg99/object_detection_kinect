#include "KinectInit.h"

void KinectSensor::init() {
	HRESULT hr = GetDefaultKinectSensor(&Kinect); // Pointer reference to kinect to find any kinect device conected 
	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor Recog");
		_getch();
		exit(10);
	}
	Kinect->Open();//opens the sensor

	hr = Kinect->get_DepthFrameSource(&DepthFrameSource);

	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor FrameSource");
		_getch();
		exit(10);
	}

	hr = DepthFrameSource->OpenReader(&DepthFrameReader);
	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor Reader");
		_getch();
		exit(10);
	}
	//Frame description to dynamically allocate the required the pointer buffer
	IFrameDescription *FrameDesc;
	DepthFrameSource->get_FrameDescription(&FrameDesc);
	FrameDesc->get_Height(&height);
	FrameDesc->get_Width(&width);
	ReleasePTR(DepthFrameSource);
	DepthBuffer = new UINT16[width*height];
	feature = 0;

}
void KinectSensor::init(int feature) {
	HRESULT hr = GetDefaultKinectSensor(&Kinect); // Pointer reference to kinect to find any kinect device conected 
	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor Recog");
		_getch();
		exit(10);
	}
	Kinect->Open();//opens the sensor
	if (feature == 1) {
		hr = Kinect->get_DepthFrameSource(&DepthFrameSource);

		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor FrameSource");
			_getch();
			exit(10);
		}

		hr = DepthFrameSource->OpenReader(&DepthFrameReader);
		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor Reader");
			_getch();
			exit(10);
		}

		IFrameDescription *FrameDesc;
		DepthFrameSource->get_FrameDescription(&FrameDesc);
		FrameDesc->get_Height(&height);
		FrameDesc->get_Width(&width);
		DepthBuffer = new UINT16[width*height];
		this->feature = feature;
		ReleasePTR(DepthFrameSource);
	}
	if (feature == 2) {
		hr = Kinect->get_ColorFrameSource(&ColorFrameSource);

		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor FrameSource");
			_getch();
			exit(10);
		}

		hr = ColorFrameSource->OpenReader(&ColorFrameReader);
		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor Reader");
			_getch();
			exit(10);
		}

		IFrameDescription *FrameDesc;
		ColorFrameSource->get_FrameDescription(&FrameDesc);
		FrameDesc->get_Height(&height);
		FrameDesc->get_Width(&width);
		ColorBuffer = new UINT32[width*height];
		this->feature = feature;
		ReleasePTR(ColorFrameSource);
	}
	printf("- %d %d \n", height, width);

}
UINT16* KinectSensor :: getBuffer() {
	return DepthBuffer;
}

void KinectSensor::draw() {
	
	HRESULT hr;
	hr = DepthFrameReader->AcquireLatestFrame(&DepthFrame);
	if (FAILED(hr)) {
		return;
	}
	hr = DepthFrame->CopyFrameDataToArray(width*height, DepthBuffer);
	if (FAILED(hr)) {
		ReleasePTR(DepthFrame);
		printf("Copying Failed\n");
		return;
	}
	ReleasePTR(DepthFrame);
	copy();
	
}
void KinectSensor::colordraw() {
	HRESULT hr;
	hr = ColorFrameReader->AcquireLatestFrame(&ColorFrame);
	if (FAILED(hr)) {
		return;
	}
	hr = ColorFrame->CopyConvertedFrameDataToArray(width *height* 4, (BYTE*)ColorBuffer, ColorImageFormat_Bgra);
	if (FAILED(hr)) {
		ReleasePTR(ColorFrame);
		printf("Copying Failed\n");
		return;
	}
	ReleasePTR(ColorFrame);
	copycolor();
}

void KinectSensor::end() {
	ReleasePTR(DepthFrameSource);
	ReleasePTR(DepthFrameReader);
	ReleasePTR(Kinect);
	ReleasePTR(ColorFrame);
	ReleasePTR(ColorFrameSource);
	ReleasePTR(ColorFrameReader);
	ReleasePTR(Kinect);
	ReleasePTR(DepthFrame);
	delete[] m_PixelBuffer ;
	delete[] DepthBuffer; 
	delete[]ColorBuffer;

}

void KinectSensor::copy() {
	for (int i = 0; i < width*height; i++) {
		if (feature == 0) {
			m_PixelBuffer[i] = DepthBuffer[i];
		}
		else {
			m_PixelBuffer[i] = greyscale(DepthBuffer[i]);
		}
	}
}
void KinectSensor::copycolor() {

	for (int i = 0; i < width*height; i++) {
		m_PixelBuffer[i] = ColorBuffer[i];
	}
}
UINT32 KinectSensor::greyscale(UINT16 val) {
	UINT8 valnew = val & 0xff;
	return ((valnew << 16) | (valnew << 8) | valnew);
}
