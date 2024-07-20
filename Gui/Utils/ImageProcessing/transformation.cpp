#include "transformation.h"
#include "Functions/pointmapper.h"
#include <opencv2/imgproc.hpp>

void Transformation::trapezoid (const cv::Mat& input, cv::Mat& out, double ratio, cv::Vec3b background) {
    assert(input.type() == CV_8UC3);
    cv::Mat output (input.size(), CV_8UC3);
    ratio = 1-ratio;
    for (int i = 0; i < input.rows; ++i) {
        int len = input.cols * (1 - ratio*i/input.rows);
        cv::Mat tmp (1, input.cols, CV_8UC3);
        for (int j = 0; j < input.cols; ++j) {
            tmp.at<cv::Vec3b>(0,j) = input.at<cv::Vec3b>(i,j);
        }
        for (int j = 0; j < input.cols; ++j) {
            output.at<cv::Vec3b>(i,j) = background;
        }
        if (len <= 0) {
            continue;
        }
        cv::resize(tmp, tmp, cv::Size(len, 1));
        double offset = (input.cols - len)/2;
        for (int j = 0; j < len; ++j) {
            output.at<cv::Vec3b>(i, j+offset) = tmp.at<cv::Vec3b>(0,j);
        }
    }
    out = output;
}

void _map (const cv::Mat& input, cv::Mat& out, auto func) {
    cv::Mat mapX(input.size(), CV_32FC1);
    cv::Mat mapY(input.size(), CV_32FC1);
    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            cv::Point2f p = func(cv::Point(j,i));
            mapX.at<float>(i,j) = p.x;
            mapY.at<float>(i,j) = p.y;
        }
    }
    cv::remap(input, out, mapX, mapY, cv::INTER_LINEAR);
}

void Transformation::polarize (const cv::Mat& input, cv::Mat& out) {
    _map (input, out, DePolarizeMapper(input.size()));
}
void Transformation::dePolarize (const cv::Mat& input, cv::Mat& out) {
    _map (input, out, PolarizeMapper(input.size()));
}
void Transformation::swirl (const cv::Mat& input, cv::Mat& out, const cv::Point& center, double radius, double mul, double power) {
    _map (input, out, SwirlMapper(input.size(), center, radius, -mul, power));
}
void Transformation::shiftX (const cv::Mat& input, cv::Mat& out, int pixelCount) {
    _map (input, out, ShiftXMapper(input.size(), -pixelCount));
}

void Transformation::shiftY (const cv::Mat& input, cv::Mat& out, int pixelCount) {
    _map (input, out, ShiftYMapper(input.size(), -pixelCount));
}
