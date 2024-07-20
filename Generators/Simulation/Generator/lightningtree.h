#ifndef LIGHTNINGTREE_H
#define LIGHTNINGTREE_H
#include "abstract_simulation.h"
#include <queue>
#include "DataStructures/graph.h"
#include <opencv2/core.hpp>

/* rate: 66
 * func: 14
 * speed: 65
 * total: 95
*/
class LightningTree : public AbstractSimulation {
public:
    explicit LightningTree(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setPointCount (int count);
    void setLineColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setLineThickness (int thick);
    void setPower (double power);
    void setLightFrames (int frames);
    void setEmptyFrames (int frames);
    void setStrikeProb (double prob);

    int defPointCount () const;
    cv::Vec3b defLineColor () const;
    cv::Vec3b defEmptyColor () const;
    int defLineThickness () const;
    double defPower () const;
    int defLightFrames () const;
    int defEmptyFrames () const;
    double defStrikeProb () const;


private:
    void setDefault();
    void start();
    double elecDistance(const cv::Point& p1, const cv::Point& p2);
    double angleY (cv::Point p1, cv::Point p2);
    void createPoints();

    //cv::Size mSize;
    int mFrameCount;
    int mPointCount;
    int mLineThick;
    double mPower;

    cv::Vec3b mEmptyColor;
    cv::Vec3b mLineColor;
    cv::Mat mOutput;

    std::priority_queue<Edge3W, std::vector<Edge3W>, Edge3W::Comparator> mPriorityQueue;
    std::vector <cv::Point2i> mPoints;
    std::vector <bool> mUsed;
    bool mReachedButtom;
    int mRemaining;

    int mLightFrames;
    int mEmptyFrames;

    double mStrikeProb;
};

#endif // LIGHTNINGTREE_H
