#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <random>
#include <thread>
#include "../cpptimer/cpptimer.h"

void generateMap(cv::Mat& map, int w, int h) {
	map = cv::Mat(h, w, CV_8U);
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<int> distribution(0, 20);

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			map.at<uchar>(i, j) = (distribution(mt) == 0) ? 0 : 255;
		}
	}
}

void changeMap(int event) {
}

void printEvent(int event) {
	std::cout << event << std::endl;
}

static void mouseHandler(int event, int x, int y, int flags, void* param) {
	cv::Mat* map = static_cast<cv::Mat*> (param);

	if (event == cv::EVENT_LBUTTONDOWN) {
		map->at<uchar>(y, x) = 0;
	}
	else if (event == cv::EVENT_RBUTTONDOWN) {
		map->at<uchar>(y, x) = 255;
	}
}

int main()
{
	//cppTimer time;
	cv::Mat main_map;
	generateMap(main_map, 800, 600);

	std::string window_name = "Window";
	cv::namedWindow(window_name);
	//cv::imshow(window_name, main_map);

	cv::setMouseCallback(window_name, mouseHandler, &main_map);

	std::thread ([&]() {
		while (true) {
			cv::imshow(window_name, main_map);
		}
		}).detach();
	cv::waitKey();

	return 0;
}