#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main() {
	Mat src, binaryMat, labelMat, stateMat, centrMat, result;
	src = imread("D:/coin.png");
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
	//绘制box
	for (int i = 1; i < com; i++) {
		Rect box;
		box.x = stateMat.at<int>(i, 0);
		box.y = stateMat.at<int>(i, 1);
		box.width = stateMat.at<int>(i, 2);
		box.height = stateMat.at<int>(i, 3);

	}
	namedWindow("binaryMat", CV_WINDOW_AUTOSIZE);
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	namedWindow("result", CV_WINDOW_AUTOSIZE);
	imshow("binaryMat", binaryMat);
	imshow("result", result);
	imshow("src", src);
	moveWindow("src", 0, 20);
	moveWindow("binaryMat", src.cols, 20);
	moveWindow("result", src.cols * 2, 20);



	waitKey(0);




}