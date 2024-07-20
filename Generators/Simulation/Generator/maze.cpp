#include "maze.h"
//#include <algorithm>
#include <queue>
//#include "Time/timemeasure.h"

Maze::Maze(const cv::Size& size) :
    AbstractSimulation (size),
    mOutput(size, CV_8UC3)
{
    setDefault();
}

void Maze::setDefault(){
    mEmptyColor = defEmptyColor();
    mLineColor = defLineColor();
    mFps = defFps();
    mAlg = defAlgorithm();
    start();
}
void Maze::start(){
    mOutput = cv::Mat(mSize, CV_8UC3, mEmptyColor);
    mW = (mSize.width+1)/2;
    mH = (mSize.height+1)/2;
    mRemaining = mW*mH-1;
    if (mAlg == eKruskal) {
        mDisjGraph.resize(mW*mH);
        mDisjSet = DisjointSet(mW*mH);
        for (int i = 0; i < mH; ++i) {
            for (int j = 0; j < mW; ++j) {
                if (i+1<mH) {
                    mDisjEdges.emplace_back(i*mW+j, (i+1)*mW+j);
                }
                if (i-1>=0) {
                    mDisjEdges.emplace_back(i*mW+j, (i-1)*mW+j);
                }
                if (j+1<mW) {
                    mDisjEdges.emplace_back(i*mW+j, i*mW+j+1);
                }
                if (j-1>=0) {
                    mDisjEdges.emplace_back(i*mW+j, i*mW+j-1);
                }
            }
        }
    } else if (mAlg == eDFS) {
        mDfsWallGraph.resize(mW*mH);
        mUsed.resize(mW*mH, false);
        int st = RandomGenerator::randInt(mW*mH);
        mUsed[st] = true;
        mDfsStack.push(st);
        for (int i = 0; i < mH; ++i) {
            for (int j = 0; j < mW; ++j) {
                if (i+1<mH) {
                    mDfsWallGraph[i*mW+j].push_back((i+1)*mW+j);
                    mDfsWallGraph[(i+1)*mW+j].push_back(i*mW+j);
                }
                if (i-1>=0) {
                    mDfsWallGraph[i*mW+j].push_back((i-1)*mW+j);
                    mDfsWallGraph[(i-1)*mW+j].push_back(i*mW+j);
                }
                if (j+1<mW) {
                    mDfsWallGraph[i*mW+j].push_back(i*mW+j+1);
                    mDfsWallGraph[i*mW+j+1].push_back(i*mW+j);
                }
                if (j-1>=0) {
                    mDfsWallGraph[i*mW+j].push_back(i*mW+j-1);
                    mDfsWallGraph[i*mW+j-1].push_back(i*mW+j);
                }
            }
        }
    } else if (mAlg == eCellular1 || mAlg == eCellular2) {
        double prob = 0.02;
        for (int i = 0; i < mSize.height; ++i) {
            for (int j = 0; j < mSize.width; ++j) {
                double p = RandomGenerator::randDouble(1);
                if (p < prob) {
                    mOutput.at<cv::Vec3b>(i,j) = mLineColor;
                }
            }
        }
    }
    /*
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
    */
}

int Maze::filledCount(cv::Point p) {
    int res=0;
    for (int i = p.y-1; i <= p.y+1; ++i) {
        for (int j = p.x-1; j <= p.x+1; ++j) {
            if (i==p.y && j==p.x)
                continue;
            if (i < 0 || j < 0 || i >= mSize.height || j >= mSize.width)
                continue;
            if (mOutput.at<cv::Vec3b>(i,j) == mLineColor)
                res++;
        }
    }
    return res;
}

