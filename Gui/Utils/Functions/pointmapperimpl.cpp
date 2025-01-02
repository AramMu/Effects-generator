//#include "pointmapperimpl.h"
//#include "Utils/utils.h"
//SwirlMapper::SwirlMapper (const cv::Size& size, const cv::Point& center, double mul, double power) :
//    PointMapper(size, size),
//    mCenter(center),
//    mMul(mul),
//    mPower(power) {}

//cv::Point SwirlMapper::remap(const cv::Point &p) {
//    int r = distanceSqr(mCenter, p);
//    double ang = mMul*std::exp(mPower*r);
//    return cv::Point (p.x*Calc::cos(ang) - p.y*Calc::sin(ang), p.x*Calc::sin(ang) + p.y*Calc::cos(ang));
//}



//PolarizeMapper::PolarizeMapper (const cv::Size& size) :
//    PointMapper(size, size)
//{}

//cv::Point PolarizeMapper::remap(const cv::Point &p) {
//    double r = p.y/2.0;
//    double ang = 2*PI*(p.x-mNewSize.width) / mNewSize.width;
//    return cv::Point (r*Calc::cos(ang), r*Calc::sin(ang));
//}



//DePolarizeMapper::DePolarizeMapper (const cv::Size& size) :
//    PointMapper(size,size)
//{}

//cv::Point DePolarizeMapper::remap(const cv::Point &p) {
//    double r = std::sqrt (Calc::sqr(p.x) + Calc::sqr(p.y));
//    double ang = std::atan2(p.y, p.x);
//    return cv::Point (ang/(2*PI)*mNewSize.width + mNewSize.width/2, r*2);
//}





