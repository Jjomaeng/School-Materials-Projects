#include <iostream>
#include <opencv2/opencv.hpp>
#define IM_TYPE	CV_8UC3

using namespace cv;

#if (IM_TYPE == CV_8UC3)
typedef uchar G;
typedef cv::Vec3b C;
#elif (IM_TYPE == CV_16SC3)
typedef short G;
typedef Vec3s C;
#elif (IM_TYPE == CV_32SC3)
typedef int G;
typedef Vec3i C;
#elif (IM_TYPE == CV_32FC3)
typedef float G;
typedef Vec3f C;
#elif (IM_TYPE == CV_64FC3)
typedef double G;
typedef Vec3d C;
#endif

using namespace cv;
using namespace std;

int main() {

	Mat input = imread("lena.jpg");
	Mat input_gray;
	cvtColor(input, input_gray, CV_RGB2GRAY);


	Mat p = Mat::zeros(input.cols*input.rows, 3, CV_32F);
	Mat labels, centers, clustered;
	vector<Mat> bgr;
	cv::split(input, bgr);
	for (int i = 0; i < input.cols*input.rows; i++) {
		p.at<float>(i, 0) = (i / input.cols) / input.rows;
		p.at<float>(i, 1) = (i%input.cols) / input.cols;
		p.at<float>(i, 2) = input_gray.at<G>(i / input.cols, i%input.cols) / 255.0;
		
	}

	int clusterCount = 10;
	int attempts = 5;
	cv::kmeans(p, clusterCount, labels,TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10000, 0.0001),attempts, KMEANS_PP_CENTERS, centers);
	

	int* colors = new int[clusterCount];
	for (int i = 0; i < clusterCount; i++) {
		colors[i] = 255 / (i + 1);
	}
	clustered = Mat(input.rows, input.cols, CV_32F);
	for (int i = 0; i < input.cols*input.rows; i++) {
		clustered.at<float>(i / input.cols, i%input.cols) = (float)(colors[labels.at<int>(i)]);

	}



	
	imshow("clustered", clustered);

	waitKey(0);
	return 0;
}