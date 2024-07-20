#include "mstree.h"
#include <algorithm>
#include <opencv2/imgproc.hpp>
//#include <queue>
//#include "Time/timemeasure.h"

MSTree::MSTree(const cv::Size& size) :
    AbstractSimulation (size),
    mOutput(size, CV_8UC3)
{
    setDefault();
}

void MSTree::setDefault(){
    mPointCount = defPointCount();
    setLineThick(defLineThick());
    setPointThick(defPointThick());
    mEmptyColor = defEmptyColor();
    mPointColor = defPointColor();
    mLineColor = defLineColor();

    setDistanceMode(defDistanceMode());
    mFps = defFps();
    start();
}
void MSTree::start(){
    mDisjoint = DisjointSet(mPointCount);
    mRemaining = mPointCount - 1;
    mPoints = std::vector<cv::Point>(mPointCount);
    EdgeListW edgeList( (mPoints.size() * (mPoints.size()-1) ) / 2);

    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i] = cv::Point2i (rng.randX(), rng.randY());
    }
    int pos = 0;

    for (int i = 0; i < mPoints.size(); ++i) {
        for (int j = i+1; j < mPoints.size(); ++j) {
            edgeList[pos] = ( Edge3W(i,j,distance (mPoints[i], mPoints[j])));
            pos++;
        }
    }

    if (mDistanceMode == eShort) {
        mPriorityQueue = std::priority_queue<Edge3W, std::vector<Edge3W>, Edge3W::Comparator>
                (edgeList.begin(), edgeList.end(), Edge3W::Comparator(true));
    } else {
        mPriorityQueue = std::priority_queue<Edge3W, std::vector<Edge3W>, Edge3W::Comparator>
                (edgeList.begin(), edgeList.end(), Edge3W::Comparator(false));
    }
    mOutput = mEmptyColor;
    assert (mOutput.isContinuous());
    for (int i = 0; i < mPoints.size(); ++i) {
        mOutput.at<cv::Vec3b> (mPoints[i]) = mPointColor;
    }
}


cv::Mat MSTree::getNextFrame() {
    for (int frameCount = 0; frameCount < mFps && mRemaining > 0; ++frameCount) {
        assert (!mPriorityQueue.empty());
        Edge3W e = mPriorityQueue.top();
        mPriorityQueue.pop();
        if (mDisjoint.merge(e.u, e.v)) {
            cv::line (mOutput, mPoints[e.u], mPoints[e.v], mLineColor, mLineThick);
            cv::circle(mOutput, mPoints[e.u], mPointThick, mPointColor, -1);
            cv::circle(mOutput, mPoints[e.v], mPointThick, mPointColor, -1);

            //mOutput.at <cv::Vec3b> (mPoints[e.u]) = mPointColor;
            //mOutput.at <cv::Vec3b> (mPoints[e.v]) = mPointColor;
            --mRemaining;
        } else {
            --frameCount;
        }
    }

    return mOutput.clone();
}

bool MSTree::hasNextFrame() {
    return mRemaining > 0;
    //return !mPriorityQueue.empty();
}
void MSTree::restart() {
    start();
}
void MSTree::resetToDefault() {
    setDefault();
}

void MSTree::setDistanceMode (DistanceMode mode) {
    mDistanceMode = mode;
}
void MSTree::setPointCount (int count){
    mPointCount = count;
}
void MSTree::setPointColor (cv::Vec3b color){
    mPointColor = color;
}
void MSTree::setLineColor (cv::Vec3b color){
    mLineColor = color;
}
void MSTree::setEmptyColor (cv::Vec3b color){
    mEmptyColor = color;
}
void MSTree::setFps (int fps) {
    mFps = fps;
}




MSTree::DistanceMode MSTree::defDistanceMode () const {
    return eShort;
}
int MSTree::defPointCount () const {
    return 500;
}
cv::Vec3b MSTree::defPointColor () const {
    return cv::Vec3b(255,255,0);
}
cv::Vec3b MSTree::defLineColor () const {
   return cv::Vec3b(0,0,255);
}
cv::Vec3b MSTree::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
int MSTree::defFps () const {
    return 10;
}

void MSTree::setLineThick (int thick) {
    mLineThick = thick;
}
int MSTree::defLineThick () const {
    return 1;
}

void MSTree::setPointThick (int thick) {
    mPointThick = thick;
}
int MSTree::defPointThick () const {
    return 0;
}




