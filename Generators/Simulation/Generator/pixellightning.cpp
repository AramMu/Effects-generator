#include "pixellightning.h"
#include <opencv2/imgproc.hpp>

PixelLightning::PixelLightning(const cv::Size& size) :
    AbstractSimulation(size)
{
    setDefault();
    start();
}
void PixelLightning::setDefault() {
    setShapeMode(defShapeMode());
    setFps (defFps());
    setPointLimit (defPointLimit());
    setPointColor (defPointColor());
    setEmptyColor (defEmptyColor());
    setNeighbourMode (defNeighbourMode());
}

void PixelLightning::start() {
    mPoints.clear();
    //mQueue = std::priority_queue<PointData> ([] (const PointData& a, const PointData& b) -> bool {
    //    return a.val > b.val;
    //});
    mQueue = std::priority_queue<PointData> ();
    switch (mShapeMode) {
    case eCircle:
        mQueue.push({cv::Point (mSize.width/2, mSize.height/2), 0});
        //mPoints.push_back(cv::Point (mSize.width/2, mSize.height/2));
        break;
    case eGravity:
        for (int i = 0; i < mSize.width; ++i) {
            mQueue.push({cv::Point (i, 0), 0});
            //mPoints.push_back(cv::Point (i, 0));
        }
        break;
    }
}


cv::Mat PixelLightning::getNextFrame () {
    cv::Mat output (mSize, CV_8UC3, mEmptyColor);
    if (mPointColor == mEmptyColor) {
        return output;
    }

    for (int frame = 0; frame < mFps && mPoints.size() < mPointLimit; ++frame) {
        PointData t = mQueue.top();
        mQueue.pop();
        output.at<cv::Vec3b> (t.p) = mPointColor;
        mPoints.push_back(t.p);
        std::vector <cv::Point> neigh = getNeighbours(output, t.p);
        for (int i = 0; i < neigh.size(); ++i) {
            if (output.at<cv::Vec3b> (neigh[i]) == mPointColor) {
                continue;
            }
            mQueue.push( {neigh[i], std::pow (5, 2 - (neigh[i].y - t.p.y)) * rng.randDouble(1, 50)} );
        }
    }

    for (int i = 0; i < mPoints.size(); ++i) {
        output.at<cv::Vec3b> (mPoints[i]) = mPointColor;
    }
    cv::flip(output, output, 0);
    return output;
}
bool PixelLightning::hasNextFrame() {
    return mPoints.size() < mPointLimit;
}

void PixelLightning::restart() {
    start();
}
void PixelLightning::resetToDefault() {
    setDefault();
}

void PixelLightning::setPointColor (cv::Vec3b color) {
    mPointColor = color;
}
void PixelLightning::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}
void PixelLightning::setFps (int fps) {
    mFps = fps;
}
void PixelLightning::setPointLimit (int count) {
    mPointLimit = count;
}
void PixelLightning::setShapeMode (ShapeMode mode) {
    mShapeMode = mode;
}
void PixelLightning::setNeighbourMode (Neighbour mode) {
    mNeighbourMode = mode;
}

cv::Vec3b PixelLightning::defPointColor () const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b PixelLightning::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
int PixelLightning::defFps () const {
    return 1000;
}
int PixelLightning::defPointLimit () const {
    return 1000000;
}
PixelLightning::ShapeMode PixelLightning::defShapeMode () const {
    return eGravity;
}
PixelLightning::Neighbour PixelLightning::defNeighbourMode () const {
    return N4;
}

