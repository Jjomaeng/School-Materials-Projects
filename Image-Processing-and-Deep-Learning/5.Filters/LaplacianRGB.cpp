#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>       /* exp */
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

Mat laplacianfilter(const Mat input);

int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output;

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("RGBscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input);

	output = laplacianfilter(input);
	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("output", output);



	waitKey(0);

	return 0;
}


Mat laplacianfilter(const Mat input) {


	int row = input.rows;
	int col = input.cols;
	int tempa;
	int tempb;
	int n = 1; // Sobel Filter Kernel N
	int kernel_size = (2 * n + 1);

	float kernel[3][3] = { { 0, 1, 0},{1, -4, 1},{0, 1, 0} };




	// Initialiazing 2 Kernel Matrix with 3x3 size for Sx and Sy
	//Fill code to initialize Sobel filter kernel matrix for Sx and Sy (Given in the lecture notes)

	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			float sum1_r = 0.0;
			float sum1_g = 0.0;
			float sum1_b = 0.0;

			for (int a = -n; a <= n; a++)
			{
				for (int b = -n; b <= n; b++)
				{
					if (i + a > row - 1) {  //mirroring for the border pixels
						tempa = i - a;
					}
					else if (i + a < 0) {
						tempa = -(i + a);
					}
					else {
						tempa = i + a;
					}
					if (j + b > col - 1) {
						tempb = j - b;
					}
					else if (j + b < 0) {
						tempb = -(j + b);
					}
					else {
						tempb = j + b;
					}
					sum1_r += kernel[a + 1][b + 1] * (float)(input.at<C>(tempa, tempb)[0]);
					sum1_g += kernel[a + 1][b + 1] * (float)(input.at<C>(tempa, tempb)[1]);
					sum1_b += kernel[a + 1][b + 1] * (float)(input.at<C>(tempa, tempb)[1]);




				}
			}
			if (sum1_r < 0) sum1_r = 0;
			if (sum1_r > 255) sum1_r = 255;
			output.at<C>(i, j)[0] = (G)sum1_r *4;
			if (sum1_g < 0) sum1_g = 0;
			if (sum1_g > 255) sum1_g = 255;
			output.at<C>(i, j)[1] = (G)sum1_g * 4;
			if (sum1_b < 0) sum1_b = 0;
			if (sum1_b > 255) sum1_b = 255;
			output.at<C>(i, j)[2] = (G)sum1_b * 4;




		}
	}


	return output;

}