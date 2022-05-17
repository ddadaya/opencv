#include <opencv2/opencv.hpp>
#include <cmath>



int main() {
	cv::Mat pic = cv::imread("../../../data/cross_0256x0256.png");
	cv::imwrite("lab03_rgb.png", pic);


	cv::Mat gray;
	cv::cvtColor(pic, gray, cv::COLOR_BGR2GRAY);
	cv::imwrite("lab03_gre.png", gray);


	std::vector<uchar> bright;
	for (size_t i = 0; i < 256; i++) {
		bright.push_back((i^10)/(64-(i/4))+20/(i+1));
	}
	for (size_t i = 0; i < gray.rows; i++) {
		for (size_t j = 0; j < gray.cols; j++) {
			gray.at<uint8_t>(i, j)  = bright[gray.at<uint8_t>(i, j)] + '0';
		}
	}
	cv::imwrite("lab03_gre_res.png", gray);


	cv::Mat channels[3];
	cv::split(pic, channels);
	for (size_t i = 0; i < gray.rows; i++) {
		for (size_t j = 0; j < gray.cols; j++) {
			channels[0].at<uint8_t>(i, j) = bright[channels[0].at<uint8_t>(i, j)] + '0';
			channels[1].at<uint8_t>(i, j) = bright[channels[1].at<uint8_t>(i, j)] + '0';
			channels[2].at<uint8_t>(i, j) = bright[channels[2].at<uint8_t>(i, j)] + '0';
		}
	}
	cv::Mat allin[3] = { channels[0],channels[1] ,channels[2] };
	cv::Mat result;
	cv::merge(allin, 3, result);
	cv::imwrite("lab03_rgb_res.png", result);


	int hist_w = 512; int hist_h = 512;
	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(256, 256, 256));
	for (size_t i = 0; i < hist_h; i+=2)
	{
		line(histImage,
			cv::Point(0, 512),
			cv::Point(0, 0),
			cv::Scalar(0, 0, 0), 2, 8, 0);
		line(histImage,
			cv::Point(0, 511),
			cv::Point(511, 511),
			cv::Scalar(0, 0, 0), 2, 8, 0);
			cv::circle(histImage, cv::Point(i, hist_h-bright[i/2]-3),0, cv::Scalar(0, 0, 255),2);
		
	}
	cv::imwrite("lab03_viz_func.png", histImage);
	cv::imshow("lab03_viz_func.png", histImage);
	cv::waitKey();
}