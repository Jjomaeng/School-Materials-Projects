//#include "hist_func.h"
//
//void hist_eq(Mat &input, Mat &equalized, G *trans_func, float *CDF);
//
//int main() {
//
//	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);//input이미지를 불러온다.
//	Mat input_gray;//이미지를 gray 이미지로 변경하기위한 mat변수 선언
//
//	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale
//
//	Mat equalized = input_gray.clone(); //input이미지를 복사한다.
//
//	// PDF or transfer function txt files
//	FILE *f_PDF;
//	FILE *f_equalized_PDF_gray;
//	FILE *f_trans_func_eq;
//	
//	fopen_s(&f_PDF, "PDF.txt", "w+"); //write하기 위한 PDF문서를 연다
//	fopen_s(&f_equalized_PDF_gray, "equalized_PDF_gray.txt", "w+");//write하기 위한 equalized_PDF_gray문서를 연다
//	fopen_s(&f_trans_func_eq, "trans_func_eq.txt", "w+");//write하기 위한 trans_func_eq문서를 연다
//
//	float *PDF = cal_PDF(input_gray);	// PDF of Input image(Grayscale) : [L]
//	float *CDF = cal_CDF(input_gray);	// CDF of Input image(Grayscale) : [L]
//
//	G trans_func_eq[L] = { 0 };			// transfer function
//
//	hist_eq(input_gray, equalized, trans_func_eq, CDF);								// histogram equalization on grayscale image
//	float *equalized_PDF_gray = cal_PDF(equalized);									// equalized PDF (grayscale)
//
//	for (int i = 0; i < L; i++) {
//		// write PDF
//		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
//		fprintf(f_equalized_PDF_gray, "%d\t%f\n", i, equalized_PDF_gray[i]);
//
//		// write transfer functions
//		fprintf(f_trans_func_eq, "%d\t%d\n", i, trans_func_eq[i]);
//	}
//
//	// memory release
//	free(PDF);
//	free(CDF);
//	fclose(f_PDF);
//	fclose(f_equalized_PDF_gray);
//	fclose(f_trans_func_eq);
//
//	////////////////////// Show each image ///////////////////////
//
//	namedWindow("Grayscale", WINDOW_AUTOSIZE);
//	imshow("Grayscale", input_gray);
//
//	namedWindow("Equalized", WINDOW_AUTOSIZE);
//	imshow("Equalized", equalized);
//
//	//////////////////////////////////////////////////////////////
//
//	waitKey(0);
//
//	return 0;
//}
//
//// histogram equalization
//void hist_eq(Mat &input, Mat &equalized, G *trans_func, float *CDF) {
//
//	// compute transfer function
//	for (int i = 0; i < L; i++)
//		trans_func[i] = (G)((L - 1) * CDF[i]); 
//
//	// perform the transfer function
//	for (int i = 0; i < input.rows; i++)
//		for (int j = 0; j < input.cols; j++)
//			equalized.at<G>(i, j) = trans_func[input.at<G>(i, j)];
//}