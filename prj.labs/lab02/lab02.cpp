#include <opencv2/opencv.hpp>

int main() {
	cv::Mat image;
	image = cv::imread("../../../data/cross_0256x0256.png");
	std::vector<int> a;
	a.push_back(cv::IMWRITE_JPEG_QUALITY);
	a.push_back(25);
	cv::imwrite("cross_0256x0256_025.jpg", image, a);
	cv::Mat channels[3];
	cv::split(image, channels);
	cv::Mat image2;

	image2 = cv::imread("./cross_0256x0256_025.jpg");
	cv::Mat channels2[3];
	cv::split(image2, channels2);
	cv::Mat nulevoe_image(256,256, CV_8UC1);
	nulevoe_image = 0;

	cv::Mat monochrome_g[3] = { nulevoe_image,channels[1],nulevoe_image };
	cv::Mat monochrome_r[3] = { nulevoe_image,nulevoe_image,channels[2] };
	cv::Mat monochrome_b[3] = { channels[0],nulevoe_image,nulevoe_image };

	cv::Mat vconcat;
	cv::Mat vconcat2;
	cv::Mat mg;
	cv::Mat mr;
	cv::Mat mb;

	cv::merge(monochrome_g, 3, mg);
	cv::merge(monochrome_r, 3, mr);
	cv::merge(monochrome_b, 3, mb);

	cv::Mat vertp[] = {image,mg};
	cv::Mat vertp2[] = { mr,mb };
	cv::vconcat(vertp, 2, vconcat);
	cv::vconcat(vertp2, 2, vconcat2);

	cv::Mat hconcat[] = { vconcat,vconcat2 };
	cv::Mat thelastone;
	cv::Mat thelastone2;
	cv::hconcat(hconcat, 2, thelastone);
	cv::hconcat(hconcat, 2, thelastone2);
	a.pop_back();
	a.push_back(100);

	int gistg[256] = {0};
	int gistb[256] = { 0 };
	int gistr[256] = { 0 };
	int brightg, brightb, brightr;
	int max=0;

	for (size_t i = 0; i < 256; i++)
	{
		for (size_t j = 0; j < 256; j++)
		{
			brightb= channels[0].at<unsigned char>(i, j);
			brightg= channels[1].at<unsigned char>(i, j);
			brightr= channels[2].at<unsigned char>(i, j);
			gistb[brightb]++;
			gistg[brightg]++;
			gistr[brightr]++;

		}
	}

	for (size_t i = 0; i < 256; i++)
	{
		if (max < gistg[i])
			max = gistg[i];
		if (max < gistr[i])
			max = gistr[i];
		if (max < gistb[i])
			max = gistb[i];
	}
	
	int hist_w = 256; int hist_h = 256;
	double koef = max / hist_h;
	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(86, 86, 86));

	for (int i = 1; i < 256; i++)
	{
		line(histImage,
			cv::Point((i - 1), hist_h-gistg[i-1]/koef),
			cv::Point((i), hist_h -gistg[i]/koef),
			cv::Scalar(0, 255, 0), 1, 8, 0);

		line(histImage,
			cv::Point((i - 1), hist_h-gistb[i-1]/koef),
			cv::Point((i), hist_h -gistb[i]/koef),
			cv::Scalar(255, 0, 0), 1, 8, 0);

		line(histImage,
			cv::Point((i - 1), hist_h-gistr[i-1]/koef),
			cv::Point((i), hist_h -gistr[i]/koef),
			cv::Scalar(0, 0, 255), 1, 8, 0);

	}

	////

	int gistgg[256] = { 0 };
	int gistbb[256] = { 0 };
	int gistrr[256] = { 0 };
	brightg, brightb, brightr;
	max = 0;
	for (size_t i = 0; i < 256; i++)
	{
		for (size_t j = 0; j < 256; j++)
		{
			brightb = channels2[0].at<unsigned char>(i, j);
			brightg = channels2[1].at<unsigned char>(i, j);
			brightr = channels2[2].at<unsigned char>(i, j);
			gistbb[brightb]++;
			gistgg[brightg]++;
			gistrr[brightr]++;

		}
	}

	for (size_t i = 0; i < 256; i++)
	{
		if (max < gistgg[i])
			max = gistgg[i];
		if (max < gistrr[i])
			max = gistrr[i];
		if (max < gistbb[i])
			max = gistbb[i];
	}

	hist_w = 256; 
	hist_h = 256;
	koef = max / hist_h;
	cv::Mat histImage2(hist_h, hist_w, CV_8UC3, cv::Scalar(86, 86, 86));

	for (int i = 1; i < 256; i++)
	{
		line(histImage2,
			cv::Point((i - 1), hist_h - gistgg[i - 1] / koef),
			cv::Point((i), hist_h - gistgg[i] / koef),
			cv::Scalar(0, 255, 0), 1, 8, 0);

		line(histImage2,
			cv::Point((i - 1), hist_h - gistbb[i - 1] / koef),
			cv::Point((i), hist_h - gistbb[i] / koef),
			cv::Scalar(255, 0, 0), 1, 8, 0);

		line(histImage2,
			cv::Point((i - 1), hist_h - gistrr[i - 1] / koef),
			cv::Point((i), hist_h - gistrr[i] / koef),
			cv::Scalar(0, 0, 255), 1, 8, 0);

	}
	cv::Mat concat[] = { histImage ,histImage2 };
	cv::Mat gistresult;
	cv::hconcat(concat, 2, gistresult);
	cv::imwrite("cross_0256x0256_hists.png", gistresult);
	cv::imwrite("cross_0256x0256_png_channels.png", thelastone);
	cv::imwrite("cross_0256x0256_jpg_channels.png", thelastone2);
	cv::waitKey();
}