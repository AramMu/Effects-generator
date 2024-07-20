#ifndef POINT_H
#define POINT_H
#include <opencv2/core/types.hpp>
//#include <opencv2/imgproc.hpp>
//#include "Utils/utils.h"

class Point {
public:
    Point();
    Point(double x, double y);
    Point(const cv::Point2d& p);
    Point(const cv::Point2i& p);
    double x;
    double y;
    class CompareXY {
    public:
        bool operator () (const Point& p1, const Point& p2);
    };
    class CompareYX {
    public:
        bool operator () (const Point& p1, const Point& p2);
    };

    class CompareY {
    public:
        CompareY ();
        CompareY (bool neg);
        bool operator () (const Point& p1, const Point& p2);
        bool mNeg;
    };

    class CompareDistance {
    public:
        CompareDistance (const Point& center);
        CompareDistance (int x, int y);
        bool operator () (const Point& p1, const Point& p2);

    private:
        double mX, mY;
    };
    friend double distanceSqr (const Point& p1, const Point& p2);
};

#endif // POINT_H
