#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <opencv2/core/types.hpp>

class Oval {
public:
    Oval();
    Oval(const cv::Point& p, double lenX, double lenY);

    void drawFill (cv::Mat &mat, cv::Vec3b color);

    cv::Point p;
    double lenX;
    double lenY;
};

#endif // ELLIPSE_H
