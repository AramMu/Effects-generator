#include "smoke.h"
#include <opencv2/imgproc.hpp>

Smoke::Smoke(const cv::Size& size) :
    AbstractSimulation(size)
    //mSize(size)
    //mMat(size, CV_8UC3)
{
    setDefault();
    start();
}

void Smoke::setDefault() {
    setEmptyColor(defEmptyColor());
    setSmokeColor(defSmokeColor());
    setSmokeProb(defSmokeProb());
    setColorMode(defColorMode());
    setScaleX(defScaleX());
    setScaleY(defScaleY());
}

void Smoke::start() {
    mMat = cv::Mat (mSize.height / mScaleY, mSize.width / mScaleX, CV_8UC3, mEmptyColor);
    generateButtom();
}


cv::Mat Smoke::getNextFrame () {
    for (int i = 0; i < mMat.rows-1; ++i) {
        for (int j = 0; j < mMat.cols; ++j) {
            mMat.at<cv::Vec3b> (i, j) = calcSum4 (i, j);
        }
    }
    generateButtom();
    cv::Mat output;
    cv::resize(mMat, output, mSize);
    return output;
}

bool Smoke::hasNextFrame() {
    return true;
}

void Smoke::resetToDefault() {
    setDefault();
}
void Smoke::restart() {
    start();
}

cv::Vec3b Smoke::calcSum3 (int y, int x) {
    cv::Vec3i sum(0,0,0);
    int k = 0;
    for (int i = x-1; i <= x+1; ++i) {
        if (i < 0 || i >= mMat.cols) {
            continue;
        }
        k++;
        sum += mMat.at<cv::Vec3b>(y+1, i);
    }
    return sum / k;
}

cv::Vec3b Smoke::calcSum4 (int y, int x) {
    cv::Vec3i sum = mMat.at<cv::Vec3b>(y,x);
    int k = 1;
    for (int i = x-1; i <= x+1; ++i) {
        if (i < 0 || i >= mMat.cols) {
            continue;
        }
        k++;
        sum += mMat.at<cv::Vec3b>(y+1, i);
    }
    return sum / k;
}
void Smoke::generateButtom() {
    for (int i = 0; i < mMat.cols; ++i) {
        double p = rng.randProb();
        cv::Vec3b color;
        if (p >= mSmokeProb) {
            color = mEmptyColor;
        } else {
            switch (mColorMode) {
            case eUniform:
                color = mSmokeColor;
                break;
            case eColored:
                color = rng.randBrightColor();
                break;
            case eRGB:
            {
                int val = rng.randInt(0,3);
                color = cv::Vec3b(0,0,0);
                color[val] = 255;
            }
                break;
            }
        }
        mMat.at<cv::Vec3b> (mMat.rows-1, i) = color;
    }
}

void Smoke::setSmokeColor (cv::Vec3b color) {
    mSmokeColor = color;
}
void Smoke::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}
void Smoke::setSmokeProb (double prob) {
    mSmokeProb = prob;
}
void Smoke::setColorMode (ColorMode mode) {
    mColorMode = mode;
}
void Smoke::setScaleX (double scale) {
    mScaleX = scale;
}
void Smoke::setScaleY (double scale) {
    mScaleY = scale;
}

cv::Vec3b Smoke::defSmokeColor () {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b Smoke::defEmptyColor () {
    return cv::Vec3b(0,0,0);
}
double Smoke::defSmokeProb () {
    return 0.6;
}
Smoke::ColorMode Smoke::defColorMode () {
    return eUniform;
}
double Smoke::defScaleX () {
    return 1.0;
}
double Smoke::defScaleY () {
    return 1.0;
}



