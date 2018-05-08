#include "KinectInit.h"

//Kinect Initialising for default deature that is obtaining depth stream
void KinectSensor::init() {
	

	//Kinect initialising
	HRESULT hr = GetDefaultKinectSensor(&Kinect); // Pointer reference to kinect to find any kinect device conected 
	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor Recog");
		_getch();
		exit(10);
	}
	Kinect->Open();//opens the sensor


	//Depth frame source initialised
	hr = Kinect->get_DepthFrameSource(&DepthFrameSource);

	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor FrameSource");
		_getch();
		exit(10);
	}

	//depth reader initialised
	hr = DepthFrameSource->OpenReader(&DepthFrameReader);
	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor Reader");
		_getch();
		exit(10);
	}

	//Coordinate mapper for getting distances in camera space
	hr = Kinect->get_CoordinateMapper(&mapper);
	if (FAILED(hr)) {
		printf("mappingfailed");
		_getch();
		exit(10);
	}
	//Frame description to dynamically allocate the required the pointer buffer

	//Additional declaratiopns to get height,width of required streams
	IFrameDescription *FrameDesc;
	DepthFrameSource->get_FrameDescription(&FrameDesc);
	FrameDesc->get_Height(&height);
	FrameDesc->get_Width(&width);
	ReleasePTR(DepthFrameSource);

	//depth stream intialised
	DepthBuffer = new UINT16[width*height];
	feature = 0;

}
void KinectSensor::init(int feature) {

	//Initialising for a different feature- Greyscale depth
	HRESULT hr = GetDefaultKinectSensor(&Kinect); // Pointer reference to kinect to find any kinect device conected 
	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor Recog");
		_getch();
		exit(10);
	}
	Kinect->Open();//opens the sensor

	//obtaining depth frame source 
	hr = Kinect->get_DepthFrameSource(&DepthFrameSource);

	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor FrameSource");
		_getch();
		exit(10);
	}

	//Obtaining depth reader
	hr = DepthFrameSource->OpenReader(&DepthFrameReader);
	if (FAILED(hr)) {
		printf("%s", "Problem with Sensor Reader");
		_getch();
		exit(10);
	}
	
	//initialising coordinate mapper for future computations
	hr = Kinect->get_CoordinateMapper(&mapper);
	if (FAILED(hr)) {
		printf("mapper Init failed");
		_getch();
		exit(10);
	}

	//feature 1 is greyscale depth image
	if (feature == 1) {
		//Additional Declarations
		IFrameDescription *FrameDesc;
		DepthFrameSource->get_FrameDescription(&FrameDesc);
		FrameDesc->get_Height(&height);
		FrameDesc->get_Width(&width);
		//Depth buffer is intialised
		DepthBuffer = new UINT16[width*height];
		this->feature = feature;
		ReleasePTR(DepthFrameSource);
	}
	//feature 2 is colour sensor data
	if (feature == 2) {
		
		//Color frame source intialisation
		hr = Kinect->get_ColorFrameSource(&ColorFrameSource);

		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor FrameSource");
			_getch();
			exit(10);
		}
		//Color frame reader intialisation
		hr = ColorFrameSource->OpenReader(&ColorFrameReader);
		if (FAILED(hr)) {
			printf("%s", "Problem with Sensor Reader");
			_getch();
			exit(10);
		}
		
		//additional declarations for the kinect frame
		IFrameDescription *FrameDesc;
		ColorFrameSource->get_FrameDescription(&FrameDesc);
		FrameDesc->get_Height(&height);
		FrameDesc->get_Width(&width);

		IFrameDescription *FrameDesc2;
		DepthFrameSource->get_FrameDescription(&FrameDesc2);
		FrameDesc2->get_Height(&heightd);
		FrameDesc2->get_Width(&widthd);

		ReleasePTR(DepthFrameSource);
		//color buffer and depth buffer intialised
		ColorBuffer = new UINT32[width*height];
		DepthBuffer = new UINT16[widthd*heightd];
		this->feature = feature;
		ReleasePTR(ColorFrameSource);
		
		printf("--/// %d %d \n ", widthd, heightd);

	}
	printf("- %d %d \n", height, width);

}


UINT16* KinectSensor :: getBuffer() {
	return DepthBuffer;
}

//getting required depth data parameters
void KinectSensor::draw() {
	
	//frame aquired
	HRESULT hr;
	hr = DepthFrameReader->AcquireLatestFrame(&DepthFrame);
	if (FAILED(hr)) {
		//printf("Feature %d Depth Frame problem", this->feature);
		ReleasePTR(DepthFrame);
		return;
	}
	
	//depth data stream acquired
	hr = DepthFrame->CopyFrameDataToArray(width*height, DepthBuffer);
	if (FAILED(hr)) {
		printf("Copying Failed\n");
		return;
	}

	//Max reliable distance and minimum reliable distance parameter for future computation
	hr = DepthFrame->get_DepthMaxReliableDistance(&DepthBufferMaxActual);
	if (FAILED(hr)) {

		printf("MaxFailed\n");

	}

	hr = DepthFrame->get_DepthMinReliableDistance(&DepthBufferMinActual);
	if (FAILED(hr)) {
		printf("MinFailed\n");
	}

	ReleasePTR(DepthFrame);
	copy();
	
}
bool KinectSensor::colordraw(UINT16 *DepthBuffer) {
	
	bool val = false;
	//depth frame aquired
	HRESULT hr;
	/*
	hr = DepthFrameReader->AcquireLatestFrame(&DepthFrame);
	if (FAILED(hr)) {
		//printf("Feature %d Depth Frame problem", this->feature);
		ReleasePTR(DepthFrame);
		return;
	}

	//depth data stream acquired
	hr = DepthFrame->CopyFrameDataToArray(widthd*heightd, DepthBuffer);
	if (FAILED(hr)) {
		ReleasePTR(DepthFrame);
		printf("Copying Failed\n");
		return;
	}
	*/
	//color frame acquired
	hr = ColorFrameReader->AcquireLatestFrame(&ColorFrame);
	if (FAILED(hr)) {
		//printf("Feature %d Frame problem \n", this->feature);
		return false;
	}

	//color data acquired
	hr = ColorFrame->CopyConvertedFrameDataToArray(width *height* 4, (BYTE*)ColorBuffer, ColorImageFormat_Bgra);
	if (FAILED(hr)) {
		ReleasePTR(ColorFrame);
		printf("Copying Failed\n");
		return false;
	}

	//Getting the mapping of the points of the buffer with respect to the position
	if (DepthBuffer != nullptr) {
		hr=mapper->MapColorFrameToCameraSpace(IMG_W*IMG_H, DepthBuffer, CIMG_W*CIMG_H, Position);
		if (FAILED(hr)) {
			printf("Space Mapping failed ");
			return false;
		}
		val = true;
		//printf("Mapping SUCCESSFULL");
	}
	else {
		printf("DepthBuffer not initialised");
	}
	ReleasePTR(ColorFrame);
	copycolor();
	return val;
}

//Releasing pinter to conserve system memory
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

//copy frame data to the array
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

//copy color data to pixelbuffer for display
void KinectSensor::copycolor() {

	for (int i = 0; i < width*height; i++) {
		m_PixelBuffer[i] = ColorBuffer[i];
	}
}

//converting depthh data to greyscale image
UINT32 KinectSensor::greyscale(UINT16 val) {
	UINT8 valnew = val & 0xff;
	return ((valnew << 16) | (valnew << 8) | valnew);
}

 


