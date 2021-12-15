#include "hist_func.h"

void hist_eq_Color(Mat &input, Mat &equalized, G(*trans_func)[3], float **CDF);

int main() {

	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR); //이미지를 컬러로 불러오기
	Mat equalized_RGB = input.clone(); //equalized_rgb에 input이미지를 복사한다.

	//PDF or transfer function txt files
	FILE *f_equalized_PDF_RGB, *f_PDF_RGB; 
	FILE *f_trans_func_eq_RGB;

	fopen_s(&f_PDF_RGB, "PDF_RGB.txt", "w+");
	fopen_s(&f_equalized_PDF_RGB, "equalized_PDF_RGB.txt", "w+");
	fopen_s(&f_trans_func_eq_RGB, "trans_func_eq_RGB.txt", "w+");

	float **PDF_RGB = cal_PDF_RGB(input);	// PDF of Input image(RGB) : [L][3]
	float **CDF_RGB = cal_CDF_RGB(input);	// CDF of Input image(RGB) : [L][3]

	G trans_func_eq_RGB[L][3] = { 0 };		// transfer function

	// histogram equalization on RGB image
	
	hist_eq_Color(input, equalized_RGB, trans_func_eq_RGB, CDF_RGB);

	// equalized PDF (RGB)
	float *equalized_PDF_RGB = *cal_PDF_RGB(equalized_RGB);

	for (int i = 0; i < L; i++) {
		
		
		for (int j = 0; j < 3; j++) {
			// write PDF
			fprintf(f_PDF_RGB, "%d\t%f \n", i, PDF_RGB[i][j]); 
			fprintf(f_equalized_PDF_RGB, "%d\t%f\n", i, equalized_PDF_RGB[i,j]);
			// write transfer functions
			fprintf(f_trans_func_eq_RGB, "%d\t%d\n", i, trans_func_eq_RGB[i][j]);
		}
	}

	// memory release
	free(PDF_RGB);
	free(CDF_RGB);
	fclose(f_PDF_RGB);
	fclose(f_equalized_PDF_RGB);
	fclose(f_trans_func_eq_RGB);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Equalized_RGB", WINDOW_AUTOSIZE);
	imshow("Equalized_RGB", equalized_RGB);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}

// histogram equalization on 3 channel image
void hist_eq_Color(Mat &input, Mat &equalized, G(*trans_func)[3], float **CDF) {
	// compute transfer function
	for (int i = 0; i < L; i++) {// 3 컬러 채널에 대한 for문을 추가한다,
		for (int j = 0; j < 3; j++) {
			trans_func[i][j] = (G)((L - 1) * CDF[i][j]);
		}
	}


	// perform the transfer function
	for (int i = 0; i < input.rows; i++) // 3 컬러 채널에 대한 for문을 추가한다,
		for (int j = 0; j < input.cols; j++)
			for (int k = 0; k < 3; k++) {
				equalized.at<C>(i, j)[k] = trans_func[input.at<C>(i, j)[k]][k];
			}
			


}