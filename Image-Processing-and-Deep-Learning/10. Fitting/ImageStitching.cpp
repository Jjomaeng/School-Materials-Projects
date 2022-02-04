#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
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
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool ratio_threshold);
void blend_stitching(const Mat I1, const Mat I2, Mat &I_f, int bound_l, int bound_u, float alpha);
Mat cal_affine(vector<Point2f> srcPoints, vector<Point2f> dstPoints, int number_of_points);
Mat int_cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points);
Mat affine_k(vector<Point2f> srcPoints, vector<Point2f> dstPoints, int number_of_points);
Mat ransac(vector<Point2f> srcPoints, vector<Point2f> dstPoints, int number_of_points);
int main() {

	Mat I1 = imread("Img01.jpg", CV_LOAD_IMAGE_COLOR);
	Mat I2 = imread("Img02.jpg", CV_LOAD_IMAGE_COLOR);


	if (!I1.data || !I2.data) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//resize(input1, input1, Size(input1.cols / 2, input1.rows / 2));
	//resize(input2, input2, Size(input2.cols / 2, input2.rows / 2));


	FeatureDetector* detector = new SiftFeatureDetector(
		0,		// nFeatures
		4,		// nOctaveLayers
		0.04,	// contrastThreshold
		10,		// edgeThreshold
		1.6		// sigma
	);

	DescriptorExtractor* extractor = new SiftDescriptorExtractor();

	// Create a image for displaying mathing keypoints
	Size size = I2.size();
	Size sz = Size(size.width + I1.size().width, max(size.height, I1.size().height));
	Mat matchingImage = Mat::zeros(sz, CV_8UC3);

	I1.copyTo(matchingImage(Rect(size.width, 0, I1.size().width, I1.size().height)));
	I2.copyTo(matchingImage(Rect(0, 0, size.width, size.height)));

	const float I1_row = I1.rows;
	const float I1_col = I1.cols;
	const float I2_row = I2.rows;
	const float I2_col = I2.cols;
	
	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints1;
	Mat descriptors1;

	detector->detect(I1, keypoints1);
	extractor->compute(I1, keypoints1, descriptors1);
	printf("input1 : %d keypoints are found.\n", (int)keypoints1.size());

	vector<KeyPoint> keypoints2;
	Mat descriptors2;

	// Detect keypoints
	detector->detect(I2, keypoints2);
	extractor->compute(I2, keypoints2, descriptors2);

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
	bool ratio_threshold = true;
	findPairs(keypoints2, descriptors2, keypoints1, descriptors1, srcPoints, dstPoints, ratio_threshold);
	printf("%zd keypoints are matched.\n", srcPoints.size());
	//case 1
	Mat A12 = cal_affine(srcPoints, dstPoints, srcPoints.size());
	Mat A21 = cal_affine(dstPoints, srcPoints, dstPoints.size());

	Point2f p1(A21.at<float>(0) * 0 + A21.at<float>(1) * 0 + A21.at<float>(2), A21.at<float>(3) * 0 + A21.at<float>(4) * 0 + A21.at<float>(5));
	Point2f p2(A21.at<float>(0) * 0 + A21.at<float>(1) * I2_row + A21.at<float>(2), A21.at<float>(3) * 0 + A21.at<float>(4) * I2_row + A21.at<float>(5));
	Point2f p3(A21.at<float>(0) * I2_col + A21.at<float>(1) * I2_row + A21.at<float>(2), A21.at<float>(3) * I2_col + A21.at<float>(4) * I2_row + A21.at<float>(5));
	Point2f p4(A21.at<float>(0) * I2_col + A21.at<float>(1) * 0 + A21.at<float>(2), A21.at<float>(3) * I2_col + A21.at<float>(4) * 0 + A21.at<float>(5));


	int bound_u = (int)round(min(0.0f, min(p1.y, p4.y)));
	int bound_b = (int)round(max(I1_row - 1, max(p2.y, p3.y)));
	int bound_l = (int)round(min(0.0f, min(p1.x, p2.x)));
	int bound_r = (int)round(max(I1_col - 1, max(p3.x, p4.x)));

	Mat I_f_case1(bound_b - bound_u + 1, bound_r - bound_l + 1, CV_32FC3, Scalar(0));

	for (int i = bound_u; i <= bound_b; i++) {
		for (int j = bound_l; j <= bound_r; j++) {
			float x = A12.at<float>(0) * j + A12.at<float>(1) * i + A12.at<float>(2) - bound_l;
			float y = A12.at<float>(3) * j + A12.at<float>(4) * i + A12.at<float>(5) - bound_u;

			float y1 = floor(y);
			float y2 = ceil(y);
			float x1 = floor(x);
			float x2 = ceil(x);

			float mu = y - y1;
			float lambda = x - x1;

			if (x1 >= 0 && x2 < I2_col && y1 >= 0 && y2 < I2_row)
				I_f_case1.at<Vec3f>(i - bound_u, j - bound_l) = lambda * (mu * I2.at<Vec3f>(y2, x2) + (1 - mu) * I2.at<Vec3f>(y1, x2)) +
				(1 - lambda) *(mu * I2.at<Vec3f>(y2, x1) + (1 - mu) * I2.at<Vec3f>(y1, x1));
		}
	}

	// image stitching with blend
	blend_stitching(I1, I2, I_f_case1, bound_l, bound_u, 0.5);

	//case 2
	Mat A12_rs = ransac(srcPoints, dstPoints, srcPoints.size());
	Mat A21_rs = ransac(dstPoints, srcPoints, dstPoints.size());

	Point2f p1(A21_rs.at<float>(0) * 0 + A21_rs.at<float>(1) * 0 + A21_rs.at<float>(2), A21_rs.at<float>(3) * 0 + A21_rs.at<float>(4) * 0 + A21_rs.at<float>(5));
	Point2f p2(A21_rs.at<float>(0) * 0 + A21_rs.at<float>(1) * I2_row + A21_rs.at<float>(2), A21_rs.at<float>(3) * 0 + A21_rs.at<float>(4) * I2_row + A21_rs.at<float>(5));
	Point2f p3(A21_rs.at<float>(0) * I2_col + A21_rs.at<float>(1) * I2_row + A21_rs.at<float>(2), A21_rs.at<float>(3) * I2_col + A21_rs.at<float>(4) * I2_row + A21_rs.at<float>(5));
	Point2f p4(A21_rs.at<float>(0) * I2_col + A21_rs.at<float>(1) * 0 + A21_rs.at<float>(2), A21_rs.at<float>(3) * I2_col + A21_rs.at<float>(4) * 0 + A21_rs.at<float>(5));

	int bound_u = (int)round(min(0.0f, min(p1.y, p4.y)));
	int bound_b = (int)round(max(I1_row - 1, max(p2.y, p3.y)));
	int bound_l = (int)round(min(0.0f, min(p1.x, p2.x)));
	int bound_r = (int)round(max(I1_col - 1, max(p3.x, p4.x)));
	
	Mat I_f_case2(bound_b - bound_u + 1, bound_r - bound_l + 1, CV_32FC3, Scalar(0));

	for (int i = bound_u; i <= bound_b; i++) {
		for (int j = bound_l; j <= bound_r; j++) {
			float x = A12.at<float>(0) * j + A12.at<float>(1) * i + A12.at<float>(2) - bound_l;
			float y = A12.at<float>(3) * j + A12.at<float>(4) * i + A12.at<float>(5) - bound_u;

			float y1 = floor(y);
			float y2 = ceil(y);
			float x1 = floor(x);
			float x2 = ceil(x);

			float mu = y - y1;
			float lambda = x - x1;

			if (x1 >= 0 && x2 < I2_col && y1 >= 0 && y2 < I2_row)
				I_f_case2.at<Vec3f>(i - bound_u, j - bound_l) = lambda * (mu * I2.at<Vec3f>(y2, x2) + (1 - mu) * I2.at<Vec3f>(y1, x2)) +
				(1 - lambda) *(mu * I2.at<Vec3f>(y2, x1) + (1 - mu) * I2.at<Vec3f>(y1, x1));
		}
	}
	blend_stitching(I1, I2, I_f_case2, bound_l, bound_u, 0.5);

	// Display mathing image
	namedWindow("result_case1");
	imshow("result_case1", I_f_case1);

	namedWindow("result_case2");
	imshow("result_case2", I_f_case2);


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
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool ratio_threshold) {
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
			if (euclidDistance(desc1, nearestNN) / euclidDistance(desc1, SecondNN) < 1)
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


		}

	}
}

