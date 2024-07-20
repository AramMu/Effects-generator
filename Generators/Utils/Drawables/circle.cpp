#include "circle.h"
#include "Utils/utils.h"
#include "Utils/calc.h"
#include <opencv2/core.hpp>
//#include <iostream>


Circle::Circle () {}
Circle::Circle (int x, int y, double r) : p(x,y), r(r) {}
Circle::Circle (const cv::Point2i& p, double r) : p(p), r(r) {}
Circle::Circle (const cv::Point2i& p1, const cv::Point2i& p2, const cv::Point2i& p3) {
    double mat[2][3];
    mat[0][0] = -2*p1.x + 2*p2.x;
    mat[0][1] = -2*p1.y + 2*p2.y;
    mat[0][2] = Calc::sqr(p2.x) + Calc::sqr(p2.y) - Calc::sqr(p1.x) - Calc::sqr(p1.y);

    mat[1][0] = -2*p1.x + 2*p3.x;
    mat[1][1] = -2*p1.y + 2*p3.y;
    mat[1][2] = Calc::sqr(p3.x) + Calc::sqr(p3.y) - Calc::sqr(p1.x) - Calc::sqr(p1.y);

    double det = Calc::crossProduct(cv::Point(mat[0][0], mat[0][1]), cv::Point(mat[1][0], mat[1][1]));
    //assert (det > 0);
    if (det == 0) {
        p = cv::Point (0,0);
        r = INF;
    } else {
        double x = Calc::crossProduct(cv::Point(mat[0][2], mat[0][1]), cv::Point(mat[1][2], mat[1][1]))/det;
        double y = Calc::crossProduct(cv::Point(mat[0][0], mat[0][2]), cv::Point(mat[1][0], mat[1][2]))/det;
        this->p = cv::Point(x,y);
        this->r = distance(p, p1);
    }
    //std::cout << "x,y,r " << x << " " << y << " " << r << std::endl;

    //x(-2p1.x + 2p2.x) + y(-2p1.y + 2p2.y) = p2.x^2 + p2.y^2 - p1.x^2 - p1.y^2
    //x(-2p1.x + 2p3.x) + y(-2p1.y + 2p3.y) = p3.x^2 + p3.y^2 - p1.x^2 - p1.y^2
}

bool Circle::contains (const cv::Point2i &pt) {
    return distanceSqr(p, pt) <= r*r;
}

bool Circle::intersect (const Circle& c1, const Circle& c2) {
    double d = distance (c1.p, c2.p);
    return (d - c2.r < c1.r && d-c2.r > -c1.r) && d + c2.r > c1.r;
}
bool Circle::contains (const Circle& c1, const Circle& c2) {
    double d = distance (c1.p, c2.p);
    return (d-c2.r < c1.r && d-c2.r > -c1.r) && (d+c2.r < c1.r && d+c2.r > -c1.r);
}



bool Circle::CompareRadius::operator () (const Circle& c1, const Circle& c2) {
    return c1.r < c2.r;
}

//void Circle::drawOutline (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, std::vector<std::vector<bool> >& used, int thick) {}

void Circle::drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, std::vector<std::vector<bool> >& used) {
    assert (img.rows == used.size() && img.cols == used[0].size());
    for (int y = p.y-r; y <= p.y+r; ++y) {
        double tmpRad = std::sqrt (Calc::sqr(r) - Calc::sqr(p.y-y));
        for (int x = p.x-tmpRad; x <= p.x+tmpRad; ++x) {
            if (y < 0 || x < 0 || y >= img.rows || x >= img.cols) {
                continue;
            }
            //double dist = distance(p, cv::Point(x,y));
            //cv::Vec3b calcColor = (dist/r*255);
            if (!used[y][x]) {
                img.at<cv::Vec3b> (y,x) = color;
            } else {
                cv::Vec3b calcColor = mixer.mix(img.at<cv::Vec3b>(y,x), color);
                img.at<cv::Vec3b> (y,x) = calcColor;
            }
            used[y][x] = true;
        }
    }
}

void Circle::drawGrad (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, std::vector<std::vector<bool> >& used) {
    assert (img.rows == used.size() && img.cols == used[0].size());
    for (int y = p.y-r; y <= p.y+r; ++y) {
        double tmpRad = std::sqrt (Calc::sqr(r) - Calc::sqr(p.y-y));
        for (int x = p.x-tmpRad; x <= p.x+tmpRad; ++x) {
            if (y < 0 || x < 0 || y >= img.rows || x >= img.cols) {
                continue;
            }
            double dist = distance(p, cv::Point(x,y));
            cv::Vec3b calcColor = (dist/r) * color;
            //for (int k = 0; k < 3; ++k) {
            //    calcColor[k] = (dist/r) * color[k];
            //}
            if (!used[y][x]) {
                img.at<cv::Vec3b> (y,x) = calcColor;
            } else {
                calcColor = mixer.mix(img.at<cv::Vec3b>(y,x), calcColor);
                img.at<cv::Vec3b> (y,x) = calcColor;
            }
            used[y][x] = true;
        }
    }
}
