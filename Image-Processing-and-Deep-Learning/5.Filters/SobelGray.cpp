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

Mat sobelfilter(const Mat input);

int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	Mat output;


	cvtColor(input, input_gray, CV_RGB2GRAY);



	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	output = sobelfilter(input_gray);
	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("output", output);



	waitKey(0);

	return 0;
}


Mat sobelfilter(const Mat input) {


	int row = input.rows;
	int col = input.cols;
	int tempa;
	int tempb;
	float temp;
	int n = 1; // Sobel Filter Kernel N
	int kernel_size = (2 * n + 1);

	float x_kernel[3][3] = { { -1, 0, 1},{-2, 0, 2},{-1, 0, 1} };
	float y_kernel[3][3] = { { -1, -2, -1},{0, 0, 0},{1, 2, 1 } };



	// Initialiazing 2 Kernel Matrix with 3x3 size for Sx and Sy
	//Fill code to initialize Sobel filter kernel matrix for Sx and Sy (Given in the lecture notes)

	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			float sum1 = 0.0;
			float sum2 = 0.0;

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
					sum1 += x_kernel[a + 1][b + 1] * (float)(input.at<G>(tempa, tempb));
					sum2 += y_kernel[a + 1][b + 1] * (float)(input.at<G>(tempa, tempb));
					

				}
			}

			temp = sqrt((sum1 * sum1) + (sum2 * sum2));

			if (temp < 0) temp = 0;
			if (temp > 255) temp = 255;
			output.at<G>(i, j) = temp;




		}
	}


	return output;

}