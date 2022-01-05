#include <iostream>
#include <opencv2/opencv.hpp>

#define IM_TYPE	CV_8UC3

using namespace cv;


// Note that this code is for the case when an input data is a color value.
int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output;


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//namedWindow("Original", WINDOW_AUTOSIZE);
	//imshow("Original", input);


	Mat samples(input.rows * input.cols, 3, CV_32F);
	Mat samples_gray(input.rows * input.cols,1, CV_32F);
	vector<Mat> bgr;
	cv::split(input, bgr);
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			for (int z = 0; z < 3; z++)
				samples.at<float>(y + x * input.rows, z) = input.at<Vec3b>(y, x)[z];
		}

	// Clustering is performed for each channel (RGB)
	// Note that the intensity value is not normalized here (0~1). You should normalize both intensity and position when using them simultaneously.
	int clusterCount = 10;
	Mat labels;
	int attempts = 5;
	Mat centers;
	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);
	//Mat new_image(input.size(), input.type());

	//code that finds for each pixel of each channel of the output image the intensity of the cluster center.
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x*input.rows, 0);
			new_image.at<Vec3b>(y, x)[0] = centers.at<float>(cluster_idx,0);

			new_image.at<Vec3b>(y, x)[1] = centers.at<float>(cluster_idx,1);

			new_image.at<Vec3b>(y, x)[2] = centers.at<float>(cluster_idx,2);			
		}

	namedWindow("clustered image", WINDOW_AUTOSIZE);
	imshow("clustered image", new_image);

	Mat clustered = Mat(input.rows, input.cols, CV_32F);
	int* colors = new int[clusterCount];
	for (int i = 0; i < clusterCount; i++) {
		colors[i] = 255 / (i + 1);
	}
	
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++) {
		clustered.at<float>(y, x) = (float)(colors[labels.at<int>(y + x * input.rows)]);

	}
	clustered.convertTo(clustered, CV_8U);
	imshow("clustered", clustered);
	waitKey(0);

	return 0;
}

