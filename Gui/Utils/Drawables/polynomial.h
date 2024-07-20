#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <opencv2/core.hpp>

class Polynomial
{
public:
    Polynomial()=default;
    Polynomial(const std::vector<double>& a, cv::Point c={0,0});


    void draw(cv::Mat& img, cv::Vec3b color, int width);
    void draw(cv::Mat &img, cv::Vec3b color, int width, int b, int e);

    std::vector<double> a;
    cv::Point c;

    double eval(double x);
    Polynomial derivate();
};

#endif // POLYNOMIAL_H
