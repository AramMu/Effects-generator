#include "utils.h"
#include <cmath>
#include "randomgenerator.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "calc.h"
#include <cassert>

double distance (const cv::Point2i& p1, const cv::Point2i& p2) {
    return std::sqrt (Calc::sqr (p1.x - p2.x) + Calc::sqr (p1.y - p2.y));
}
double distance (const cv::Point2d& p1, const cv::Point2d& p2){
    return std::sqrt (Calc::sqr (p1.x - p2.x) + Calc::sqr (p1.y - p2.y));
}

int distanceSqr (const cv::Point2i &p1, const cv::Point2i &p2) {
    return Calc::sqr (p1.x - p2.x) + Calc::sqr (p1.y - p2.y);
}
double distanceSqr (const cv::Point2d &p1, const cv::Point2d &p2) {
    return Calc::sqr (p1.x - p2.x) + Calc::sqr (p1.y - p2.y);
}


int distanceChess (const cv::Point2i& p1, const cv::Point2i& p2) {
    return std::min (Calc::abs (p1.x-p2.x), Calc::abs (p1.y-p2.y));
}
double distanceChess (const cv::Point2d& p1, const cv::Point2d& p2) {
    return std::min (Calc::abs (p1.x-p2.x), Calc::abs (p1.y-p2.y));
}
int distanceCity (const cv::Point2i& p1, const cv::Point2i& p2) {
    return Calc::abs (p1.x - p2.x) + Calc::abs (p1.y - p2.y);
}
double distanceCity (const cv::Point2d& p1, const cv::Point2d& p2) {
    return Calc::abs (p1.x - p2.x) + Calc::abs (p1.y - p2.y);
}



bool rangeCheck (const cv::Mat& mat, const cv::Point2i& p) {
    return p.y >= 0 && p.y < mat.rows && p.x >= 0 && p.x < mat.cols;
}
bool rangeCheck (const cv::Mat& mat, const cv::Point2d& p) {
    return p.y >= 0 && p.y < mat.rows && p.x >= 0 && p.x < mat.cols;
}
bool rangeCheck (const cv::Mat& mat, int y, int x) {
    return y >= 0 && y < mat.rows && x >= 0 && x < mat.cols;
}

bool rangeCheck (const std::vector <std::vector <int> >& mat, const cv::Point2i& p) {
    return p.y >= 0 && p.y < mat.size() && p.x >= 0 && p.x < mat[0].size();
}
bool rangeCheck (const std::vector <std::vector <bool> >& mat, const cv::Point2i& p) {
    return p.y >= 0 && p.y < mat.size() && p.x >= 0 && p.x < mat[0].size();
}
bool rangeCheck (const std::vector <std::vector <double> >& mat, const cv::Point2i& p) {
    return p.y >= 0 && p.y < mat.size() && p.x >= 0 && p.x < mat[0].size();
}

bool rangeCheck (const std::vector <std::vector <int> >& mat, const cv::Point2d& p) {
    return p.y >= 0 && p.y < mat.size() && p.x >= 0 && p.x < mat[0].size();
}
bool rangeCheck (const std::vector <std::vector <bool> >& mat, const cv::Point2d& p) {
    return p.y >= 0 && p.y < mat.size() && p.x >= 0 && p.x < mat[0].size();
}
bool rangeCheck (const std::vector <std::vector <double> >& mat, const cv::Point2d& p) {
    return p.y >= 0 && p.y < mat.size() && p.x >= 0 && p.x < mat[0].size();
}

bool rangeCheck (const std::vector <std::vector <int> >& mat, int y, int x) {
    return y >= 0 && y < mat.size() && x >= 0 && x < mat[0].size();
}
bool rangeCheck (const std::vector <std::vector <bool> >& mat, int y, int x) {
    return y >= 0 && y < mat.size() && x >= 0 && x < mat[0].size();
}
bool rangeCheck (const std::vector <std::vector <double> >& mat, int y, int x) {
    return y >= 0 && y < mat.size() && x >= 0 && x < mat[0].size();
}

bool valueBoundCheck (double min, double max, double val) {
    return val >= min && val <= max;
}

std::vector <cv::Point> getNeighbours (const cv::Mat& mat, const cv::Point2i& p) {
    std::vector <cv::Point> res;
    for (int i = p.y-1; i <= p.y+1; ++i) {
        for (int j = p.x-1; j <= p.x+1; ++j) {
            cv::Point tmp(j,i);
            if (rangeCheck(mat, tmp) && tmp != p) {
                res.push_back (tmp);
            }
        }
    }
    return res;
}


void fillCvMat (cv::Mat& mat, cv::Vec3b color) {
    assert (mat.type() == CV_8UC3);
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            mat.at<cv::Vec3b> (i,j) = color;
        }
    }
}


void flipVertical (cv::Mat& mat) {
    assert (mat.type() == CV_8UC3);
    cv::Vec3b tmp;
    for (int i = 0; i < mat.rows/2; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            tmp = mat.at<cv::Vec3b>(i,j);
            mat.at<cv::Vec3b> (i,j) = mat.at<cv::Vec3b> (mat.rows-i-1,j);
            mat.at<cv::Vec3b> (mat.rows-i-1,j) = tmp;
        }
    }
}

void flipHorizontal (cv::Mat& mat) {
    assert (mat.type() == CV_8UC3);
    cv::Vec3b tmp;
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols/2; ++j) {
            tmp = mat.at<cv::Vec3b>(i,j);
            mat.at<cv::Vec3b> (i,j) = mat.at<cv::Vec3b> (i, mat.cols-j-1);
            mat.at<cv::Vec3b> (i, mat.cols-j-1) = tmp;
        }
    }
}

double moveValue (double curValue, double minValue, double maxValue, double step) {
    assert (minValue <= maxValue);
    assert (curValue >= minValue);
    assert (curValue <= maxValue);
    double min = std::max (curValue - step, minValue);
    double max = std::min (curValue + step, maxValue);
    return RandomGenerator::randDouble(min, max);
}

bool CvPointCompareXY::operator () (const cv::Point& p1, const cv::Point& p2) const {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
