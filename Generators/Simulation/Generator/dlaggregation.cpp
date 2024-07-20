#include "dlaggregation.h"
#include "Utils/calc.h"
#include <opencv2/core.hpp>
DLAggregation::DLAggregation(const cv::Size& size) :
    AbstractSimulation(size)
    //mSize(size)
{
    setDefault();
    start();
}
void DLAggregation::setDefault() {
    setFps (defFps());
    setPointLimit (defPointLimit());
    setPointColor (defPointColor());
    setEmptyColor (defEmptyColor());
    setNeighbourMode (defNeighbourMode());
    setCoordinateMode (defCoordinateMode());
    tmpShapeMode = defShapeMode();
}
void DLAggregation::start() {
    mShapeMode = tmpShapeMode;
    mPoints.clear();
    switch (mShapeMode) {
    case eCircle:
        mPoints.push_back(cv::Point (mSize.width/2, mSize.height/2));
        break;
    case eGravity:
        for (int i = 0; i < mSize.width; ++i) {
            mPoints.push_back(cv::Point (i, mSize.height-1));
        }
        break;
    }
}

cv::Point DLAggregation::nearestNeighbour (const cv::Point& p, const cv::Point n) {
    int min = mSize.height * mSize.width * 2;
    cv::Point res(-1,-1);
    for (int i = n.y-1; i <= n.y+1; ++i) {
        for (int j = n.x-1; j <= n.x+1; ++j) {
            if (i < 0 || j < 0 || i >= mSize.height || j >= mSize.width) {
                continue;
            }
            if (i==n.y && j==n.x) {
                continue;
            }
            if (mNeighbourMode == N4 && Calc::abs(i-n.y) + Calc::abs(j-n.x) >= 2) {
                continue;
            }
            cv::Point cand(j,i);
            int tmp = distanceSqr(p,cand);
            if (tmp < min) {
                min = tmp;
                res = cand;
            }
        }
    }
    return res;
}

cv::Point DLAggregation::nearest (const cv::Point& p) {
    assert (!mPoints.empty());
    int ind = 0;
    int min = distanceSqr(p, mPoints[ind]);
    for (int i = 0; i < mPoints.size(); ++i) {
        //if (p == mPoints[i]) return cv::Point(-1,-1);
        int tmp = distanceSqr(p, mPoints[i]);
        if (tmp < min) {
            min = tmp;
            ind = i;
        }
    }
    cv::Point res = mPoints[ind];
    return nearestNeighbour (p, res);
}

cv::Mat DLAggregation::getNextFrame () {
    cv::Mat output (mSize, CV_8UC3, mEmptyColor);
    if (mPointColor == mEmptyColor) {
        return output;
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        output.at<cv::Vec3b> (mPoints[i]) = mPointColor;
    }

    for (int frame = 0; frame < mFps && mPoints.size() < mPointLimit; ++frame) {
        cv::Point p;
        switch (mCoordinateMode) {
        case ePolar:
            p = rng.randPointPolar();
            break;
        case eCart:
            p = rng.randPointCart();
            break;
        }
        if (output.at<cv::Vec3b> (p) == mPointColor) {
            frame--;
            continue;
        }

        cv::Point q = nearest (p);
        if (q.x < 0) {
            frame--;
            continue;
        }
        mPoints.push_back(q);
    }
    return output;
}
bool DLAggregation::hasNextFrame() {
    return mPoints.size() < mPointLimit;
}

void DLAggregation::restart() {
    start();
}
void DLAggregation::resetToDefault() {
    setDefault();
}

void DLAggregation::setPointColor (cv::Vec3b color) {
    mPointColor = color;
}
void DLAggregation::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}
void DLAggregation::setFps (int fps) {
    mFps = fps;
}
void DLAggregation::setPointLimit (int count) {
    mPointLimit = count;
}
void DLAggregation::setShapeMode (ShapeMode mode) {
    tmpShapeMode = mode;
}
void DLAggregation::setNeighbourMode (Neighbour mode) {
    mNeighbourMode = mode;
}
void DLAggregation::setCoordinateMode (CoordinateMode mode) {
    mCoordinateMode = mode;
}

cv::Vec3b DLAggregation::defPointColor () const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b DLAggregation::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
int DLAggregation::defFps () const {
    return 100;
}
int DLAggregation::defPointLimit () const {
    return 10000;
}
DLAggregation::ShapeMode DLAggregation::defShapeMode () const {
    return eCircle;
}
DLAggregation::Neighbour DLAggregation::defNeighbourMode () const {
    return N4;
}
DLAggregation::CoordinateMode DLAggregation::defCoordinateMode () const {
    return eCart;
}
