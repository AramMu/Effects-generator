#ifndef UTILS_H
#define UTILS_H
//#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core/types.hpp>
double distance (const cv::Point2i& p1, const cv::Point2i& p2);
double distance (const cv::Point2d& p1, const cv::Point2d& p2);

int distanceSqr (const cv::Point2i &p1, const cv::Point2i &p2);
double distanceSqr (const cv::Point2d &p1, const cv::Point2d &p2);

int distanceChess (const cv::Point2i& p1, const cv::Point2i& p2);
double distanceChess (const cv::Point2d& p1, const cv::Point2d& p2);
int distanceCity (const cv::Point2i& p1, const cv::Point2i& p2);
double distanceCity (const cv::Point2d& p1, const cv::Point2d& p2);

bool rangeCheck (const cv::Mat& mat, const cv::Point2i& p);
bool rangeCheck (const cv::Mat& mat, const cv::Point2d& p);
bool rangeCheck (const cv::Mat& mat, int y, int x);

bool rangeCheck (const std::vector <std::vector <int> >& mat, const cv::Point2i& p);
bool rangeCheck (const std::vector <std::vector <bool> >& mat, const cv::Point2i& p);
bool rangeCheck (const std::vector <std::vector <double> >& mat, const cv::Point2i& p);

bool rangeCheck (const std::vector <std::vector <int> >& mat, const cv::Point2d& p);
bool rangeCheck (const std::vector <std::vector <bool> >& mat, const cv::Point2d& p);
bool rangeCheck (const std::vector <std::vector <double> >& mat, const cv::Point2d& p);

bool rangeCheck (const std::vector <std::vector <int> >& mat, int y, int x);
bool rangeCheck (const std::vector <std::vector <bool> >& mat, int y, int x);
bool rangeCheck (const std::vector <std::vector <double> >& mat, int y, int x);

bool valueBoundCheck (double min, double max, double val);

std::vector <cv::Point> getNeighbours (const cv::Mat& mat, const cv::Point2i& p);

void fillCvMat (cv::Mat& mat, cv::Vec3b color);

void flipVertical (cv::Mat& mat);
void flipHorizontal (cv::Mat& mat);

double moveValue (double curValue, double minValue, double maxValue, double step);

class CvPointCompareXY {
public:
    bool operator () (const cv::Point& p1, const cv::Point& p2) const;
};

#endif // UTILS_H

