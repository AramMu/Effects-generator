#ifndef SPLINE_H
#define SPLINE_H
#include "Utils/Drawables/polynomial.h"

Polynomial splineStep (cv::Point b, cv::Point e, double d1, double d2);
std::vector <Polynomial> spline (const std::vector <cv::Point>& p);

#endif // SPLINE_H
