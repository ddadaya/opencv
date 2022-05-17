#include <opencv2/opencv.hpp>

int main() {
  cv::Mat I_1(60, 768, CV_8UC1);
  cv::imshow("a", I_1);
  // draw dummy image
  I_1 = 0;

  for (int i = 0; i < I_1.rows; i++)
  {
	  for (int j = 0; j < I_1.cols; j++)
	  {
		  I_1.at<uint8_t>(i, j) = j/3;
	  }
  }

  cv::Mat G_1 = I_1.clone();
  cv::TickMeter tm;
  tm.start();
  I_1.convertTo(G_1, CV_32FC1, 1.0 / 255.0);
  pow(G_1, 2.2, G_1);
  G_1.convertTo(G_1, CV_8UC1, 255.0/1.0);
  tm.stop();
  std::cout << "Total time: " << tm.getTimeSec() << std::endl;

  cv::Mat G_2 = I_1.clone();
  tm.reset();
  tm.start();
  for (int i = 0; i < I_1.rows; i++)
  {
	  for (int j = 0; j < I_1.cols; j++)
	  {
		  G_2.at<uint8_t>(i, j) = pow(G_2.at<uint8_t>(i, j) / 255.0, 2.2) * 255.0;
	  }
  }
  tm.stop();
  std::cout << "Total time: " << tm.getTimeSec() << std::endl;
  cv::Mat concat;
  cv::Mat asd[] = {I_1,G_1,G_2};
  cv::vconcat(asd, 3, concat);

  // save result
  cv::imwrite("lab01.png", concat);
  cv::imshow("lab01", concat);
  cv::waitKey(0);
}