void blend_stitching(const Mat I1, const Mat I2, Mat &I_f, int bound_l, int bound_u, float alpha) {

	int col = I_f.cols;
	int row = I_f.rows;

	// I2 is already in I_f by inverse warping
	for (int i = 0; i < I1.rows; i++) {
		for (int j = 0; j < I1.cols; j++) {
			bool cond_I2 = I_f.at<Vec3f>(i - bound_u, j - bound_l) != Vec3f(0, 0, 0) ? true : false;

			if (cond_I2)
				I_f.at<Vec3f>(i - bound_u, j - bound_l) = alpha * I1.at<Vec3f>(i, j) + (1 - alpha) * I_f.at<Vec3f>(i - bound_u, j - bound_l);
			else
				I_f.at<Vec3f>(i - bound_u, j - bound_l) = I1.at<Vec3f>(i, j);

		}
	}
}


Mat cal_affine(vector<Point2f> srcPoints, vector<Point2f> dstPoints, int number_of_points) {

	Mat M(2 * number_of_points, 6, CV_32F, Scalar(0));
	Mat b(2 * number_of_points, 1, CV_32F);

	Mat M_trans, temp, affineM;

	// initialize matrix
	for (int i = 0; i < number_of_points; i++) {
		M.at<C>(2 * i, 0) = srcPoints[i].x;		M.at<C>(2 * i, 1) = srcPoints[i].y;		M.at<C>(2 * i, 2) = 1;
		M.at<C>(2 * i + 1, 3) = srcPoints[i].x;		M.at<C>(2 * i + 1, 4) = srcPoints[i].y;		M.at<C>(2 * i + 1, 5) = 1;
		b.at<C>(2 * i) = dstPoints[i].x;		b.at<C>(2 * i + 1) = dstPoints[i].y;
	}

	// (M^T * M)^(??) * M^T * b ( * : Matrix multiplication)
	transpose(M, M_trans);
	invert(M_trans * M, temp);
	affineM = temp * M_trans * b;

	return affineM;
}

