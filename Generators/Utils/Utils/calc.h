#ifndef CALC_H
#define CALC_H
#include <string>
//#include <fstream>
#include <vector>
//#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include "matrix.h"
#include <cmath>

const int INF = 10000000;
//3.14159265358979323846264338327950288
const double PI = 3.14159265358979323846;
const double SQRT2 = 1.414213;

class Calc {
public:
    static bool load (const std::string& fileName);
    static int abs (int x);
    static double abs (double x);
    static int sqr (int x);
    static long long sqr (long long x);
    static double sqr (double x);
    static int round (double x);
    static int ceil (double x);
    static int floor (double x);
    static double sin (double x);
    static double cos (double x);
    static double tan (double x);

    static double angle (const cv::Point& p);
    static double angle (const cv::Point& p1, const cv::Point& p2);
    static double angle (const cv::Point& p1, const cv::Point& p2, const cv::Point& p3);
    static double crossProduct (const cv::Point& p1, const cv::Point& p2);
    static double crossProduct (const cv::Point& p1, const cv::Point& p2, const cv::Point& p3);

    static std::vector<double> solveLinear (const Matrix<double>& input);
private:
    //static bool isLoaded;
    static std::vector <double> val;
    static int n;
};










inline
int Calc::abs (int x) {
    return x >= 0 ? x : -x;
}

inline
double Calc::abs (double x) {
    return x >= 0 ? x : -x;
}

inline
int Calc::round (double x) {
    return int (x + 0.5*(x >= 0 ? 1 : -1) );
}

inline
int Calc::ceil (double x) {
    if (x >= 0) {
        return int(x-0.00001+1);
    } else {
        return int(x+0.00001);
    }
}

inline
int Calc::floor (double x) {
    if (x >= 0) {
        return int(x+0.00001);
    } else {
        return int(x+0.00001-1);
    }
}

inline
int Calc::sqr (int x) {
    return x*x;
}

inline
long long Calc::sqr (long long x) {
    return x*x;
}

inline
double Calc::sqr (double x) {
    return x*x;
}

inline
double Calc::sin (double x) {
    /*
    if (x < 0) return -sin(-x);
    x = x - int(x/(2*PI)) * (2*PI);
    if (x > PI) {
        return -sin(x-PI);
    }
    if (x > PI/2) {
        x = PI - x;
    }
    return val [round (x/(PI/2) * n)];
    */
    return std::sin(x);
}

inline
double Calc::cos (double x) {
    //return sin(x+PI/2);
    return std::cos(x);
}

inline
double Calc::tan (double x) {
    //return sin(x)/sin(x+PI/2);
    return std::tan(x);
}

inline
double Calc::angle (const cv::Point& p) {
    double res = std::atan2(p.y, p.x);
    if (res < 0) {
        res += 2*PI;
    }
    return res;
}

inline
double Calc::angle (const cv::Point& p1, const cv::Point& p2) {
    double res = std::atan2 (p2.y-p1.y, p2.x-p1.x);
    if (res < 0) res += PI*2;
    return res;
}

inline
double Calc::angle (const cv::Point& p1, const cv::Point& p2, const cv::Point& p3) {
    return angle (p1, p2) - angle (p3, p2);
}

inline
double Calc::crossProduct (const cv::Point& p1, const cv::Point& p2) {
    return p1.x*p2.y - p1.y*p2.x;
}

inline
double Calc::crossProduct (const cv::Point& p1, const cv::Point& p2, const cv::Point& p3) {
    cv::Point v1(p2.x-p1.x, p2.y-p1.y), v2(p3.x-p2.x, p3.y-p2.y);
    return crossProduct(v1, v2);
}





#endif // CALC_H
