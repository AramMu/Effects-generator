#ifndef POINTMAPPER_H
#define POINTMAPPER_H
#include <opencv2/core/types.hpp>

class SwirlMapper {
public:
    SwirlMapper (const cv::Size& size, const cv::Point &center, double radius, double mul, double power);
    cv::Point2f operator () (const cv::Point &p1);
private:
    cv::Size mSize;
    cv::Point mCenter;
    double mRadius;
    double mMul;
    double mPower;
};

class PolarizeMapper {
public:
    PolarizeMapper (const cv::Size& size);
    cv::Point2f operator () (const cv::Point &p);
private:
    cv::Size mSize;
};

class DePolarizeMapper {
public:
    DePolarizeMapper (const cv::Size& size);
    cv::Point2f operator () (const cv::Point &p1);
private:
    cv::Size mSize;
};

class ShiftXMapper {
public:
    ShiftXMapper (const cv::Size& size, int pixelCount);
    cv::Point2f operator () (const cv::Point &p1);
private:
    cv::Size mSize;
    int mPixelCount;
};

class ShiftYMapper {
public:
    ShiftYMapper (const cv::Size& size, int pixelCount);
    cv::Point2f operator () (const cv::Point &p1);
private:
    cv::Size mSize;
    int mPixelCount;
};

#endif // POINTMAPPER_H