template <typename T>
Mat int_cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points) {

	Mat M(2 * number_of_points, 6, CV_32F, Scalar(0));
	Mat b(2 * number_of_points, 1, CV_32F);

	Mat M_trans, temp, affineM;

	// initialize matrix
	for (int i = 0; i < number_of_points; i++) {
		M.at<T>(2 * i, 0) = ptl_x[i];		M.at<T>(2 * i, 1) = ptl_y[i];		M.at<T>(2 * i, 2) = 1;
		M.at<T>(2 * i + 1, 3) = ptl_x[i];		M.at<T>(2 * i + 1, 4) = ptl_y[i];		M.at<T>(2 * i + 1, 5) = 1;
		b.at<T>(2 * i) = ptr_x[i];		b.at<T>(2 * i + 1) = ptr_y[i];
	}

	// (M^T * M)^(??) * M^T * b ( * : Matrix multiplication)
	transpose(M, M_trans);
	invert(M_trans * M, temp);
	affineM = temp * M_trans * b;

	return affineM;
}

Mat affine_k(vector<Point2f> srcPoints, vector<Point2f> dstPoints, int number_of_points)
{
	srand(time(NULL));
	int src_x[3], src_y[3], dst_x[3], dst_y[3];
	int rand_idx;
	for (int i = 0; i < 3; i++)
	{
		rand_idx = rand() % number_of_points;
		src_x[i]=srcPoints[rand_idx].x;
		src_y[i] = srcPoints[rand_idx].y;
		dst_x[i] = dstPoints[rand_idx].x;
		dst_y[i] = dstPoints[rand_idx].y;
		
	}
	return int_cal_affine(src_x, src_y, dst_x, dst_y, 3);
}

Mat ransac(vector<Point2f> srcPoints, vector<Point2f> dstPoints, int number_of_points)
{
	int count=0, max_count=0;
	Mat affineM,final_M;
	for (int k = 0; k < 5; k++)
	{
		count = 0;
		for (int i = 0; i < number_of_points; i++)
		{
			affineM = affine_k(srcPoints, dstPoints, number_of_points);
			float x = affineM.at<float>(0) * srcPoints[i].x + affineM.at<float>(1) * srcPoints[i].y + affineM.at<float>(2);
			float y = affineM.at<float>(3) * srcPoints[i].x + affineM.at<float>(4) * srcPoints[i].y + affineM.at<float>(5);
			if (sqrt(pow(x - dstPoints[i].x, 2) + pow(y - dstPoints[i].y, 2)) < 10)
				count++;
		}
		if (max_count < count)
		{
			max_count = count;
			final_M = affineM;
		}
	}
	return final_M;
}