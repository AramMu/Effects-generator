#ifndef TONGUE_H
#define TONGUE_H
#include <opencv2/core.hpp>
#include "Functions/colormixer.h"
#include "Utils/matrix.h"

class Tongue {
public:
    Tongue ();
    Tongue (double centerX, double height, double p2hRatio, double ampl, double thick, double buttomY = 0, double offset=0);
    void drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool>& used);
    void drawFill (cv::Mat& img, cv::Vec3b color);
    void drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used);
    void drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2);
    void drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used);
    void drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2);
    double centerX;
    double height;
    double p2hRatio;
    double ampl;
    double thick;
    double buttomY;
    double offset;
};

#endif // TONGUE_H
