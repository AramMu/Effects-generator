#ifndef MSTREE_H
#define MSTREE_H
#include "abstract_simulation.h"
#include "DataStructures/disjointset.h"
#include "DataStructures/graph.h"
#include <queue>
#include <opencv2/core.hpp>

/* rate: 36
 * func: 14
 * speed: 50
 * total: 60
*/
class MSTree : public AbstractSimulation {
public:
    enum DistanceMode {
        eShort, eLong
    };

    enum ColorMode {
        eUniform, eColored, eRGB
    };

    explicit MSTree(const cv::Size &size);

    cv::Mat getNextFrame();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setDistanceMode (DistanceMode mode);
    void setPointCount (int count);
    void setLineThick (int thick);
    void setPointThick (int thick);
    void setPointColor (cv::Vec3b color);
    void setLineColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setFps (int fps);

    DistanceMode defDistanceMode () const;
    int defPointCount () const;
    int defLineThick () const;
    int defPointThick () const;
    cv::Vec3b defPointColor () const;
    cv::Vec3b defLineColor () const;
    cv::Vec3b defEmptyColor () const;
    int defFps () const;
private:
    void setDefault();
    void start();
    cv::Mat mOutput;
    DistanceMode mDistanceMode;

    int mFps;
    int mPointCount;
    int mLineThick;
    int mPointThick;

    cv::Vec3b mEmptyColor;
    cv::Vec3b mPointColor;
    cv::Vec3b mLineColor;

    DisjointSet mDisjoint;
    //EdgeListW edgeList;
    std::priority_queue<Edge3W, std::vector<Edge3W>, Edge3W::Comparator> mPriorityQueue;
    std::vector <cv::Point2i> mPoints;
    int mRemaining;
    //std::vector <Line> mLines;
    //cv::Size size;
};

#endif // MSTREE_H
