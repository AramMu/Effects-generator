#ifndef SPIDER_H
#define SPIDER_H
#include "abstract_simulation.h"
#include <opencv2/core.hpp>
//#include "DataStructures/disjointset.h"
//#include "DataStructures/graph.h"
//#include <queue>

/* rate: 35
 * func: 14
 * speed: 50
 * total: 59
*/
class Spider : public AbstractSimulation {
public:

    explicit Spider(const cv::Size &size);

    cv::Mat getNextFrame();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setPointCount (int count);
    void setLineThick (int thick);
    void setPointColor (cv::Vec3b color);
    void setLineColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);

    int defPointCount () const;
    int defLineThick () const;
    cv::Vec3b defPointColor () const;
    cv::Vec3b defLineColor () const;
    cv::Vec3b defEmptyColor () const;
private:
    void setDefault();
    void start();
    cv::Mat mOutput;

    int mPointCount;
    int mLineThick;

    cv::Vec3b mEmptyColor;
    cv::Vec3b mPointColor;
    cv::Vec3b mLineColor;

    std::vector <cv::Point2i> mPoints;

    bool mConsumed;
};

#endif // SPIDER_H
