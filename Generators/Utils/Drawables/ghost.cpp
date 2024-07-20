#include "ghost.h"
#include "parabola.h"
#include <opencv2/imgproc.hpp>

Ghost::Ghost() {}

Ghost::Ghost (double h, double c, double p) : h(h), c(c), p(p) {}


void Ghost::drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool>& used) {
    Parabola(h,c,p).drawFill(img, color, mixer, used);
}

void Ghost::drawEyes (cv::Mat& img, cv::Vec3b color) {
    double yRatio(15);
    double xRatio(15);
    double xOffRatio(2.5);
    double xLen(sqrt(-h/p) * 2);
    int eyeY = h*0.75;
    double xOff(sqrt((h-eyeY)/-p));
    //std::cout << xOff << std::endl;
    cv::ellipse(img, cv::Point(c-xOff/xOffRatio, eyeY), cv::Size(xLen/xRatio, h/yRatio), 0, 0, 360, cv::Vec3b(0,0,0), -1);
    cv::ellipse(img, cv::Point(c+xOff/xOffRatio, eyeY), cv::Size(xLen/xRatio, h/yRatio), 0, 0, 360, cv::Vec3b(0,0,0), -1);
}

void Ghost::drawFill (cv::Mat& img, cv::Vec3b color) {
    Parabola(h,c,p).drawFill(img, color);
}
void Ghost::drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used) {
    Parabola(h,c,p).drawGrad(img, color1, color2, mixer, used);
}
void Ghost::drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2) {
    Parabola(h,c,p).drawGrad(img, color1, color2);
}
void Ghost::drawOutline (cv::Mat& img, cv::Vec3b color, int thick) {
    Parabola(h,c,p).drawOutline(img, color, thick);
}
