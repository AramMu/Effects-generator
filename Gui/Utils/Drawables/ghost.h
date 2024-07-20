#ifndef GHOST_H
#define GHOST_H
#include <opencv2/core.hpp>
#include "Utils/matrix.h"
#include "Functions/colormixer.h"

class Ghost {
public:
    Ghost ();
    Ghost (double h, double c, double p);
    double h;
    double c;
    double p;

    void drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool>& used);
    void drawFill (cv::Mat& img, cv::Vec3b color);
    void drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used);
    void drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2);
    void drawOutline (cv::Mat& img, cv::Vec3b color, int thick);
    void drawEyes (cv::Mat& img, cv::Vec3b color);
};

#endif // GHOST_H
