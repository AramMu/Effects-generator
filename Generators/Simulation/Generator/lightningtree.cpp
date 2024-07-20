#include "lightningtree.h"
#include <opencv2/imgproc.hpp>
#include "Utils/calc.h"
//#include "Time/timemeasure.h"

LightningTree::LightningTree(const cv::Size& size) :
    AbstractSimulation (size),
    //mSize(size),
    mOutput(size, CV_8UC3)
{
    setDefault();
}

void LightningTree::setDefault() {
    setPointCount(defPointCount());
    setEmptyColor (defEmptyColor());
    setLineColor (defLineColor());
    setLineThickness (defLineThickness());
    setPower(defPower());
    setLightFrames(defLightFrames());
    setEmptyFrames(defEmptyFrames());
    setStrikeProb(defStrikeProb());
    start();
}
void LightningTree::start() {
    mFrameCount = 0;
    //createPoints();
}

void LightningTree::createPoints() {
    mReachedButtom = false;
    mPoints = std::vector<cv::Point2i>(mPointCount + 1 + mSize.width);
    mRemaining = mPoints.size() - 1;
    mUsed = std::vector<bool> (mPoints.size(), false);
    mPoints[0] = cv::Point2i (mSize.width/2, 0);
    for (int i = 0; i < mSize.width; ++i) {
        mPoints[i+1] = cv::Point2i (i, mSize.height-1);
    }

    for (int i = 1+mSize.width; i < mPoints.size(); ++i) {
        mPoints[i] = cv::Point2i (rng.randX(), rng.randY());
    }

    mPriorityQueue = std::priority_queue<Edge3W, std::vector<Edge3W>, Edge3W::Comparator>
            (Edge3W::Comparator(true));

    mPriorityQueue.push (Edge3W(0,0,0));
}



cv::Mat LightningTree::getNextFrame() {
    assert (mOutput.isContinuous());

    if (mFrameCount < mLightFrames) {
        if (mFrameCount == 0) {
            bool isStrike = rng.randProb() < mStrikeProb;
            mOutput = mEmptyColor;

            createPoints();

            for (; mRemaining > 0 && !mReachedButtom;) {
                assert (!mPriorityQueue.empty());
                Edge3W e = mPriorityQueue.top();
                mPriorityQueue.pop();
                if (!mUsed[e.v]) {
                    mUsed[e.v] = true;

                    if (isStrike) {
                        cv::line (mOutput, mPoints[e.u], mPoints[e.v], mLineColor, std::min(mSize.width, mSize.height)/15);
                    } else {
                        cv::line (mOutput, mPoints[e.u], mPoints[e.v], mLineColor, mLineThick);
                    }
                    --mRemaining;
                    if (e.v > 0 && e.v <= mOutput.cols) {
                        mReachedButtom = true;
                        continue;
                    }
                    for (int i = 0; i < mPoints.size(); ++i) {
                        if (mUsed[i]) {
                            continue;
                        }
                        mPriorityQueue.push (Edge3W (e.v, i,
                                                     elecDistance (mPoints[e.v], mPoints[i])));
                    }
                }
            }

            if (isStrike) {
                /*
                for (int i = 0; i < mOutput.rows; ++i) {
                    for (int j = 0; j < mOutput.cols; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            mOutput.at<cv::Vec3b>(i,j)[k] = 255 - mOutput.at<cv::Vec3b>(i,j)[k];
                        }
                    }
                }
                */
                mOutput = ~mOutput;
            }
        }
    } else {
        mOutput = mEmptyColor;
    }
    mFrameCount++;
    mFrameCount %= mLightFrames + mEmptyFrames;
    return mOutput.clone();
}

bool LightningTree::hasNextFrame() {
    return true;
}
void LightningTree::restart() {
    start();
}
void LightningTree::resetToDefault() {
    setDefault();
}

double LightningTree::angleY (cv::Point p1, cv::Point p2) {
    double y = p2.y - p1.y;
    double x = p2.x - p1.x;
    return Calc::abs(std::atan2(x,y));
}

double LightningTree::elecDistance(const cv::Point& p1, const cv::Point& p2) {
    double ang = angleY(p1,p2);
    double dist = distance(p1, p2);
    return dist * std::exp (ang*mPower);
}


void LightningTree::setPointCount (int count){
    mPointCount = count;
}
void LightningTree::setLineColor (cv::Vec3b color){
    mLineColor = color;
}
void LightningTree::setEmptyColor (cv::Vec3b color){
    mEmptyColor = color;
}
void LightningTree::setLineThickness (int thick) {
    mLineThick = thick;
}
void LightningTree::setPower (double power) {
    mPower = power;
}
void LightningTree::setLightFrames (int frames) {
    mLightFrames = frames;
}
void LightningTree::setEmptyFrames (int frames) {
    mEmptyFrames = frames;
}
void LightningTree::setStrikeProb(double prob) {
    mStrikeProb = prob;
}


int LightningTree::defPointCount () const {
    return 1000;
}
cv::Vec3b LightningTree::defLineColor () const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b LightningTree::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
int LightningTree::defLineThickness () const {
    return 1;
}
double LightningTree::defPower () const {
    return 0.6;
}
int LightningTree::defLightFrames () const {
    return 3;
}
int LightningTree::defEmptyFrames () const {
    return 20;
}
double LightningTree::defStrikeProb() const {
    return 0.1;
}
