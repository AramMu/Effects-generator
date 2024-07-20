#include "magnet.h"


Magnet::Magnet (const cv::Size& size) :
    AbstractSimulation (size),
    mOutput(cv::Mat (size, CV_8UC3))
{
    setDefault();
    start ();
}

void Magnet::setDefault(){
    tmpShapeMode = defShapeMode();
    //setShapeMode(tmpShapeMode);
    setNeighbourMode(defNeighbourMode());
    mPointColor = defPointColor();
    mEmptyColor = defEmptyColor();
    mFps = defFps();
    mPointLimit = defPointLimit();
}
void Magnet::start(){
    mPointCount = 0;
    mShapeMode = tmpShapeMode;
    //setShapeMode(tmpShapeMode);
    mOutput = mEmptyColor;
    //fillCvMat(mOutput, mEmptyColor);
    assert (mOutput.isContinuous());
    switch (mShapeMode) {
    case eGravity:// case ePyramid:
        for (int i = 0; i < mOutput.cols; ++i) {
            mOutput.at <cv::Vec3b> (mOutput.rows-1,i) = mPointColor;
        }
        mPointCount = mOutput.cols;
        break;
    default:
        //mOutput.at <cv::Vec3b> (mOutput.rows/2, mOutput.cols/2) = mPointColor;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                //if (Calc::abs(i) + Calc::abs(j) >= 2) {
                //    continue;
                //}
                mOutput.at <cv::Vec3b> (mOutput.rows/2+i, mOutput.cols/2+j) = mPointColor;
            }
        }
        mPointCount = 9;
        break;
    }
}

cv::Mat Magnet::getNextFrame() {
    if (mEmptyColor == mPointColor) {
        return mOutput;
    }
    for (int frame = 0; mPointCount < mPointLimit && frame < mFps; ++frame, ++mPointCount) {
        cv::Point2d p;
        switch (mShapeMode) {
        case eCircle:
            p = rng.randPointPolarD();
            break;
        default:
            p = rng.randPointCartD();
            break;
        }
        //std::cout << p.x << " " << p.y << std::endl;
        assert (int(p.y)>=0 && int(p.x)>=0);
        assert (int(p.y) < mOutput.rows && int(p.x) < mOutput.cols);
        if (mOutput.at<cv::Vec3b> (int(p.y), int(p.x)) != mEmptyColor) {
            mPointCount--;
            frame--;
            continue;
        }
        while (!check (p)) {
            //std::cout << p.x << " " << p.y << std::endl;
            switch (mShapeMode) {
            case eCross:
            {
                p = moveCross(p);
                break;
            }
            case eCircle: case eSquare:
            {
                p = moveCircle(p);
                break;
            }
            case eGravity:// case ePyramid:
            {
                p = moveGravity(p);
                break;
            }
            }
        }
        //std::cout << "reached" << std::endl;
        mOutput.at <cv::Vec3b> (int(p.y), int(p.x)) = mPointColor;
    }
    return mOutput.clone();
}



bool Magnet::hasNextFrame() {
    return mPointCount < mPointLimit;
}
void Magnet::restart() {
    start();
}
void Magnet::resetToDefault() {
    setDefault();
}






bool Magnet::check (const cv::Point2d& p) {
    int x=(int)p.x, y=(int)p.y;
    bool res =
            (x-1 >= 0 && mOutput.at <cv::Vec3b> (y,x-1) != mEmptyColor) ||
            (y-1 >= 0 && mOutput.at <cv::Vec3b> (y-1,x) != mEmptyColor) ||
            (x+1 < mOutput.cols && mOutput.at <cv::Vec3b> (y,x+1) != mEmptyColor) ||
            (y+1 < mOutput.rows && mOutput.at <cv::Vec3b> (y+1,x) != mEmptyColor);
    if (mNeighbourMode == N8) {
        res = res ||
                (x-1 >= 0 && y-1 >= 0 && mOutput.at <cv::Vec3b> (y-1,x-1) != mEmptyColor) ||
                (x-1 >= 0 && y+1 < mOutput.rows && mOutput.at <cv::Vec3b> (y+1,x-1) != mEmptyColor) ||
                (x+1 < mOutput.cols && y-1 >= 0 && mOutput.at <cv::Vec3b> (y-1,x+1) != mEmptyColor) ||
                (x+1 < mOutput.cols && y+1 < mOutput.rows && mOutput.at <cv::Vec3b> (y+1,x+1) != mEmptyColor);
    }
    return res;
}

cv::Point2d Magnet::moveCross(const cv::Point2d& pp) {
    cv::Point2d p = pp;
    double xDist = p.x - mOutput.cols / 2;
    double yDist = p.y - mOutput.rows / 2;
    if (abs (xDist) > abs (yDist)) {
        p.x -= abs (xDist) / xDist;
    } else {
        p.y -= abs (yDist) / yDist;
    }
    return p;
}

cv::Point2d Magnet::moveCircle(const cv::Point2d& pp) {
    cv::Point2d p = pp;
    double xDist = p.x - mOutput.cols/2;
    double yDist = p.y - mOutput.rows/2;
    double radius = distance(p, cv::Point2d(mOutput.cols/2, mOutput.rows/2));
    assert (radius > 0);
    double dx = xDist/radius;
    double dy = yDist/radius;
    p.x -= dx;
    p.y -= dy;
    return p;
}

cv::Point2d Magnet::moveSquare(const cv::Point2d& pp) {
    return moveCircle(pp);
}

cv::Point2d Magnet::moveGravity(const cv::Point2d& pp){
    cv::Point p = pp;
    p.y = p.y + 1;
    return p;
}

void Magnet::setPointLimit (int limit) {
    mPointLimit = limit;
}

void Magnet::setPointColor (cv::Vec3b color) {
    mPointColor = color;
}
void Magnet::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}

void Magnet::setShapeMode (ShapeMode mode) {
    tmpShapeMode = mode;
    //mShapeMode = mode;
}
void Magnet::setNeighbourMode (Neighbour mode) {
    mNeighbourMode = mode;
}

void Magnet::setFps (int fps) {
    mFps = fps;
}


int Magnet::defPointLimit () const {
    return 40000;
}
cv::Vec3b Magnet::defPointColor () const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b Magnet::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
Magnet::ShapeMode Magnet::defShapeMode () const {
    return eCircle;
}
Magnet::Neighbour Magnet::defNeighbourMode () const {
    return N4;
}

int Magnet::defFps () const {
    return 100;
}