cv::Mat Maze::getNextFrame() {
    /*
    if (mAlg == eDFS) {
        for (int frameCount = 0; frameCount < mFps; ++frameCount) {

        }
    }
    */
    if (mAlg == eKruskal) {
        for (int frameCount = 0; frameCount < mFps && mRemaining>0; ++frameCount) {
            int ind = RandomGenerator::randInt(mDisjEdges.size());
            Edge2 e = mDisjEdges[ind];
            mDisjEdges[ind] = mDisjEdges.back();
            mDisjEdges.pop_back();
            if (mDisjSet.find(e.u) == mDisjSet.find(e.v)) {
                frameCount--;
                continue;
            }
            mRemaining--;
            mDisjGraph[e.u].push_back(e.v);
            mDisjGraph[e.v].push_back(e.u);
            mDisjSet.merge(e.u, e.v);
        }
        for (int u = 0; u < mDisjGraph.size(); ++u) {
            if (!mDisjGraph[u].empty()) {
                for (int i = 0; i < mDisjGraph[u].size(); ++i) {
                    int v = mDisjGraph[u][i];
                    cv::line(mOutput, {u%mW*2, u/mW*2}, {v%mW*2, v/mW*2}, mLineColor, 1);
                }
            }
        }

        return mOutput.clone();
    } else if (mAlg == eDFS) {
        for (int frameCount = 0; frameCount < mFps && mRemaining > 0; ++frameCount) {
            int u = mDfsStack.top();
            if (mDfsWallGraph[u].empty()) {
                mDfsStack.pop();
                frameCount--;
                continue;
            }
            int ind = RandomGenerator::randInt(mDfsWallGraph[u].size());
            int v = mDfsWallGraph[u][ind];
            mDfsWallGraph[u][ind] = mDfsWallGraph[u].back();
            mDfsWallGraph[u].pop_back();
            if (mUsed[v]) {
                frameCount--;
                continue;
            }
            mRemaining--;
            mDfsStack.push(v);
            mDfsOutput.emplace_back(u, v);
            mUsed[v] = true;
        }

        for (int i = 0; i < mDfsOutput.size(); ++i) {
            int u = mDfsOutput[i].u;
            int v = mDfsOutput[i].v;
            cv::line(mOutput, {u%mW*2, u/mW*2}, {v%mW*2, v/mW*2}, mLineColor, 1);
        }
        return mOutput.clone();
    } else if (mAlg == eCellular1 || mAlg == eCellular2) {
        cv::Mat next = cv::Mat(mSize, CV_8UC3, mEmptyColor);
        for (int i = 0; i < mSize.height; ++i) {
            for (int j = 0; j < mSize.width; ++j) {
                int cnt = filledCount({j,i});
                if (mOutput.at<cv::Vec3b>(i,j) == mEmptyColor) {
                    if (cnt == 3) {
                        next.at<cv::Vec3b>(i,j) = mLineColor;
                    } else {
                        next.at<cv::Vec3b>(i,j) = mEmptyColor;
                    }
                } else {
                    if (cnt > 5 || (cnt == 5 && mAlg==eCellular2)) {
                        next.at<cv::Vec3b>(i,j) = mEmptyColor;
                    } else {
                        next.at<cv::Vec3b>(i,j) = mLineColor;
                    }
                }
            }
        }
        mOutput = next;
        return mOutput.clone();
    }
    /*
    for (int frameCount = 0; frameCount < mFps && mRemaining > 0; ++frameCount) {
        assert (!mPriorityQueue.empty());
        Edge3W e = mPriorityQueue.top();
        mPriorityQueue.pop();
        if (mDisjoint.merge(e.u, e.v)) {
            cv::line (mOutput, mPoints[e.u], mPoints[e.v], mLineColor, mLineThick);
            cv::circle(mOutput, mPoints[e.u], mPointThick, mPointColor, -1);
            cv::circle(mOutput, mPoints[e.v], mPointThick, mPointColor, -1);
            --mRemaining;
        } else {
            --frameCount;
        }
    }

    return mOutput.clone();
    */
}

bool Maze::hasNextFrame() {
    return mRemaining > 0;
    //return mRemaining > 0;
    //return !mPriorityQueue.empty();
}
void Maze::restart() {
    start();
}
void Maze::resetToDefault() {
    setDefault();
}

void Maze::setLineColor (cv::Vec3b color){
    mLineColor = color;
}
void Maze::setEmptyColor (cv::Vec3b color){
    mEmptyColor = color;
}
void Maze::setFps (int fps) {
    mFps = fps;
}
void Maze::setAlgorithm(Maze::Algorithm alg) {
    mAlg = alg;
}


cv::Vec3b Maze::defLineColor () const {
   return cv::Vec3b(0,0,255);
}
cv::Vec3b Maze::defEmptyColor () const {
    return cv::Vec3b(0,0,0);
}
int Maze::defFps () const {
    return 20;
}
Maze::Algorithm Maze::defAlgorithm() {
    return eDFS;
    //return eCellular2;
}
