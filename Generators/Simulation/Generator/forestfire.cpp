#include "forestfire.h"


ForestFire::ForestFire(const cv::Size& size) :
    AbstractSimulation (size),
    mMat(size.height, size.width, EMPTY)
{
    setDefault();
    start();
}

void ForestFire::setDefault() {
    setEmptyColor(defEmptyColor());
    setTreeColor(defTreeColor());
    setFireColor(defFireColor());
    setTreeProb(defTreeProb());
    setFireProb(defFireProb());
}

void ForestFire::start () {
    mRandProbInd=0;
    mMat.fill(EMPTY);
}

cv::Mat ForestFire::getNextFrame() {
    spread ();
    ignite ();
    replant ();
    cv::Mat output(mSize, CV_8UC3);

    int* matData = mMat.data;
    cv::Vec3b* imgData = output.ptr<cv::Vec3b>();
    int max = mMat.rows*mMat.cols;
    for (int i = 0; i < max; ++i) {
        switch (matData[i]) {
        case EMPTY:
            imgData[i] = mEmptyColor;
            break;
        case TREE:
            imgData[i] = mTreeColor;
            break;
        case FIRE:
            imgData[i] = mFireColor;
            break;
        }
    }

    return output;
}

bool ForestFire::hasNextFrame() {
    return true;
}
void ForestFire::restart() {
    start();
}
void ForestFire::resetToDefault() {
    setDefault();
}


void ForestFire::spread () {
    int n = mMat.rows;
    int m = mMat.cols;
    std::vector<cv::Point> firePoints, ignitionPoints;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mMat.at(i,j) != FIRE) {
                continue;
            }
            firePoints.push_back(cv::Point (j,i));
            if (i+1 < n && mMat.at(i+1,j) == TREE) {
                ignitionPoints.push_back(cv::Point (j,i+1));
            }
            if (j+1 < m && mMat.at(i,j+1) == TREE) {
                ignitionPoints.push_back(cv::Point (j+1,i));
            }

            if (i-1 >= 0 && mMat.at(i-1,j) == TREE) {
                ignitionPoints.push_back(cv::Point (j,i-1));
            }
            if (j-1 >= 0 && mMat.at(i,j-1) == TREE) {
                ignitionPoints.push_back(cv::Point (j-1,i));
            }

            if (i+1 < n && j+1 < m && mMat.at(i+1,j+1) == TREE) {
                ignitionPoints.push_back(cv::Point (j+1,i+1));
            }
            if (i+1 < n && j-1 >= 0 && mMat.at(i+1,j-1) == TREE) {
                ignitionPoints.push_back(cv::Point (j-1,i+1));
            }
            if (i-1 >= 0 && j+1 < m && mMat.at(i-1,j+1) == TREE) {
                ignitionPoints.push_back(cv::Point (j+1,i-1));
            }
            if (i-1 >= 0 && j-1 >= 0 && mMat.at(i-1,j-1) == TREE) {
                ignitionPoints.push_back(cv::Point (j-1,i-1));
            }
        }
    }

    for (int i = 0; i < firePoints.size(); ++i) {
        mMat.at(firePoints[i]) = EMPTY;
        //mOutput.at<cv::Vec3b>(firePoints[i]) = mEmptyColor;
    }
    for (int i = 0; i < ignitionPoints.size(); ++i) {
        mMat.at(ignitionPoints[i]) = FIRE;
        //mOutput.at<cv::Vec3b>(ignitionPoints[i]) = mFireColor;
    }

}

void ForestFire::replant () {
    for (int i = 0; i < mMat.rows; ++i) {
        for (int j = 0; j < mMat.cols; ++j) {
            if (mMat.at(i,j) == EMPTY) {
                if (mRandProbInd >= mRandProb.cols) {
                    updateRandProb();
                }
                if (mRandProb.at<float>(0, mRandProbInd) < mTreeProb) {
                    mMat.at (i,j) = TREE;
                    //mOutput.at<cv::Vec3b>(i,j) = mTreeColor;
                }
                mRandProbInd++;
            }
        }
    }
}

void ForestFire::ignite () {
    for (int i = 0; i < mMat.rows; ++i) {
        for (int j = 0; j < mMat.cols; ++j) {
            if (mMat.at(i,j) == TREE) {
                if (mRandProbInd >= mRandProb.cols) {
                    updateRandProb();
                }
                if (mRandProb.at<float>(0, mRandProbInd) < mFireProb) {
                    mMat.at (i,j) = FIRE;
                    //mOutput.at<cv::Vec3b>(i,j) = mFireColor;
                }
                mRandProbInd++;
            }
        }
    }
}

void ForestFire::updateRandProb () {
    mRandProb = cv::Mat(1, mSize.height*mSize.width, CV_32F);
    cv::randu(mRandProb, 0, 1);
    mRandProbInd = 0;
}

void ForestFire::setTreeColor (cv::Vec3b color) {
    mTreeColor = color;
}

void ForestFire::setFireColor (cv::Vec3b color) {
    mFireColor = color;
}

void ForestFire::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}

void ForestFire::setTreeProb(double prob) {
    mTreeProb = prob;
}

void ForestFire::setFireProb(double prob) {
    mFireProb = prob;
}



double ForestFire::defTreeProb() const {
    return 0.01;
}
double ForestFire::defFireProb() const {
    return 0.0001;
}
cv::Vec3b ForestFire::defTreeColor() const {
    return cv::Vec3b(0,255,0);
}
cv::Vec3b ForestFire::defFireColor() const {
    return cv::Vec3b(0,0,255);
}
cv::Vec3b ForestFire::defEmptyColor() const {
    return cv::Vec3b(0,0,0);
}

