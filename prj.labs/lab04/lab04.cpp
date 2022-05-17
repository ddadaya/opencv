#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

void video(std::string video_name, int porog_binary) {
	VideoCapture note("../../../MONEY/" + video_name + ".mp4");
	int amount_of_frames = note.get(CAP_PROP_FRAME_COUNT);
	int choose_f1 = (amount_of_frames / 5) * 2,
		choose_f2 = (amount_of_frames / 5) * 3,
		choose_f3 = (amount_of_frames / 5) * 4;
	cv::Mat frame[3];
	for (int i = 0; i < 3; i++)
	{
		if(i==0)
		note.set(CAP_PROP_POS_FRAMES, choose_f1);  //94,141,188
		else if(i==1)
		note.set(CAP_PROP_POS_FRAMES, choose_f2);  //94,141,188
		else 
		note.set(CAP_PROP_POS_FRAMES, choose_f3);  //94,141,188
		note >> frame[i];
		if (i == 0)
			imwrite(video_name + "_1_color.png", frame[0]);
		else if (i == 1)
			imwrite(video_name + "_2_color.jpg", frame[1]);
		else
			imwrite(video_name + "_3_color.png", frame[2]);
		cvtColor(frame[i], frame[i], COLOR_BGR2GRAY);
		if (i == 0)
			imwrite(video_name + "_1_grayscale.png", frame[0]);
		else if (i == 1)
			imwrite(video_name + "_2_grayscale.png", frame[1]);
		else
			imwrite(video_name + "_3_grayscale.png", frame[2]);
		threshold(frame[i], frame[i], porog_binary, 255, THRESH_BINARY);
		if (i == 0)
			imwrite(video_name + "_1_binary.png", frame[0]);
		else if (i == 1)
			imwrite(video_name + "_2_binary.png", frame[1]);
		else
			imwrite(video_name + "_3_binary.png", frame[2]);
		Mat mask;
		morphologyEx(frame[i], mask, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(40, 40)));
		if (i == 0)
			imwrite(video_name + "_1_morph.png", mask);
		else if (i == 1)
			imwrite(video_name + "_2_morph.png", mask);
		else
			imwrite(video_name + "_3_morph.png", mask);
		Mat centroids, stats, res;
		int n = cv::connectedComponentsWithStats(mask, res, stats, centroids);
		std::vector<Vec3b> labels(n);
		int max = 0, imax = 0;
		for (int j = 1; j < n; j++) {
			if (max < stats.at<int>(j, CC_STAT_AREA)) {
				max = stats.at<int>(j, CC_STAT_AREA);
				imax = j;
			}
		}
		for (size_t j = 0; j < n; j++) {
			labels[j] = Vec3b(0, 0, 0);
		}
		labels[imax] = Vec3b(255, 255, 255);
		Mat exit(mask.rows, mask.cols, CV_8UC3);
		for (size_t a = 0; a < exit.rows; a++) {
			for (size_t b = 0; b < exit.cols; b++) {
				int label = res.at<int>(a, b);
				Vec3b& pixel = exit.at<Vec3b>(a, b);
				pixel = labels[label];
			}
		}
		if (i == 0)
			imwrite(video_name + "_1_svyazi.png", exit);
		else if (i == 1)
			imwrite(video_name + "_2_svyazi.png", exit);
		else
			imwrite(video_name + "_3_svyazi.png", exit);
	}
	std::cout << '\n';
}



int main() {
	video("10",150);
	video("5",110);
	video("500",120);
	video("100old",200);
	video("100new", 177);

	//namedWindow("10r", 1);
	//for (;;)
	//{
	//	Mat frame;
	//	desyat >> frame;
	//	imshow("10r", frame);
	//	if (waitKey(30) >= 0) break;
	//}

	//imshow("a", frame1);
	//int amount_of_frames = desyat.get(CAP_PROP_POS_FRAMES);
	//std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!¸!!!  " << amount_of_frames;
	waitKey();


}