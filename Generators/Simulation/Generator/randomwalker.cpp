#include "randomwalker.h"



RandomWalker::RandomWalker(const cv::Size &size) :
    AbstractSimulation (size),
    mOutput(size, CV_8UC3)
{
    setDefault();
    start();
}


void RandomWalker::setDefault(){
    mEmptyColor = defEmptyColor();
    mPointColor = defPointColor();
    mFps = defFps();
    mSpeed = defSpeed();
    //int pointCount = defPointCount();
    //mPoints = std::vector<cv::Point> (pointCount);
    //mColors = std::vector<cv::Vec3b> (pointCount);
    setColorMode(defColorMode());
    setOverflowMode (defOverflowMode());
    setPointCount(defPointCount());
}
void RandomWalker::start(){
    //mOutput = mEmptyColor;
    fillCvMat(mOutput, mEmptyColor);
    assert (mOutput.isContinuous());
    createPoints(0, mPoints.size());
}


cv::Mat RandomWalker::getNextFrame () {
    for (int frameCount = 0; frameCount < mFps; ++frameCount) {
        for (int i = 0; i < mPoints.size(); ++i) {
            switch (mOverflowMode) {
            case eFixed:
                //mOutput.at<cv::Vec3b> (mPoints[i]) += mColors[i]*1.0*mSpeed/255;
                for (int j = 0; j < 3; ++j) {
                    int tmp = mOutput.at<cv::Vec3b> (mPoints[i])[j] + mColors[i][j]*1.0*mSpeed/255;
                    if (tmp > 255) tmp=255;
                    mOutput.at<cv::Vec3b> (mPoints[i])[j] = tmp;
                }
                break;
            case eOverflow:
                for (int j = 0; j < 3; ++j) {
                    mOutput.at<cv::Vec3b> (mPoints[i])[j] += mColors[i][j]*1.0*mSpeed/255;
                }
                break;
            case eOverwrite:
                for (int j = 0; j < 3; ++j) {
                    mOutput.at<cv::Vec3b> (mPoints[i])[j] = mColors[i][j]*1.0*mSpeed/255;
                }
                break;
            }

            int dx, dy;
            dx = rng.randInt(-1,2);
            dy = rng.randInt(-1,2);
            mPoints[i].y += dy;
            mPoints[i].x += dx;
            if (mPoints[i].y < 0 || mPoints[i].y >= mOutput.rows) {
                mPoints[i].y -= 2*dy;
            }
            if (mPoints[i].x < 0 || mPoints[i].x >= mOutput.cols) {
                mPoints[i].x -= 2*dx;
            }
        }
    }
    return mOutput.clone();
}


bool RandomWalker::hasNextFrame() {
    return true;
}
void RandomWalker::restart() {
    start();
}
void RandomWalker::resetToDefault() {
    setDefault();
}

void RandomWalker::createColors(int b, int e) {
    switch (mColorMode) {
    case eUniform:
        for (int i = b; i < e; ++i) {
            mColors[i] = mPointColor;
        }
        break;
    case eRGB:
        for (int i = b; i < e; ++i) {
            cv::Vec3b col(0,0,0);
            col[2-i%3] = 255;
            mColors[i] = col;
        }
        break;
    case eColored:
        for (int i = b; i < e; ++i) {
            mColors[i] = rng.randBrightColor();
        }
        break;
    }
}

void RandomWalker::createPoints(int b, int e) {
    createColors(b,e);
    for (int i = b; i < e; ++i) {
        mPoints[i] = rng.randPointCart();
    }
}

void RandomWalker::setOverflowMode (OverflowMode mode) {
    mOverflowMode = mode;
}

void RandomWalker::setColorMode (ColorMode mode) {
    mColorMode = mode;
    createColors(0, mColors.size());
}

void RandomWalker::setPointColor (cv::Vec3b color) {
    mPointColor = color;
    createColors(0, mColors.size());
}

void RandomWalker::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}

void RandomWalker::setPointCount(int count) {
    int oldSize = mColors.size();
    mPoints.resize(count);
    mColors.resize(count);
    if (count > oldSize) {
        createPoints(oldSize, count);
    }
}

void RandomWalker::setSpeed (int speed) {
    mSpeed = speed;
}

void RandomWalker::setFps (int fps) {
    mFps = fps;
}






RandomWalker::ColorMode RandomWalker::defColorMode () const {
    return eRGB;
}
RandomWalker::OverflowMode RandomWalker::defOverflowMode () const {
    return eOverflow;
}
cv::Vec3b RandomWalker::defPointColor () const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b RandomWalker::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
int RandomWalker::defPointCount () const {
    return 15;
}
int RandomWalker::defSpeed () const {
    return 40;
}
int RandomWalker::defFps () const {
    return 100;
}








