//#include "hist_func.h"
//
//int main() {
//
//	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
//	Mat input_gray; //회색 이미지를 담기위한 변수 선언
//
//	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale
//
//	// PDF, CDF txt files
//	FILE *f_PDF, *f_CDF;
//
//	//pdf,cdf를 적기위한 파일 변수 선언
//	fopen_s(&f_PDF, "PDF3.txt", "w+");
//	fopen_s(&f_CDF, "CDF3.txt", "w+");
//
//	// each histogram
//	float *PDF = cal_PDF(input_gray);		// PDF of Input image(Grayscale) : [L]
//	float *CDF = cal_CDF(input_gray);		// CDF of Input image(Grayscale) : [L]
//
//	for (int i = 0; i < L; i++) {
//		// write PDF, CDF
//		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]); //pdf 적기
//		fprintf(f_CDF, "%d\t%f\n", i, CDF[i]); //cdf 적기
//	}
//
//	// memory release
//	free(PDF);
//	free(CDF);
//	fclose(f_PDF);
//	fclose(f_CDF);
//
//	////////////////////// Show each image ///////////////////////
//
//	namedWindow("RGB", WINDOW_AUTOSIZE);
//	imshow("RGB", input);
//
//	namedWindow("Grayscale", WINDOW_AUTOSIZE);
//	imshow("Grayscale", input_gray);
//
//	//////////////////////////////////////////////////////////////
//
//	waitKey(0);
//
//	return 0;
//}