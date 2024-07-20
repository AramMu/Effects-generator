#include "point.h"
#include "Utils/calc.h"

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y): x(x), y(y) {}
Point::Point(const cv::Point2d& p) : x(p.x), y(p.y) {}
Point::Point(const cv::Point2i& p) : x(p.x), y(p.y) {}

double distanceSqr (const Point& p1, const Point& p2) {
    return Calc::sqr (p1.x - p2.x) + Calc::sqr (p1.y - p2.y);
}

bool Point::CompareXY::operator () (const Point& p1, const Point& p2) {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool Point::CompareYX::operator () (const Point& p1, const Point& p2) {
    return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}

Point::CompareY::CompareY () : mNeg(false) {}
Point::CompareY::CompareY (bool neg) : mNeg(neg) {}
bool Point::CompareY::operator () (const Point& p1, const Point& p2) {
    return (p1.y < p2.y) ^ mNeg;
}


Point::CompareDistance::CompareDistance (const Point& center): mX(center.x), mY(center.y) {}
Point::CompareDistance::CompareDistance (int x, int y): mX(x), mY(y) {}
bool Point::CompareDistance::operator () (const Point& p1, const Point& p2) {
    /*
    double x1s = p1.x - mX;
    double y1s = p1.y - mY;
    double x2s = p2.x - mX;
    double y2s = p2.y - mY;
    x1s = x1s*x1s;
    y1s = y1s*y1s;
    x2s = x2s*x2s;
    y2s = y2s*y2s;
    return x1s + y1s < x2s + y2s;
    */
    return distanceSqr(p1, Point(mX,mY)) < distanceSqr(p2, Point(mX,mY));
}
