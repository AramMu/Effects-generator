#include "ellipse.h"
#include "Utils/calc.h"
#include <opencv2/core.hpp>

Oval::Oval() {}

Oval::Oval(const cv::Point& p, double lenX, double lenY):
    p(p),
    lenX(lenX),
    lenY(lenY)
{
    assert(lenX>0);
    assert(lenY>0);
}

void Oval::drawFill (cv::Mat& mat, cv::Vec3b color) {
    int minX = std::max (0, int (p.x-lenX));
    int maxX = std::min (mat.cols-1, int (p.x+lenX));
    for (int x = minX; x <= maxX; ++x) {
        int minY = std::max (0,
            int (p.y - std::sqrt((1 - Calc::sqr(x-p.x) / Calc::sqr(lenX))*Calc::sqr(lenY) )));
        int maxY = std::min (mat.rows-1,
            int (p.y + std::sqrt((1 - Calc::sqr(x-p.x) / Calc::sqr(lenX))*Calc::sqr(lenY) )));

        for (int y = minY; y <= maxY; ++y) {
            mat.at<cv::Vec3b> (y,x) = color;
        }
    }
}


