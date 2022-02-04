#include "hist_func.h"

void hist_eq(Mat &input, Mat &equalized, G *trans_func, float *CDF);

int main() {

	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat equalized_YUV;
	Mat reference_YUV;
	Mat hist_match;
	Mat Reference = imread("Equlize_YUV.jpg", CV_LOAD_IMAGE_COLOR);

	cvtColor(input, equalized_YUV, CV_RGB2YUV);	// RGB -> YUV
	cvtColor(Reference, reference_YUV, CV_RGB2YUV);

	// split each channel(Y, U, V)
	Mat channels[3];
	Mat r_channels[3];
	split(equalized_YUV, channels);
	split(reference_YUV, r_channels);
	Mat Y = channels[0];	// U = channels[1], V = channels[2]
	Mat R_Y = r_channels[0];	//PDF or transfer function txt files



	float *CDF_YUV = cal_CDF(Y);	// CDF of Y channel image
	float *R_CDF_YUV = cal_CDF(R_Y);



	G R_trans_func_eq_YUV[L] = { 0 };
	G trans_func_eq_YUV[L] = { 0 };	// transfer function

	// histogram equalization on Y channel
	hist_eq(R_Y, r_channels[0], R_trans_func_eq_YUV, R_CDF_YUV);
	hist_eq(Y, channels[0], trans_func_eq_YUV, CDF_YUV);





	G t_func[1][L];


	G total_inverse[L];

	G temp1;



	G sum = 0;


	Mat result = r_channels[0].clone();

	int i = 0, j = 0;

	//calculate inverse matrix
	//create M*t
	for (int i = 0; i < L; i++)
		t_func[0][i] = R_trans_func_eq_YUV[i];
	////mul (M*t x M)
	for (int i = 0; i < L; i++)
		sum += (t_func[0][i] * R_trans_func_eq_YUV[i]);
	temp1 = sum;

	
	
	




	
	//cal (M*t x M)-1 x m*t
	for (int i = 0; i < L; i++)
		total_inverse[i] = temp1 * t_func[1][i];
	

	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			result.at<G>(i, j) = total_inverse[channels[0].at<G>(i, j)];

	channels[0] = result;

	merge(channels, 3, hist_match);

	cvtColor(hist_match, hist_match, CV_YUV2RGB);

	
	imshow("original", input);
	imshow("reference IMage", Reference);
	imshow("hist_match", hist_match);

	waitKey();


	return 0;
}

// histogram equalization
void hist_eq(Mat &input, Mat &equalized, G *trans_func, float *CDF) {

	// compute transfer function
	for (int i = 0; i < L; i++)
		trans_func[i] = (G)((L - 1) * CDF[i]);

	// perform the transfer function
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			equalized.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}

