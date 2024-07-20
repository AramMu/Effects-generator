#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <opencv2/core.hpp>

class Transformation {
public:
    static void trapezoid (const cv::Mat& input, cv::Mat& out, double ratio, cv::Vec3b background = cv::Vec3b(0,0,0));
    static void polarize (const cv::Mat& input, cv::Mat& out);
    static void dePolarize (const cv::Mat& input, cv::Mat& out);
    static void swirl (const cv::Mat& input, cv::Mat& out, const cv::Point &center, double radius, double mul, double power);
    static void shiftX (const cv::Mat& input, cv::Mat& out, int pixelCount);
    static void shiftY (const cv::Mat& input, cv::Mat& out, int pixelCount);
};

#endif // TRANSFORMATION_H
