#ifndef POINTMAPPERIMPL_H
#define POINTMAPPERIMPL_H
#include "pointmapper.h"

class SwirlMapper : public PointMapper {
public:
    SwirlMapper (const cv::Size& size, const cv::Point &mCenter, double mMul, double mPower);
    virtual cv::Point remap(const cv::Point &p);
private:
    cv::Point mCenter;
    double mMul;
    double mPower;
};

class PolarizeMapper : public PointMapper {
public:
    PolarizeMapper (const cv::Size& size);
    virtual cv::Point remap(const cv::Point &p);
};

class DePolarizeMapper : public PointMapper {
public:
    DePolarizeMapper (const cv::Size& size);
    virtual cv::Point remap(const cv::Point &p);
};


#endif // POINTMAPPERIMPL_H
