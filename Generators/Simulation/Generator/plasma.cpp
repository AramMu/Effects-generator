#include "plasma.h"


Plasma::Plasma(const cv::Size &size) :
    AbstractSimulation (size),
    mOutput (size, CV_8UC3, mEmptyColor),
    mUsed (size, false)
{
    setDefault();
    start();
}

void Plasma::setDefault() {
    setUsedColor(defUsedColor());
    setEmptyColor(defEmptyColor());
    setBranchProb(defBranchProb());
}

void Plasma::start() {
    mConsumed=true;
}

cv::Mat Plasma::getNextFrame() {
    mUsed.fill(false);
    for (int i = 0; i < mUsed.cols; ++i) {
        mUsed.at(mUsed.rows-1, i) = true;
    }
    for (int i = mUsed.rows-1; i >= 1; --i) {
        for (int j = 0; j < mUsed.cols; ++j) {
            if (!mUsed.at(i,j)) continue;
            int ind;
            if (j==0) {
                ind=rng.randInt(0,2);
            } else if (j == mUsed.cols-1) {
                ind=rng.randInt(mUsed.cols-2,mUsed.cols);
            } else {
                double p = rng.randProb();
                if (p < mBranchProb) {
                    mUsed.at(i-1, j-1) = true;
                    mUsed.at(i-1, j+1) = true;
                    continue;
                }
                ind=rng.randInt(j-1, j+2);
            }
            assert (i >= 0 && i < mUsed.rows);
            assert (j >= 0 && j < mUsed.cols);
            mUsed.at(i-1, ind) = true;
        }
    }

    mOutput = mEmptyColor;
    for (int i = 0; i < mOutput.rows; ++i) {
        for (int j = 0; j < mOutput.cols; ++j) {
            mOutput.at<cv::Vec3b> (i,j) = mUsed.at(i,j) ? mUsedColor : mEmptyColor;
        }
    }
    mConsumed = false;
    return mOutput.clone();
}

bool Plasma::hasNextFrame() {
    return mConsumed;
}
void Plasma::restart() {
    start();
}
void Plasma::resetToDefault() {
    setDefault();
}

void Plasma::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}
void Plasma::setUsedColor (cv::Vec3b color) {
    mUsedColor = color;
}
void Plasma::setBranchProb (double prob) {
    mBranchProb = prob;
}

cv::Vec3b Plasma::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
cv::Vec3b Plasma::defUsedColor () const {
    return cv::Vec3b(255,255,255);
}
double Plasma::defBranchProb () const {
    return 0.05;
}

