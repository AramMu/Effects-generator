#include "voronoidiagram.h"
#include <opencv2/imgproc.hpp>
#include "Utils/calc.h"

VoronoiDiagram::VoronoiDiagram(const cv::Size &size) :
    AbstractSimulation(size),
    mMat (size)
{
    setDefault();
    start();
}

void VoronoiDiagram::setDefault() {
    mEmptyColor = defEmptyColor();
    mLineColor = defLineColor();
    mPointColor = defPointColor();
    setDistanceMode(defDistanceMode());
    mPointCount = defPointCount();
}

void VoronoiDiagram::start () {
    mConsumed = false;
    mPoints = std::vector<cv::Point> (mPointCount);
    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i] = cv::Point (rng.randX(), rng.randY());
    }
}


int VoronoiDiagram::getDistance (const cv::Point& p1, const cv::Point& p2) {
    int tmp;
    switch (mDistanceMode) {
    case eEuclid:
        tmp = distanceSqr(p1, p2);
        break;
    case eCity:
        tmp = distanceCity(p1, p2);
        break;
    case eChess:
        tmp = distanceChess(p1, p2);
        break;
    }
    return tmp;
}

cv::Mat VoronoiDiagram::getNextFrame() {
    start();
    mMat.fill(-1);
    std::vector<int> maxDist(mPointCount, 1);
    for (int i = 0; i < mMat.rows; ++i) {
        for (int j = 0; j < mMat.cols; ++j) {
            int min=INF;

            for (int k = 0; k < mPoints.size(); ++k) {
                int tmp = getDistance(cv::Point (j, i), mPoints[k]);
                if (tmp < min) {
                    min = tmp;
                    mMat.at(i,j) = k;
                }
            }
            maxDist [mMat.at(i,j)] = std::max (maxDist [mMat.at(i,j)], getDistance(cv::Point (j, i), mPoints[mMat.at(i,j)]));
        }
    }
    cv::Mat output (mMat.rows, mMat.cols, CV_8UC3, mEmptyColor);
    assert (output.isContinuous());

    for (int i = 0; i < mMat.rows; ++i) {
        for (int j = 0; j < mMat.cols; ++j) {
            if (isEdge (cv::Point (j,i))) {
                output.at <cv::Vec3b> (i,j) = mLineColor;
            }
        }
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        cv::circle(output,  mPoints[i], 2, mPointColor,-1);
    }
    mConsumed = true;
    return output;
}


bool VoronoiDiagram::hasNextFrame() {
    return !mConsumed;
}
void VoronoiDiagram::restart() {
    start();
}
void VoronoiDiagram::resetToDefault() {
    setDefault();
}


bool VoronoiDiagram::isEdge (const cv::Point& p) {
    for (int i = p.y-1; i <= p.y+1; ++i) {
        for (int j = p.x-1; j <= p.x+1; ++j) {
            if (i < 0 || j < 0 || i >= mMat.rows || j >= mMat.cols) {
                continue;
            }
            if (mMat.at(i,j) != mMat.at(p.y, p.x)) {
                return true;
            }
        }
    }
    return false;
}

void VoronoiDiagram::setDistanceMode (DistanceMode mode) {
    mDistanceMode = mode;
}

void VoronoiDiagram::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}
void VoronoiDiagram::setPointColor (cv::Vec3b color) {
    mPointColor = color;
}
void VoronoiDiagram::setLineColor (cv::Vec3b color) {
    mLineColor = color;
}
void VoronoiDiagram::setPointCount (int count) {
    mPointCount = count;
}


VoronoiDiagram::DistanceMode VoronoiDiagram::defDistanceMode () const {
    return eEuclid;
}
cv::Vec3b VoronoiDiagram::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
cv::Vec3b VoronoiDiagram::defPointColor () const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b VoronoiDiagram::defLineColor () const {
    return cv::Vec3b (0,0,255);
}
int VoronoiDiagram::defPointCount () const {
    return 30;
}

