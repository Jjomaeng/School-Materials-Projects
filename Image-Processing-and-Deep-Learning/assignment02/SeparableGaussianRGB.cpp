#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>   
#include <time.h>/* exp */
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

Mat Separable_gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS);

int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output;

	clock_t start, end;
	double result;


	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("RGB color", WINDOW_AUTOSIZE);
	imshow("RGB color", input);
	start = clock(); //start
	output = Separable_gaussianfilter(input, 3, 3, 3); //Boundary process: zero-paddle, mirroring, adjustkernel
	end = clock(); //end
	result = (double)(end - start);
	namedWindow("Gaussian Filter_separable", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter_separable", output);


	printf("Separable 계산 시간 : %f ", result);

	waitKey(0);

	return 0;
}


Mat Separable_gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS) {

	Mat kernel_s, kernel_t;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	float denom_s, denom_t;


	// Initialiazing Kernel Matrix 
	kernel_s = Mat::zeros(kernel_size, 1, CV_32F);
	kernel_t = Mat::zeros(kernel_size, 1, CV_32F);



	denom_s = 0.0;
	denom_t = 0.0;
	for (int a = -n; a <= n; a++) {  // Denominator in m(s,t)

		float value1 = exp(-(pow(a, 2) / (2 * pow(sigmaS, 2))));
		kernel_s.at<float>(a + n) = value1;
		denom_s += value1;
		float value2 = exp(-(pow(a, 2) / (2 * pow(sigmaT, 2))));
		kernel_t.at<float>(a + n) = value2;
		denom_t += value2;

	}

	for (int a = -n; a <= n; a++) {  // Denominator in m(s,t)
		kernel_s.at<float>(a + n) /= denom_s;
		kernel_t.at<float>(a + n) /= denom_t;
	}

	Mat output = Mat::zeros(row, col, input.type());



	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float sum1_r = 0.0;
			float sum1_g = 0.0;
			float sum1_b = 0.0;

			for (int a = -n; a <= n; a++) {
				if ((i + a <= row - 1) && (i + a >= 0) && (j + a <= col - 1) && (j + a >= 0))
				{
					sum1_r += kernel_t.at<float>(a + n) * (float)(input.at<C>(i, j + a)[0]);
					sum1_g += kernel_t.at<float>(a + n) * (float)(input.at<C>(i, j + a)[1]);
					sum1_b += kernel_t.at<float>(a + n) * (float)(input.at<C>(i, j + a)[2]);
				}
			}
			output.at<C>(i, j)[0] = (G)sum1_r;
			output.at<C>(i, j)[1] = (G)sum1_g;
			output.at<C>(i, j)[2] = (G)sum1_b;
		}

	}


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float sum1_r = 0.0;
			float sum1_g = 0.0;
			float sum1_b = 0.0;
			for (int a = -n; a <= n; a++) {
				if ((i + a <= row - 1) && (i + a >= 0) && (j + a <= col - 1) && (j + a >= 0))
				{
					sum1_r += kernel_s.at<float>(a + n) * (float)(output.at<C>(i + a, j)[0]);
					sum1_g += kernel_s.at<float>(a + n) * (float)(output.at<C>(i + a, j)[1]);
					sum1_b += kernel_s.at<float>(a + n) * (float)(output.at<C>(i + a, j)[2]);
				}

			}
			output.at<C>(i, j)[0] = (G)sum1_r;
			output.at<C>(i, j)[1] = (G)sum1_g;
			output.at<C>(i, j)[2] = (G)sum1_b;
		}

	}

	return output;

}