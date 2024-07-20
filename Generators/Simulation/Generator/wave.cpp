#include "wave.h"
#include <queue>
#include <opencv2/core.hpp>

Wave::Wave(const cv::Size& size) :
    AbstractSimulation (size),
    mMat(size)
{
    setDefault();
    start();
}

void Wave::setDefault() {
    setEmptyColor(defEmptyColor());
    setStoneColor(defStoneColor());
    setWaterColor(defWaterColor());
    setStoneProb(defStoneProb());
}

void Wave::start () {}

cv::Mat Wave::getNextFrame() {
    mMat.fill(EMPTY);
    createStones ();
    flowWater ();

    cv::Mat output(mMat.size(), CV_8UC3);
    for (int i = 0; i < output.rows; ++i) {
        for (int j = 0; j < output.cols; ++j) {
            switch (mMat.at(i,j)) {
            case EMPTY:
                output.at<cv::Vec3b>(i,j) = mEmptyColor;
                break;
            case STONE:
                output.at<cv::Vec3b>(i,j) = mStoneColor;
                break;
            case WATER:
                output.at<cv::Vec3b>(i,j) = mWaterColor;
                break;
            }
        }
    }
    return output;
}

bool Wave::hasNextFrame() {
    return true;
}
void Wave::restart() {
    start();
}
void Wave::resetToDefault() {
    setDefault();
}


void Wave::flowWater () {
    int n = mMat.rows;
    int m = mMat.cols;
    std::queue<cv::Point> q;
    for (int i = 0; i < m; ++i) {
        if (mMat.at(n-1, i) == EMPTY) {
            q.push(cv::Point(i, n-1));
            mMat.at(n-1, i) = WATER;
        }
    }

    while (!q.empty()) {
        cv::Point t = q.front();
        q.pop();
        for (int i = t.y-1; i <= t.y+1; ++i) {
            for (int j = t.x-1; j <= t.x+1; ++j) {
                cv::Point p(j,i);
                if (p == t || p.x < 0 || p.y < 0 || p.x >= m || p.y >= n) {
                    continue;
                }
                if (mMat.at(p) == EMPTY) {
                    mMat.at(p) = WATER;
                    q.push(p);
                }
            }
        }
    }
}

void Wave::createStones () {
    for (int i = 0; i < mMat.rows; ++i) {
        for (int j = 0; j < mMat.cols; ++j) {
            if (mMat.at(i,j) == EMPTY) {
                double r = rng.randProb();
                if (r < mStoneProb) {
                    mMat.at (i,j) = STONE;
                }
            }
        }
    }
}


void Wave::setStoneColor (cv::Vec3b color) {
    mStoneColor = color;
}
void Wave::setWaterColor (cv::Vec3b color) {
    mWaterColor = color;
}
void Wave::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}
void Wave::setStoneProb(double prob) {
    mStoneProb = prob;
}

double Wave::defStoneProb() const {
    return 0.6;
}
cv::Vec3b Wave::defStoneColor() const {
    return cv::Vec3b(0,0,0);
}
cv::Vec3b Wave::defWaterColor() const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b Wave::defEmptyColor() const {
    return cv::Vec3b(0,0,0);
}
