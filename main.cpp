#include <iostream>
#include "model.h"
#include <opencv2/opencv.hpp>
#include <fstream>

int main() {

	cv::Mat test_signal = cv::imread("/home/wangxc/Code/APT/Resource/Holes_Book_arrival_bh_10_to_8_CL_060.bmp");
	// 暂且按照灰度图处理
	cv::cvtColor(test_signal, test_signal, CV_BGR2GRAY);
	test_signal.convertTo(test_signal, CV_32F);
	cv::imshow("test_signal", test_signal);
	model test(test_signal);

	cv::Mat error_map = test.get_error_map();

	std::ofstream fout("error_map.txt", std::ios::out);
	for (int i = 0; i < error_map.rows; i++)
	{
		for (int j = 0; j < error_map.cols; j++)
		{
			fout << error_map.at<float>(i, j) << "\t";
		}
		fout << std::endl;
	}

	cv::imshow("error_map", error_map);
	cv::imwrite("error_map.bmp", error_map);

	cv::waitKey(0);

	return 0;
}