#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
	Mat src;

	src = imread("lena.jpg");
	imshow("original", src);

	Mat p = Mat::zeros(src.cols*src.rows, 5, CV_32F);
	Mat labels, centers, clustered;
	vector<Mat> bgr;
	cv::split(src, bgr);

	for (int i = 0; i < src.cols*src.rows; i++) {
		p.at<float>(i, 0) = (i / src.cols) / src.rows;
		p.at<float>(i, 1) = (i%src.cols) / src.cols;
		p.at<float>(i, 2) = bgr[0].data[i] / 255.0;
		p.at<float>(i, 3) = bgr[1].data[i] / 255.0;
		p.at<float>(i, 4) = bgr[2].data[i] / 255.0;
	}

	int clusterCount = 10;
	int attempts = 5;
	cv::kmeans(p, clusterCount, labels,
		TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10000, 0.0001),
		attempts, KMEANS_PP_CENTERS, centers);

	int* colors = new int[clusterCount];
	for (int i = 0; i < clusterCount; i++) {
		colors[i] = 255 / (i + 1);
	}

	clustered = Mat(src.rows, src.cols, CV_32F);
	for (int i = 0; i < src.cols*src.rows; i++) {
		clustered.at<float>(i / src.cols, i%src.cols) = (float)(colors[labels.at<int>(i)]);
	
	}

	clustered.convertTo(clustered, CV_8U);
	imshow("clustered", clustered);

	waitKey(0);
	return 0;
}