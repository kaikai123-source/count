#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;

int main() {
	Mat src, binaryMat, labelMat, stateMat, centrMat, result;
	src = imread("D:/coin.png");
	cvtColor(src, src, CV_BGR2GRAY);
	cv::threshold(src, binaryMat, 0, 255, THRESH_OTSU);

	//获得连通域
	int com = cv::connectedComponentsWithStats(binaryMat, labelMat, stateMat, centrMat, 8, CV_32S);
	//输出连通域
	for (int i = 0; i<com; i++) {
		cout << "connected Components NO." << i << endl;
		cout << "pixels = " << stateMat.at<int>(i, 4) << endl;
		cout << "width = " << stateMat.at<int>(i, 2) << endl;
		cout << "height = " << stateMat.at<int>(i, 3) << endl;
		cout << endl;
	}

	cout << "总的连通域个数" << com - 1 << endl;
	result = cv::Mat::zeros(src.size(), CV_8UC3);
	std::vector<cv::Vec3b>colors(com);
	colors[0] = cv::Vec3b(0, 0, 0);
	for (int i = 1; i < com; i++) {
		colors[i] = cv::Vec3b(rand()/255, rand() / 255, rand() / 255);

	}

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			int label = labelMat.at<int>(j, i);
			result.at<cv::Vec3b>(j, i) = colors[label];
		}
	}

	for (int i = 1; i < com; i++) {
		Rect box;
		box.x = stateMat.at<int>(i, 0);
		box.y = stateMat.at<int>(i, 1);
		box.width = stateMat.at<int>(i, 2);
		box.height = stateMat.at<int>(i, 3);
		rectangle(result, box, CV_RGB(255, 255, 255),1,8,0);


	}
	namedWindow("binaryMat", CV_WINDOW_AUTOSIZE);
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	namedWindow("result", CV_WINDOW_AUTOSIZE);
	imshow("binaryMat", binaryMat);
	imshow("result", result);
	imshow("src", src);
	
	waitKey(0);

}