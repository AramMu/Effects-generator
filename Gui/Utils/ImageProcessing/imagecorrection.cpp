#include "imagecorrection.h"



void ImageCorrection::adjustContrast (const cv::Mat& input, cv::Mat& out, double value) {
    assert (input.type() == CV_8UC3);
    //Enable when ready to go to [-1,+1] range
    //value = std::pow(16, value+1) - 1;


    //output = cv::Mat(input.size(), CV_8UC3);
    cv::Mat output(input.size(), CV_8UC3);
    for (int i = 0; i < output.rows; ++i) {
        for (int j = 0; j < output.cols; ++j) {
            for (int k = 0; k < 3; ++k) {
                double tmp = value * (input.at<cv::Vec3b>(i,j)[k] - 127.5) + 127.5;
                if (tmp < 0) tmp = 0;
                if (tmp > 255) tmp = 255;
                output.at<cv::Vec3b> (i,j)[k] = tmp;
            }
        }
    }
    out = output;
}
