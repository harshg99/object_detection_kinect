#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <conio.h> 
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "jackylib.h"
namespace handGesture {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;
	using namespace std;
	using namespace jacky_lib;
	const int FRAME_WIDTH = 640;	// Video frame
	const int FRAME_HEIGHT = 360;	// Video fram size
	int ismyframeuse = 0;
	int palm_radius;
	CascadeClassifier face_cascade;
	//Mat mybackground = null;
	float radius_palm_center;
	bool showmyhull = true;
	bool showcondefects = true;
	cv::Point middle;
	vector<Rect> faces;
	cv::Point center;
	cv::Rect boundingBox;
	VideoCapture videocap;
	Mat frame,myframe;
	int lengthMin;
	int angleMax;
	int angleMin;
	mat2picture Mat2Bitmap;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: delegate void delegates(int lengMin);
	private: System::Windows::Forms::Button^  btnProcess;
	private: System::Windows::Forms::PictureBox^  ptbVideo;
	private: System::Windows::Forms::TrackBar^  trbAnglemin;


	private: System::Windows::Forms::TrackBar^  trbLengmin;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TrackBar^  trbAnglemax;
	private: System::Windows::Forms::Label^  label3;

	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnProcess = (gcnew System::Windows::Forms::Button());
			this->ptbVideo = (gcnew System::Windows::Forms::PictureBox());
			this->trbAnglemin = (gcnew System::Windows::Forms::TrackBar());
			this->trbLengmin = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->trbAnglemax = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbVideo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbAnglemin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbLengmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbAnglemax))->BeginInit();
			this->SuspendLayout();
			// 
			// btnProcess
			// 
			this->btnProcess->Location = System::Drawing::Point(685, 428);
			this->btnProcess->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnProcess->Name = L"btnProcess";
			this->btnProcess->Size = System::Drawing::Size(119, 113);
			this->btnProcess->TabIndex = 0;
			this->btnProcess->Text = L"Start";
			this->btnProcess->UseVisualStyleBackColor = true;
			this->btnProcess->Click += gcnew System::EventHandler(this, &MainForm::btnProcess_Click);
			// 
			// ptbVideo
			// 
			this->ptbVideo->Location = System::Drawing::Point(16, 15);
			this->ptbVideo->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->ptbVideo->Name = L"ptbVideo";
			this->ptbVideo->Size = System::Drawing::Size(788, 402);
			this->ptbVideo->TabIndex = 1;
			this->ptbVideo->TabStop = false;
			// 
			// trbAnglemin
			// 
			this->trbAnglemin->Location = System::Drawing::Point(96, 425);
			this->trbAnglemin->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->trbAnglemin->Maximum = 100;
			this->trbAnglemin->Name = L"trbAnglemin";
			this->trbAnglemin->Size = System::Drawing::Size(581, 56);
			this->trbAnglemin->TabIndex = 2;
			this->trbAnglemin->Value = 20;
			// 
			// trbLengmin
			// 
			this->trbLengmin->Location = System::Drawing::Point(92, 506);
			this->trbLengmin->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->trbLengmin->Maximum = 100;
			this->trbLengmin->Name = L"trbLengmin";
			this->trbLengmin->Size = System::Drawing::Size(581, 56);
			this->trbLengmin->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 428);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Min Angle";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 508);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(66, 17);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Min Leng";
			// 
			// trbAnglemax
			// 
			this->trbAnglemax->Location = System::Drawing::Point(96, 466);
			this->trbAnglemax->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->trbAnglemax->Maximum = 360;
			this->trbAnglemax->Name = L"trbAnglemax";
			this->trbAnglemax->Size = System::Drawing::Size(581, 56);
			this->trbAnglemax->TabIndex = 2;
			this->trbAnglemax->Value = 200;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 470);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(73, 17);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Max Angle";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(820, 556);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trbLengmin);
			this->Controls->Add(this->trbAnglemax);
			this->Controls->Add(this->trbAnglemin);
			this->Controls->Add(this->ptbVideo);
			this->Controls->Add(this->btnProcess);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbVideo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbAnglemin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbLengmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbAnglemax))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void btnProcess_Click(System::Object^  sender, System::EventArgs^  e) {
		if (btnProcess->Text == "Start")
		{
			videocap.open(0);
			if (!videocap.isOpened()) {
				MessageBox::Show("Fail to open video");
				_getch();
				return;
			}
			videocap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH); // Set video frame size
			videocap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

			face_cascade.load("haarcascade_frontalface_alt.xml");
			
			btnProcess->Text = "Stop";
			backgroundWorker1->RunWorkerAsync();
		}
		else
		{
			btnProcess->Text = "Start";
			backgroundWorker1->CancelAsync();
			
			
		}

	}
	private: Rect facedetect(Mat frame, CascadeClassifier facecad)
	{
		Mat frame_gray;
		Rect p;
		//Initialize
		p.height = 0;
		p.width = 0;
		p.x = 0;
		int maxarea = -1;
		int maxareai = -1;
		p.y = 0;
		cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);
		cv::equalizeHist(frame_gray, frame_gray);
		facecad.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
		for (int i = 0; i < faces.size(); i++) //consider the first face
		{
			cv::Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			maxareai = (faces[i].area() > maxarea) ? i : maxareai;
			maxarea = (faces[i].area() > maxarea) ? faces[i].area() : maxarea;
			ellipse(myframe, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
		}
		if (faces.size() != 0) p = faces[maxareai];
		return p;
	}
	private: void SkinColorModel(Mat frame, Rect faceregion, int* ymax, int* ymin, int* crmax, int* crmin, int* cbmax, int* cbmin)
	{
		int y, cb, cr, r, b, g, gray;
		Mat p;
		cv::cvtColor(frame, p, CV_BGR2YCrCb);
		*crmax = -1;
		*crmin = 295;
		*cbmax = -1;
		*cbmin = 295;
		*ymax = 295;
		*ymin = -1;
		if (faceregion.area() > 5)
		{

			for (int i = faceregion.x; i < faceregion.x + faceregion.width&& i < frame.cols; i++)
			{
				for (int j = faceregion.y; j < faceregion.y + faceregion.height&& j < frame.rows; j++)
				{

					b = frame.at<cv::Vec3b>(j, i)[0];
					g = frame.at<cv::Vec3b>(j, i)[1];
					r = frame.at<cv::Vec3b>(j, i)[2];
					y = p.at<cv::Vec3b>(j, i)[0];
					cr = p.at<cv::Vec3b>(j, i)[1];
					cb = p.at<cv::Vec3b>(j, i)[2];
					gray = (int)(0.2989 * r + 0.5870 * g + 0.1140 * b);
					if (gray < 200 && gray>40 && r > g && r > b)
					{
						*ymax = (y > *ymax) ? y : *ymax;
						*ymin = (y < *ymin) ? y : *ymin;
						*crmax = (cr > *crmax) ? cr : *crmax;
						*crmin = (cr < *crmin) ? cr : *crmin;
						*cbmax = (cb > *cbmax) ? cb : *cbmax;
						*cbmin = (cb < *cbmin) ? cb : *cbmin;
					}
				}
			}
			/**ymin = *ymin - 10;
			*ymax = *ymax + 10;
			*crmin = *crmin - 10;
			*crmax = *crmax + 10;
			*cbmin = *cbmin - 10;
			*cbmax = *cbmax + 10;*/
		}
		else
		{
			*ymax = 255;//(*ymax>163) ? 163 : *ymax;
			*ymin = 0;// (*ymin < 54) ? 54 : *ymin;
			*crmax = 173;// (*crmax > 173) ? 173 : *crmax;
			*crmin = 133;// (*crmin < 133) ? 133 : *crmin;
			*cbmax = 127;// (*cbmax > 127) ? 127 : *cbmax;
			*cbmin = 77;// (*cbmin < 77) ? 77 : *cbmin;
		}
		/**crmax = (*crmax > 173) ? 173 : *crmax;
		*crmin = (*crmin < 133) ? 133 : *crmin;
		*cbmax = (*cbmax > 127) ? 127 : *cbmax;
		*cbmin = (*cbmin < 77) ? 77 : *cbmin;*/
	}
	private: void HandDetection(Mat frame, Rect faceregion, int ymax, int ymin, int crmax, int crmin, int cbmax, int cbmin)
	{
		int largest_area = 0;
		int largest_contour_index = 0;
		vector<vector<cv::Point> > contours;
		vector<Vec4i> hierarchy;
		//cv::Size sz = cvGetSize(&frame);
		Mat mask = Mat(frame.rows, frame.cols, CV_8U);
		Mat maskmat(mask);
		
		if (faceregion.area() > 5)
		{
			if (faceregion.y > faceregion.height / 4)
			{
				faceregion.y -= faceregion.height / 4;
				faceregion.height += faceregion.height / 4;
			}
			else
			{
				faceregion.height += faceregion.y;
				faceregion.y = 0;

			}
			//avoid noise for T-shirt
			faceregion.height += faceregion.height / 2;
		}

		int y, cr, cb;
		//Turn to YCrCb
		Mat p, b,pyr;
		Mat frameblur;
		blur(frame, frameblur, cv::Size(5, 5));
		cv::cvtColor(frameblur, p, CV_BGR2YCrCb);
		//Remove the face area & binary image
		for (int i = 0; i < frame.cols; i++)
			for (int j = 0; j < frame.rows; j++)
			{

				y = p.at<cv::Vec3b>(j, i)[0];
				cr = p.at<cv::Vec3b>(j, i)[1];
				cb = p.at<cv::Vec3b>(j, i)[2];
				if (y > ymin && y < ymax && cr<crmax && cr>crmin && cb<cbmax && cb>cbmin)
					maskmat.at<unsigned char>(j, i) = 255;
				else maskmat.at<unsigned char>(j, i) = 0;

				/*if (mybackground != NULL)
				{
					b = mybackground;
					if (abs((int)frame.at<cv::Vec3b>(j, i)[0] - (int)b.at<cv::Vec3b>(j, i)[0]) < 10 && abs((int)frame.at<cv::Vec3b>(j, i)[1] - (int)b.at<cv::Vec3b>(j, i)[1]) < 10 && abs((int)frame.at<cv::Vec3b>(j, i)[2] - (int)b.at<cv::Vec3b>(j, i)[2]) < 10)
						maskmat.at<unsigned char>(j, i) = 0;
				}*/

			}
		for (int i = 0; i < faces.size(); i++)
			for (int j = faces[i].x; j < faces[i].x + faces[i].width; j++)
				for (int k = faces[i].y; k < faces[i].y + faces[i].height; k++)
					maskmat.at<unsigned char>(k, j) = 0;
		
		Mat erode_element = getStructuringElement(MORPH_RECT, cv::Size(3, 3));
		Mat dilate_element = getStructuringElement(MORPH_RECT, cv::Size(6, 6));
		//erode(mask, mask, erode_element); //ERODE first then DILATE to eliminate the noises.
		erode(mask, mask, erode_element);
		dilate(mask, mask, dilate_element);
		
		imshow("mask", mask);
		findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		/// Find the convex hull object for each contour
		vector<vector<cv::Point>> hull(contours.size());
		vector<vector<int>> inthull(contours.size());
		vector<vector<Vec4i>> defects(contours.size());
		
		//find largest contour
		for (int i = 0; i < contours.size(); i++) // iterate through each contour. 
		{
			double a = contourArea(contours[i], false);  //  Find the area of contour
			if (a > largest_area)
			{
				largest_area = a;
				largest_contour_index = i;                //Store the index of largest contour
			}

		}

		//checkforcontourarea function if error occur
		if (contours.size() > 0)
		{  
			convexHull(Mat(contours[largest_contour_index]), hull[largest_contour_index],true);
			convexHull(Mat(contours[largest_contour_index]), inthull[largest_contour_index], true);
			if (inthull[largest_contour_index].size() > 3) // If number of hull > 3  we will go to find the convexity defect
				convexityDefects(contours[largest_contour_index], inthull[largest_contour_index], defects[largest_contour_index]);
			drawContours(frame, contours, largest_contour_index, CV_RGB(0, 255, 0), 2, 8, hierarchy); // Draw the largest contour using previously stored index.																					  //draw hull as well
			if (showmyhull)
				drawContours(frame, hull, largest_contour_index, CV_RGB(0, 0, 255), 2, 8, hierarchy);
			if (showcondefects)
				condefects(defects[largest_contour_index], contours[largest_contour_index], frame);
			boundingBox = cv::boundingRect(hull[largest_contour_index]);
			cv::rectangle(frame, boundingBox, cv::Scalar(255, 0, 0));
			center = cv::Point(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);
		}

	}
	private: float innerAngle(float px1, float py1, float px2, float py2, float cx1, float cy1)
	{

		float dist1 = std::sqrt((px1 - cx1)*(px1 - cx1) + (py1 - cy1)*(py1 - cy1));
		float dist2 = std::sqrt((px2 - cx1)*(px2 - cx1) + (py2 - cy1)*(py2 - cy1));

		float Ax, Ay;
		float Bx, By;
		float Cx, Cy;
		Cx = cx1;
		Cy = cy1;
		if (dist1 < dist2)
		{
			Bx = px1;
			By = py1;
			Ax = px2;
			Ay = py2;


		}
		else {
			Bx = px2;
			By = py2;
			Ax = px1;
			Ay = py1;
		}


		float Q1 = Cx - Ax;
		float Q2 = Cy - Ay;
		float P1 = Bx - Ax;
		float P2 = By - Ay;


		float A = std::acos((P1*Q1 + P2*Q2) / (std::sqrt(P1*P1 + P2*P2) * std::sqrt(Q1*Q1 + Q2*Q2)));

		A = A * 180 / CV_PI;

		return A;
	}
	private: int findBiggestContour(vector<vector<cv::Point> > contours) {
		int indexOfBiggestContour = -1;
		int sizeOfBiggestContour = 0;
		for (int i = 0; i < contours.size(); i++) {
			if (contours[i].size() > sizeOfBiggestContour) {
				sizeOfBiggestContour = contours[i].size();
				indexOfBiggestContour = i;
			}
		}
		return indexOfBiggestContour;
	}
	private: void updateAngleMax(){angleMax = trbAnglemax->Value;}
    private: void updateAngleMin() { angleMin = trbAnglemin->Value; }
	private: void updateImage() { ptbVideo->Image = Mat2Bitmap.Mat2Bimap(frame); ptbVideo->Refresh();}
	private: void condefects(vector<Vec4i> convexityDefectsSet, vector<cv::Point> mycontour, Mat &frame)
	{
		Point2f mycenter;
		float myradius;
		float dis;
		vector<cv::Point>fingertips, deptharr;

		trbAnglemax->Invoke(gcnew MethodInvoker(this, &MainForm::updateAngleMax));
		trbAnglemin->Invoke(gcnew MethodInvoker(this, &MainForm::updateAngleMin));
		//std::vector<cv::Point> validPoints;
		for (int cDefIt = 0; cDefIt < convexityDefectsSet.size(); cDefIt++) {

			int startIdx = convexityDefectsSet[cDefIt].val[0]; cv::Point ptStart(mycontour[startIdx]);

			int endIdx = convexityDefectsSet[cDefIt].val[1]; cv::Point ptEnd(mycontour[endIdx]);

			int farIdx = convexityDefectsSet[cDefIt].val[2]; cv::Point ptFar(mycontour[farIdx]);
			
			double angle = std::atan2(center.y - ptStart.y, center.x - ptStart.x) * 180 / CV_PI;
			double inAngle = innerAngle(ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, ptFar.x, ptFar.y);
			double length = std::sqrt(std::pow(ptStart.x - ptFar.x, 2) + std::pow(ptStart.y - ptFar.y, 2));
			double centerLength = std::sqrt(std::pow(ptStart.x - center.x, 2) + std::pow(ptStart.y - center.y*1.2, 2));
			double depth = static_cast<double>(convexityDefectsSet[cDefIt].val[3]) / 256;
			
			if (angle > -100 && angle < 200 && std::abs(inAngle) > angleMin && std::abs(inAngle) < angleMax && length > 0.15 * boundingBox.height)
			{
				fingertips.push_back(ptStart);
			}
			
			
			//if (depth > 0 && depth < 120 && std::abs(inAngle) > 20 && std::abs(inAngle) < 120 && angle > -160 && angle < 160 && centerLength > lengthMin/100*boundingBox.height)
			//{
			//	line(frame, cv::Point(center.x / 1.1, center.y*1.2), ptStart,Scalar(0,255,0),1,8);
			//	circle(frame, ptStart, 20, Scalar(0, 255, 0), 1,8);
			//	fingertips.push_back(ptStart);
			//}
			if(depth > 10 && depth < 120)
			{
				circle(frame, ptFar, 3, Scalar(100, 0, 255), 2, 8);
				deptharr.push_back(ptFar);
			}
			
		
		}
		cv::Point2f centerps;
		float radips;
		if (deptharr.size() > 3)
		{
			cv::minEnclosingCircle(deptharr, centerps, radips);
			//circle(frame, centerps, radips, Scalar(0, 255, 0), 1, 8);
		}
		
		for (size_t i = 0; i < fingertips.size(); i++)
		{
			if (deptharr.size() > 3)
			{
				line(frame, centerps, fingertips[i], Scalar(0, 255, 0), 1, 8);
			}
			cv::circle(frame, fingertips[i], 3, cv::Scalar(100,0, 255), 5);
		}

		if (fingertips.size() == 1)
		{
			putText(frame, "01", cv::Point(400, 50), 1, 2, CV_RGB(255, 0, 0), 2, 8);
		}
		else if (fingertips.size() == 2)
		{
			putText(frame, "02", cv::Point(400, 50), 1, 2, CV_RGB(255, 0, 0), 2, 8);
		}
		else if (fingertips.size() == 3)
		{
			putText(frame, "03", cv::Point(400, 50), 1, 2, CV_RGB(255, 0, 0), 2, 8);
		}
		else if (fingertips.size() == 4)
		{
			putText(frame, "04", cv::Point(400, 50), 1, 2, CV_RGB(255, 0, 0), 2, 8);
		}
		else if (fingertips.size() == 5)
		{
			putText(frame, "05", cv::Point(400, 50), 1, 2, CV_RGB(255, 0, 0), 2, 8);
		}
		//work will start from here
		//if (krokaam)
			//workOnDefects(frame, fingertips, deptharr);

	}// condefects ends here

	private: float distanceP2P(cv::Point a, cv::Point b) {
		float d = sqrt(fabs(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
		return d;
	}
	private: int anglebetween(cv::Point p1, cv::Point p2)
	{
		int ang;
		if (p2.x == p1.x)
			return 0;
		ang = int(atan((p1.y - p2.y) / (p2.x - p1.x)) * 180 / 3.14);
		if (ang < 0)
			return ang + 180;
		else
			return ang;

	}
	private: void drawangle(Mat &frame, cv::Point p1, cv::Point p2, int ang)
	{
		putText(frame, intToString(ang), cv::Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2), 1, 1, CV_RGB(255, 255, 255), 2, 8);
	}
	private: string intToString(int number) {
		std::stringstream ss;
		ss << number;
		return ss.str();
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		
	}
	private: Void MainProcess(DoWorkEventArgs^  e)
	{
		while (1)
		{
			videocap.read(frame);
			//imshow("srcs", frame);
			Rect recFace = facedetect(frame, face_cascade);	// Find the face
			rectangle(frame, recFace, Scalar(0, 255, 0), 1, 8, 0); // Draw rect on the face
			int ymax; int ymin; int crmax; int crmin; int cbmax; int cbmin;
			SkinColorModel(frame, recFace, &ymax, &ymin, &crmax, &crmin, &cbmax, &cbmin); // Filter & cleaning face area
			HandDetection(frame, recFace, ymax, ymin, crmax, crmin, cbmax, cbmin); // Dectect hand
			//imshow("result", frame);
			ptbVideo->Invoke(gcnew MethodInvoker(this, &MainForm::updateImage));
			/*ptbVideo->Image = Mat2Bitmap.Mat2Bimap(frame);
			ptbVideo->Refresh();*/
			waitKey(10);
			if (btnProcess->Text == "Start")
			{
				videocap.release();
				break;
			}

		}
	}
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		MainProcess(e);
}
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}

