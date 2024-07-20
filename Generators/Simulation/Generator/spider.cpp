#include "spider.h"

#include <algorithm>
//#include <queue>
#include <set>
//#include "Time/timemeasure.h"
#include "Algorithms/convexhull.h"
#include <opencv2/imgproc.hpp>

Spider::Spider(const cv::Size& size) :
    AbstractSimulation (size),
    mOutput(size, CV_8UC3)
{
    setDefault();
}

void Spider::setDefault(){
    mPointCount = defPointCount();
    setLineThick(defLineThick());
    mEmptyColor = defEmptyColor();
    mPointColor = defPointColor();
    mLineColor = defLineColor();
    start();
}
void Spider::start(){
    mConsumed = false;
    mPoints = std::vector<cv::Point>(mPointCount);

    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i] = cv::Point2i (rng.randX(), rng.randY());
    }
    std::sort (mPoints.begin(), mPoints.end(), CvPointCompareXY());
}


cv::Mat Spider::getNextFrame() {
    mConsumed = true;
    mOutput = mEmptyColor;
    assert (mOutput.isContinuous());
    std::vector <cv::Point> points = mPoints;
    std::vector <cv::Point> prev;
    while (!points.empty()) {
        std::vector <cv::Point> hull = convexHull(points);
        std::set<cv::Point, CvPointCompareXY> hullSet;
        for (int i = 0; i < hull.size(); ++i) {
            hullSet.insert (hull[i]);
        }
        std::vector <cv::Point> replace;
        for (int i = 0; i < points.size(); ++i) {
            if (!hullSet.count(points[i]) >= 1) {
                replace.push_back(points[i]);
            }
        }
/*
        for (int i = 0; i < hull.size(); ++i) {
            cv::line(mOutput, hull[i], hull[(i+1)%hull.size()], mLineColor, 1);
            if (prev.empty()) continue;
            int ind = 0;
            for (int j = 1; j < prev.size(); ++j) {
                if (distanceSqr(hull[i], prev[j]) < distanceSqr(hull[i], prev[ind])) {
                    ind = j;
                }
            }
            cv::line(mOutput, hull[i], prev[ind], mLineColor, 1);
        }
*/


        for (int i = 0; i < hull.size(); ++i) {
            cv::line(mOutput, hull[i], hull[(i+1)%hull.size()], mLineColor, 1);
        }
        if (hull.empty()) continue;

        for (int i = 0; i < prev.size(); ++i) {
            int ind = 0;
            for (int j = 1; j < hull.size(); ++j) {
                if (distanceSqr(hull[j], prev[i]) < distanceSqr(hull[ind], prev[i])) {
                    ind = j;
                }
            }
            cv::line(mOutput, hull[ind], prev[i], mLineColor, 1);
        }


        prev = hull;
        points = replace;
    }

    return mOutput.clone();
}

bool Spider::hasNextFrame() {
    return !mConsumed;
}
void Spider::restart() {
    start();
}
void Spider::resetToDefault() {
    setDefault();
}

void Spider::setPointCount (int count){
    mPointCount = count;
}
void Spider::setPointColor (cv::Vec3b color){
    mPointColor = color;
}
void Spider::setLineColor (cv::Vec3b color){
    mLineColor = color;
}
void Spider::setEmptyColor (cv::Vec3b color){
    mEmptyColor = color;
}


int Spider::defPointCount () const {
    return 100;
}
cv::Vec3b Spider::defPointColor () const {
    return cv::Vec3b(255,255,0);
}
cv::Vec3b Spider::defLineColor () const {
   return cv::Vec3b(0,0,255);
}
cv::Vec3b Spider::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}

void Spider::setLineThick (int thick) {
    mLineThick = thick;
}

int Spider::defLineThick () const {
    return 1;
}
