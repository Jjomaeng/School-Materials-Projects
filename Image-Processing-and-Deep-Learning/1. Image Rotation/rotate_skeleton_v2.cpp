#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt);

int main()
{
	Mat input, rotated;

	// Read each image
	input = imread("lena.jpg");

	// Check for invalid input
	if (!input.data) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// original image
	namedWindow("image"); //create window
	imshow("image", input);  //show image
	 
	rotated = myrotate<Vec3b>(input, 10, "bilinear"); //rotate

	// rotated image
	namedWindow("rotated"); //create window
	imshow("rotated", rotated); //show image

	waitKey(0); 

	return 0;
}

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt) {
	int row = input.rows; //for input size(row)
	int col = input.cols; //for input size(col)

	float radian = angle * CV_PI / 180; // angle -> radian

	float sq_row = ceil(row * sin(radian) + col * cos(radian)); //rotate function
	float sq_col = ceil(col * sin(radian) + row * cos(radian)); //rotate function

	Mat output = Mat::zeros(sq_row, sq_col, input.type()); // make ouput image(fill out 0)

	


	for (int i = 0; i < sq_row; i++) {//iterative 0 to rotated row size 
		for (int j = 0; j < sq_col; j++) { // iterative 0 to rotated col size 
			float x = (j - sq_col / 2) * cos(radian) - (i - sq_row / 2) * sin(radian) + col / 2; //apply inverse rotaiton to x'
			float y = (j - sq_col / 2) * sin(radian) + (i - sq_row / 2) * cos(radian) + row / 2; ////apply inverse rotaiton to y'

			float myu = y - floor(y); // this is how i set the myu
			float lambda = x - floor(x); // this is how i set the lambda

			if ((y >= 0) && (y <= (row - 1)) && (x >= 0) && (x <= (col - 1))) { // Conditions for not exceeding x and y
				if (!strcmp(opt, "nearest")) { //if option is nearest

					output.at<Vec3b>(i, j) = input.at<Vec3b>(y, x); //The input value is put into the rotated output value
				}
				else if (!strcmp(opt, "bilinear")) { //if option is bilinear
					output.at<Vec3b>(i, j) = (input.at<Vec3b>(y, x) * (1 - myu)*(1 - lambda) //I will explain the equation in the report
						+ input.at<Vec3b>(y + 1, x) * myu*(1 - lambda)
						+ input.at<Vec3b>(y, x + 1) * (1 - myu)*lambda
						+ input.at<Vec3b>(y + 1, x + 1) * myu*lambda);

				}
			}
		}
	}

	return output;
}