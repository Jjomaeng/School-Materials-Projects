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


// Note that this code is for the case when an input data is a color value.
int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	cvtColor(input, input_gray, CV_RGB2GRAY);

	Mat output;


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//namedWindow("Original", WINDOW_AUTOSIZE);
	//imshow("Original", input);


	Mat samples(input.rows * input.cols, 1, CV_32F);
	vector<Mat> bgr;
	cv::split(input, bgr);
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			samples.at<float>(y + x * input.rows) = input_gray.at<G>(y, x);
		}

	int clusterCount = 10;
	Mat labels;
	int attempts = 5;
	Mat centers;
	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);



	int* colors = new int[clusterCount];
	for (int i = 0; i < clusterCount; i++) {
		colors[i] = 255 / (i + 1);
	}
	Mat clustered = Mat(input_gray.rows, input_gray.cols, CV_32F);
	for (int i = 0; i < input_gray.cols*input_gray.rows; i++) {
		clustered.at<float>(i%input_gray.cols, i / input_gray.cols) = (float)(colors[labels.at<int>(i)]);

	}
	
	
	clustered.convertTo(clustered, CV_8U);
	imshow("clustered", clustered);
	waitKey(0);

	return 0;
}

