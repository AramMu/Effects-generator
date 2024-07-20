#include "pointmapper.h"
#include "Utils/calc.h"
#include "Utils/utils.h"
#include <iostream>

SwirlMapper::SwirlMapper (const cv::Size& size, const cv::Point &center, double radius, double mul, double power) :
    mSize(size), mCenter(center), mRadius(radius), mMul(mul), mPower(power)
{}
cv::Point2f SwirlMapper::operator ()(const cv::Point& p1) {
    cv::Point p(p1-mCenter);
    int r = std::sqrt(Calc::sqr(p.x) + Calc::sqr(p.y));
    if (r > mRadius) {
        return p;
    }
    double ang = mMul*std::exp(mPower*r);
    //std::cout << "Ang = " << ang << std::endl;
    return cv::Point2f (p.x*Calc::cos(ang) - p.y*Calc::sin(ang)+mCenter.x, p.x*Calc::sin(ang) + p.y*Calc::cos(ang)+mCenter.y);
}


PolarizeMapper::PolarizeMapper (const cv::Size& size) :
    mSize(size)
{}

cv::Point2f PolarizeMapper::operator ()(const cv::Point &p) {
    double r = p.y/2.0;
    double ang = 2*PI*p.x / mSize.width;
    //int minSize = std::min(mSize.width, mSize.height)/2;
    //cv::Point2f ret = {r*Calc::cos(ang)+minSize, r*Calc::sin(ang)+minSize};
    //return ret;
    return cv::Point2f (r*Calc::cos(ang)+mSize.width/2, r*Calc::sin(ang)+mSize.height/2);
}


DePolarizeMapper::DePolarizeMapper (const cv::Size& size) :
    mSize(size)
{}

cv::Point2f DePolarizeMapper::operator ()(const cv::Point &p1) {
    cv::Point p = {p1.x-mSize.width/2, p1.y-mSize.height/2};
    double r = std::sqrt (Calc::sqr(p.x) + Calc::sqr(p.y));
    double ang = std::atan2(p.y, p.x);
    if (ang < 0) ang += 2*PI-0.01;
    return cv::Point2f (ang/(2*PI)*mSize.width, r*2);
}


ShiftXMapper::ShiftXMapper (const cv::Size &size, int pixelCount) :
    mSize(size), mPixelCount(pixelCount)
{}

cv::Point2f ShiftXMapper::operator ()(const cv::Point& p) {
    cv::Point2f ret(p.x+mPixelCount, p.y);
    if (ret.x >= mSize.width) {
        ret.x -= mSize.width;
    } else if (ret.x < 0) {
        ret.x += mSize.width;
    }
    return ret;
}


ShiftYMapper::ShiftYMapper (const cv::Size &size, int pixelCount) :
    mSize(size), mPixelCount(pixelCount) {}

cv::Point2f ShiftYMapper::operator ()(const cv::Point& p) {
    cv::Point2f ret(p.x, p.y+mPixelCount);
    if (ret.y >= mSize.height) {
        ret.y -= mSize.height;
    } else if (ret.y < 0) {
        ret.y += mSize.height;
    }
    return ret;
}
