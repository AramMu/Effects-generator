#ifndef MAZE_H
#define MAZE_H

#include "abstract_simulation.h"
#include "DataStructures/disjointset.h"
#include "DataStructures/graph.h"
//#include <queue>
#include <stack>
#include <opencv2/imgproc.hpp>

/* rate: 39
 * func: 16
 * speed: 45
 * total: 62
*/
class Maze : public AbstractSimulation {
public:
    explicit Maze(const cv::Size &size);
    enum Algorithm {
        ePrim, eKruskal, eBFSLoose, eBFSStrict, eDFS, eDAC, eCellular1, eCellular2
    };
    //Cellular animation with rules either B3/S12345 or B3/S1234, result is determined by starting positions

    cv::Mat getNextFrame();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setLineColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setFps (int fps);
    void setAlgorithm(Algorithm alg);

    cv::Vec3b defLineColor () const;
    cv::Vec3b defEmptyColor () const;
    int defFps () const;
    Algorithm defAlgorithm();

private:
    void setDefault();
    cv::Mat mOutput;
    int mFps;
    Algorithm mAlg;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mLineColor;

    Graph mDisjGraph;
    Graph mDfsWallGraph;
    DisjointSet mDisjSet;
    EdgeList mDisjEdges;
    int mRemaining;
    int mW, mH;
    std::stack<int> mDfsStack;
    std::vector<bool> mUsed;
    EdgeList mDfsOutput;
    void start();
    int filledCount(cv::Point p);
    /*
    DistanceMode mDistanceMode;
    DisjointSet mDisjoint;
    //EdgeListW edgeList;
    std::priority_queue<Edge3W, std::vector<Edge3W>, Edge3W::Comparator> mPriorityQueue;
    std::vector <cv::Point2i> mPoints;

    */
};

#endif // MAZE_H
