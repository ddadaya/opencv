#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;



int main() {
    Mat default(300, 450, CV_32FC1);

    const int c = 2, r = 3;
    double color_rectangle[c][r] = {0,0.5,1,1,0,0.5};
    double color_circle[] = {1,0,0.5,0,0.5,1};

    int place = 150;
    Rect2d rectangle(0, 0, 150, 150);

    int cnt = 0;

    for (int i = 0; i < c; i++)
    {
        rectangle.y = i * place;

        for (int j = 0; j < r; j++)
        {
            rectangle.x = j * place;
            Mat tmp = default(rectangle);
            tmp = color_rectangle[i][j];
            circle(default, Point(rectangle.x + 75, rectangle.y + 75), 70, color_circle[cnt],-1);
            cnt++;
        }
    }
   

    Mat I1(2, 2, CV_32S);
    I1.at<int>(0, 0) = 1;
    I1.at<int>(0, 1) = 0;
    I1.at<int>(1, 0) = 0;
    I1.at<int>(1, 1) = -1;
    Mat image_f1;

    filter2D(default, image_f1, -1, I1, Point(0, 0));

    Mat I2(2, 2, CV_32S);
    I2.at<int>(0, 0) = 0;
    I2.at<int>(0, 1) = 1;
    I2.at<int>(1, 0) = -1;
    I2.at<int>(1, 1) = 0;
    Mat image_f2;

    filter2D(default, image_f2, -1, I2, Point(0, 0));

    Mat end_image(default.size(), CV_32FC1);
    for (size_t i = 0; i < end_image.rows; i++)
    {
        for (size_t j = 0; j < end_image.cols; j++)
        {
            end_image.at<float>(i, j) = sqrt(pow(image_f1.at<float>(i, j), 2) + pow(image_f2.at<float>(i, j), 2));
        }
    }

    image_f1 = (image_f1 + 1) / 2;
    image_f2 = (image_f2 + 1) / 2;
    
    imwrite("start_image.png", default * 255);
    imwrite("image_f1.png", image_f1 * 255);
    imwrite("image_f2.png", image_f2 * 255);
    imwrite("end_image.png", end_image * 255);

}