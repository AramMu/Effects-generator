#include "polynomial.h"
#include <opencv2/imgproc.hpp>

Polynomial::Polynomial(const std::vector<double>& a, cv::Point s) : a(a), c(s) {}

Polynomial Polynomial::derivate() {
    std::vector<double> r(a.size()-1);
    for (int i = 1; i < a.size(); ++i) {
        r[i-1] = i*a[i];
    }
    return Polynomial(r, c);
}


double Polynomial::eval(double x) {
    double y = 0;
    for (int i = a.size()-1; i >= 0; --i) {
        y = y*x + a[i];
    }
    return y;
}

void Polynomial::draw(cv::Mat &img, cv::Vec3b color, int width, int b, int e) {
    cv::Point prev(b, eval(b-c.x)+c.y);
    cv::circle(img, prev, ceil(width/2), color, -1);
    for (int x = b+1; x <= e; ++x) {
        cv::Point next(x, eval(x-c.x)+c.y);
//        std::cout << eval(x-c.x)+c.y << std::endl;
        cv::circle(img, next, ceil(width/2), color, -1);
        cv::Point prevT(prev), nextT(next);
        if (cv::clipLine(img.size(), prevT, nextT)) {
            cv::line(img, prevT, nextT, color, width);
        }
//        cv::line(img, prev, next, color, width);
        prev = next;
    }
}


void Polynomial::draw(cv::Mat& img, cv::Vec3b color, int width) {
    draw(img,color,width, 0, img.cols-1);
}
