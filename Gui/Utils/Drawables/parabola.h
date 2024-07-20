#ifndef PARABOLA_H
#define PARABOLA_H
#include <opencv2/core.hpp>
#include "Functions/colormixer.h"
#include "Utils/utils.h"
#include "Utils/matrix.h"

class Parabola {
public:
    Parabola ();
    Parabola (double h, double c, double p);
    double h;
    double c;
    double p;

    void drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool>& used);
    void drawFill (cv::Mat& img, cv::Vec3b color);
    void drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used);
    void drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2);
    void drawOutline (cv::Mat& img, cv::Vec3b color, int thick);
};

#endif // PARABOLA_H
