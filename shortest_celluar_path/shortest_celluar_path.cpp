#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <random>
#include "../cpptimer/cpptimer.h"

int generateMap(cv::Mat& map, int w, int h) {
	map = cv::Mat(h, w, CV_8U);
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<int> distribution(0, 20);

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			map.at<uchar>(i, j) = (distribution(mt) == 0) ? 0 : 255;
		}
	}

	return 0;
}

void mouseHandler(int event, int x, int y, int, void*) {
	std::cout << x << "  " << y << std::endl; 
}

int main()
{
	cppTimer time;
	cv::Mat main_map;
	generateMap(main_map, 800, 600);

	std::string window_name = "Window";
	cv::namedWindow(window_name);
	cv::imshow(window_name, main_map);
	cv::setMouseCallback(window_name, mouseHandler, NULL);
	cv::waitKey();

	return 0;
}