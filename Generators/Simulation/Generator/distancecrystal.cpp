#include "distancecrystal.h"
//#include "Utils/utils.h"
#include "utils/calc.h"
#include <opencv2/imgproc.hpp>

DistanceCrystal::DistanceCrystal(const cv::Size &size) :
    AbstractSimulation(size),
    mOutput (size, CV_8UC3)
{
    setDefault();
    start();
}


void DistanceCrystal::setDefault() {
    mPointCount = defPointCount();
    mSiteCount = defSiteCount();

    mEmptyColor = defEmptyColor();
    mLineColor = defLineColor();
    mFps = defFps();
    setStartMode(defStartMode());
    setColorMode(defColorMode());
}

void DistanceCrystal::start() {
    mOutput = mEmptyColor;
    assert (mOutput.isContinuous());
    mPoints = std::vector<PointIndex> (mPointCount);
    switch (mStartMode) {
    case eCenter:
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i].p = rng.randPointPolar();
        }
        break;
    default:
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i].p = rng.randPointCart();
            //mPoints[i].p = cv::Point (rng.randX(), rng.randY());
        }
        break;
    }
    switch (mStartMode) {
    case eCenter:
        mSites.clear();
        mSites.push_back(cv::Point(mOutput.cols/2, mOutput.rows/2));
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i].dist = distanceSqr(mPoints[i].p, mSites[0]);
            mPoints[i].index = 0;
        }
        break;
    case eButtom:
        mSites = std::vector<cv::Point>(mOutput.cols);
        for (int i = 0; i < mSites.size(); ++i) {
            mSites[i] = cv::Point (i, mOutput.rows-1);
        }
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i].dist = mOutput.rows-1 - mPoints[i].p.y;
            mPoints[i].index = mPoints[i].p.x;
        }
        break;
    case eRandom:
        mSites = std::vector <cv::Point> (mSiteCount);
        for (int i = 0; i < mSites.size(); ++i) {
            mSites[i] = rng.randPointCart();
        }
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i].dist = INF;
            mPoints[i].index = -1;
            for (int j = 0; j < mSites.size(); ++j) {
                double tmp = distanceSqr(mPoints[i].p, mSites[j]);
                if (tmp < mPoints[i].dist) {
                    mPoints[i].dist = tmp;
                    mPoints[i].index = j;
                }
            }
        }
        break;
    }
    std::sort (mPoints.begin(), mPoints.end(), PointIndex::CompareGreater());
    //std::reverse (mPoints.begin(), mPoints.end());
}



cv::Mat DistanceCrystal::getNextFrame() {
    for (int frame = 0; frame < mFps && !mPoints.empty(); ++frame) {
        switch (mColorMode) {
        case eUniform:
            cv::line(mOutput, mPoints.back().p, mSites [ mPoints.back().index], mLineColor, 1);
            break;
        case eColored:
            cv::line(mOutput, mPoints.back().p, mSites [ mPoints.back().index], rng.randBrightColor(), 1);
            break;
        case eRGB:
        {
            cv::Vec3b color(0,0,0);
            color [rng.randInt(0,3)] = 255;
            //color[2 - mPointPos%3] = 255;
            cv::line(mOutput, mPoints.back().p, mSites [ mPoints.back().index], color, 1);
        }
            break;
        }
        mPoints.pop_back();
    }
    return mOutput.clone();
}



bool DistanceCrystal::hasNextFrame() {
    return !mPoints.empty();
}

void DistanceCrystal::restart() {
    start();
}
void DistanceCrystal::resetToDefault() {
    setDefault();
}

void DistanceCrystal::setStartMode (StartMode mode) {
    mStartMode = mode;
}
void DistanceCrystal::setColorMode (ColorMode mode) {
    mColorMode = mode;
}
void DistanceCrystal::setLineColor (cv::Vec3b color) {
    mLineColor = color;
}
void DistanceCrystal::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}
void DistanceCrystal::setFps (int fps) {
    mFps = fps;
}
void DistanceCrystal::setPointCount (int count) {
    mPointCount = count;
}
void DistanceCrystal::setSiteCount (int count) {
    mSiteCount = count;
}

DistanceCrystal::StartMode DistanceCrystal::defStartMode () const {
    return eRandom;
}
DistanceCrystal::ColorMode DistanceCrystal::defColorMode () const {
    return eUniform;
}
cv::Vec3b DistanceCrystal::defLineColor () const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b DistanceCrystal::defEmptyColor () const {
   return cv::Vec3b(0,0,0);
}
int DistanceCrystal::defFps () const {
    return 10;
}
int DistanceCrystal::defPointCount () const {
    return 1000;
}
int DistanceCrystal::defSiteCount () const {
    return 20;
}

int DistanceCrystal::minFps () const {
    return 0;
}
int DistanceCrystal::maxFps () const {
    return 10;
}
int DistanceCrystal::stepFps () const {
    return 1;
}
int DistanceCrystal::minPointCount () const {
    return 1;
}
int DistanceCrystal::maxPointCount () const {
    return 1000;
}
int DistanceCrystal::stepPointCount () const {
    return 100;
}
int DistanceCrystal::minSiteCount () const {
    return 1;
}
int DistanceCrystal::maxSiteCount () const {
    return 30;
}
int DistanceCrystal::stepSiteCount () const {
    return 1;
}
