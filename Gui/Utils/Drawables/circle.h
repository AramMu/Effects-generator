#ifndef CIRCLE_H
#define CIRCLE_H
#include <opencv2/core/types.hpp>
//#include <opencv2/imgproc.hpp>
#include "Functions/colormixer.h"

class Circle {
public:
    Circle ();
    Circle (int x, int y, double r);
    Circle (const cv::Point2i& p, double r);
    Circle (const cv::Point2i& p1, const cv::Point2i& p2, const cv::Point2i& p3);

    bool contains (const cv::Point2i& pt);
    static bool intersect (const Circle& c1, const Circle& c2);
    static bool contains (const Circle& c1, const Circle& c2);

    class CompareRadius {
    public:
        bool operator () (const Circle& c1, const Circle& c2);
    };
    //void drawOutline (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, std::vector<std::vector<bool> >& used, int thick);
    void drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, std::vector<std::vector<bool> >& used);
    void drawGrad (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, std::vector<std::vector<bool> >& used);


    cv::Point2i p;
    double r;
};

#endif // CIRCLE_H
