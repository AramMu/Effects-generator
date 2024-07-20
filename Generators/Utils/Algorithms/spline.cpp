#include "spline.h"



Polynomial splineStep (cv::Point b, cv::Point e, double d1, double d2) {
    cv::Point center(b);
    e = e-b;
    b = b-b;

}

std::vector <Polynomial> spline (const std::vector <cv::Point>& p) {
    int n = p.size();
    double d1(0), d2(0);
    std::vector<Polynomial> res(n-1);
    for (int i = 0; i < n-1; ++i) {
        Polynomial t = splineStep(p[i], p[i+1], d1, d2);
        Polynomial t1 = t.derivate();
        Polynomial t2 = t1.derivate();
        double x = p[i+1].x-p[i].x;
        d1 = t1.eval(x);
        d2 = t2.eval(x);
    }
    return res;
}
