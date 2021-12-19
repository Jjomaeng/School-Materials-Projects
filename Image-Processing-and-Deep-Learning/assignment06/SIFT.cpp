#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#define IM_TYPE	CV_8UC3

using namespace cv;

// Image Type
// "G" for GrayScale Image, "C" for Color Image
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

#define PI 3.14

#define RATIO_THR 0.4

using namespace std;

double euclidDistance(Mat& vec1, Mat& vec2);
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors);
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold);

int main() {

	Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//resize(input1, input1, Size(input1.cols / 2, input1.rows / 2));
	//resize(input2, input2, Size(input2.cols / 2, input2.rows / 2));

	cvtColor(input1, input1_gray, CV_RGB2GRAY);
	cvtColor(input2, input2_gray, CV_RGB2GRAY);

	FeatureDetector* detector = new SiftFeatureDetector(
		0,		// nFeatures
		4,		// nOctaveLayers
		0.04,	// contrastThreshold
		10,		// edgeThreshold
		1.6		// sigma
	);

	DescriptorExtractor* extractor = new SiftDescriptorExtractor();

	// Create a image for displaying mathing keypoints
	Size size = input2.size();
	Size sz = Size(size.width + input1_gray.size().width, max(size.height, input1_gray.size().height));
	Mat matchingImage = Mat::zeros(sz, CV_8UC3);

	input1.copyTo(matchingImage(Rect(size.width, 0, input1_gray.size().width, input1_gray.size().height)));
	input2.copyTo(matchingImage(Rect(0, 0, size.width, size.height)));
	
	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints1;
	Mat descriptors1;

	detector->detect(input1_gray, keypoints1);
	extractor->compute(input1_gray, keypoints1, descriptors1);
	printf("input1 : %d keypoints are found.\n", (int)keypoints1.size());

	vector<KeyPoint> keypoints2;
	Mat descriptors2;

	// Detect keypoints
	detector->detect(input2_gray, keypoints2);
	extractor->compute(input2_gray, keypoints2, descriptors2);

	printf("input2 : %zd keypoints are found.\n", keypoints2.size());

	for (int i = 0; i < keypoints1.size(); i++) {
		KeyPoint kp = keypoints1[i];
		kp.pt.x += size.width;
		circle(matchingImage, kp.pt, cvRound(kp.size*0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	for (int i = 0; i < keypoints2.size(); i++) {
		KeyPoint kp = keypoints2[i];
		circle(matchingImage, kp.pt, cvRound(kp.size*0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	// Find nearest neighbor pairs
	vector<Point2f> srcPoints;
	vector<Point2f> dstPoints;
	bool crossCheck = true;
	bool ratio_threshold = false;
	findPairs(keypoints2, descriptors2, keypoints1, descriptors1, srcPoints, dstPoints, crossCheck, ratio_threshold);
	printf("%zd keypoints are matched.\n", srcPoints.size());

	// Draw line between nearest neighbor pairs
	for (int i = 0; i < (int)srcPoints.size(); ++i) {
		Point2f pt1 = srcPoints[i];
		Point2f pt2 = dstPoints[i];
		Point2f from = pt1;
		Point2f to = Point(size.width + pt2.x, pt2.y);
		line(matchingImage, from, to, Scalar(0, 0, 255));
	}

	// Display mathing image
	namedWindow("Matching");
	imshow("Matching", matchingImage);

	waitKey(0);

	return 0;
}

/**
* Calculate euclid distance
*/
double euclidDistance(Mat& vec1, Mat& vec2) {
	double sum = 0.0;
	int dim = vec1.cols;
	for (int i = 0; i < dim; i++) {
		sum += (vec1.at<float>(0, i) - vec2.at<float>(0, i)) * (vec1.at<float>(0, i) - vec2.at<float>(0, i));
	}

	return sqrt(sum);
}

/**
* Find the index of nearest neighbor point from keypoints.
*/
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	int neighbor = -1;
	double minDist = 1e6;
	double dist;

	for (int i = 0; i < descriptors.rows; i++) {
		Mat v = descriptors.row(i);		// each row of descriptor
		
		dist = euclidDistance(v, vec);
		if (dist < minDist)
		{
			minDist = dist;
			neighbor = i;
		}
	}

	return neighbor;
}

/**
* Find pairs of points with the smallest distace between them
*/
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold) {
	for (int i = 0; i < descriptors1.rows; i++) {
		KeyPoint pt1 = keypoints1[i];
		Mat desc1 = descriptors1.row(i);
		KeyPoint pt2;

		int nn = nearestNeighbor(desc1, keypoints2, descriptors2);
		

		// Refine matching points using ratio_based thresholding
		if (ratio_threshold) {
			double nearest_dist = -1.0;
			double sencond_dist = -1.0;
			
			for (int i = 0; i < descriptors2.rows; i++)
			{
				Mat v = descriptors2.row(i);
				double dist = euclidDistance(v, desc1);
				if (nearest_dist == -1.0)
					nearest_dist = dist;
				else
				{
					if (dist < nearest_dist)
					{
						sencond_dist = nearest_dist;
						nearest_dist = euclidDistance(v, desc1);
					}
					else
					{
						if (sencond_dist == -1.0)
						{
							sencond_dist = dist;
						}
						else
						{
							if (dist < sencond_dist)
								sencond_dist = dist;
						}
					}
				}
				
			}
			Mat nearestNN = descriptors2.row(nearest_dist);
			Mat SecondNN = descriptors2.row(sencond_dist);
			if (euclidDistance(desc1, nearestNN) / euclidDistance(desc1, SecondNN) > 0.8)
			{
				pt2 = keypoints2[nearest_dist];
				srcPoints.push_back(pt1.pt);
				dstPoints.push_back(pt2.pt);
			}


		}

		// Refine matching points using cross-checking
		if (crossCheck)
		{
			int cross_nn;
			Mat desc3 = descriptors2.row(nn);
			cross_nn = nearestNeighbor(desc3, keypoints2, descriptors1);
			
			if (keypoints1[cross_nn].pt.x == pt1.pt.x && keypoints1[cross_nn].pt.y == pt1.pt.y)
			{
				pt2 = keypoints2[nn];
				srcPoints.push_back(pt1.pt);
				dstPoints.push_back(pt2.pt);
			}

				
		}

		//KeyPoint pt2 = keypoints2[nn];
		//srcPoints.push_back(pt1.pt);
		//dstPoints.push_back(pt2.pt);
	}
}