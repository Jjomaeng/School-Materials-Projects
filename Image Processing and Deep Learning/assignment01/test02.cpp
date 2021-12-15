//#include "hist_func.h"
//
//void hist_eq_Color(Mat &input, Mat &equalized, G(*trans_func)[3], float **CDF);
//
//int main() {
//
//	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
//	Mat equalized_RGB = input.clone();
//	Mat result = input.clone();
//	Mat Reference = imread("Equlize_YUV.jpg", CV_LOAD_IMAGE_COLOR);
//
//
//
//	//PDF or transfer function txt files
//	FILE *f_equalized_PDF_RGB, *f_PDF_RGB;
//	FILE *f_trans_func_eq_RGB;
//
//
//	float **PDF_RGB = cal_PDF_RGB(input);	// PDF of Input image(RGB) : [L][3]
//	float **CDF_RGB = cal_CDF_RGB(input);	// CDF of Input image(RGB) : [L][3]
//
//	G trans_func_eq_RGB[L][3] = { 0 };// transfer function
//
//	G t_func_eq_RGB[3][L];
//
//	G inverse_func[3][L];
//
//	G total_inverse[L][3];
//
//	G temp[3][3];
//
//	G inverse[3][3];
//
//	G sum = 0;
//
//	float determinant = 0;
//
//
//
//	// histogram equalization on RGB image
//	
//	hist_eq_Color(input, equalized_RGB, trans_func_eq_RGB, CDF_RGB);
//
//	////// equalized PDF (RGB)
//	float *equalized_PDF_RGB = *cal_PDF_RGB(equalized_RGB);
//
//
//	// memory release
//	free(PDF_RGB);
//	free(CDF_RGB);
//
//	for (int i = 0; i < L; i++)
//		for (int j = 0; j < 3; j++)
//			t_func_eq_RGB[j][i] = trans_func_eq_RGB[i][j];
//
//	for (int k = 0; k < 3; k++)
//	{
//		
//		for (int i = 0; i < 3; i++)
//		{
//			sum = 0;
//			for (int j = 0; j < L; j++)
//				sum += t_func_eq_RGB[k][j] * trans_func_eq_RGB[j][i];
//			temp[k][i] = sum;
//		}
//	}
//	
//	for (int i = 0; i < 3; i++)
//		determinant = determinant + (temp[0][i] * (temp[1][(i + 1) % 3] * temp[2][(i + 2) % 3] - temp[1][(i + 2) % 3] * temp[2][(i + 1) % 3]));
//
//	
//
//
//
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++)
//			inverse[i][j] = ((temp[(i + 1) % 3][(j + 1) % 3] * temp[(i + 2) % 3][(j + 2) % 3]) - (temp[(i + 1) % 3][(j + 2) % 3] * temp[(i + 2) % 3][(j + 1) % 3])) / determinant;
//	}
//
//	sum = 0;
//			
//	for (int k = 0; k < 3; k++)
//	{
//		
//		for (int i = 0; i < 3; i++)
//		{
//			sum = 0;
//			for (int j = 0; j < L; j++)
//				sum += inverse[k][i] * t_func_eq_RGB[i][j];
//			inverse_func[k][i] = sum;
//		}
//	}
//
//	for (int i = 0; i < L; i++)
//		for (int j = 0; j < 3; j++)
//			t_func_eq_RGB[j][i] = trans_func_eq_RGB[i][j];
//
//	for (int i = 0; i < L; i++)
//		for (int j = 0; j < 3; j++)
//			total_inverse[i][j] = inverse_func[j][i];
//	
//	for (int i = 0; i < input.rows; i++)
//		for (int j = 0; j < input.cols; j++)
//			for (int k = 0; k < 3; k++) {
//				result.at<C>(i, j)[k] = total_inverse[equalized_YUV.at<C>(i, j)[k]][k]-128;
//			}
//
//	imshow("result", result);
//	waitKey();
//
//
//
//
//
//
//	return 0;
//}
//
// //histogram equalization on 3 channel image
