#ifndef DISTANCECRYSTAL_H
#define DISTANCECRYSTAL_H
#include "abstract_simulation.h"
#include <opencv2/core.hpp>
//#include "utils/point.h"



/* rate: 49
 * func: 42
 * speed: 94
 * total: 101
*/
class DistanceCrystal : public AbstractSimulation {
public:
    enum StartMode {
        eCenter, eButtom, eRandom
    };

    enum ColorMode {
        eUniform, eColored, eRGB
    };

    explicit DistanceCrystal(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setStartMode (StartMode mode);
    void setColorMode (ColorMode mode);
    void setLineColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setFps (int fps);
    void setPointCount (int count);
    void setSiteCount (int count);

    StartMode defStartMode () const;
    ColorMode defColorMode () const;
    cv::Vec3b defLineColor () const;
    cv::Vec3b defEmptyColor () const;
    int defFps () const;
    int defPointCount () const;
    int defSiteCount () const;

    int minFps () const;
    int maxFps () const;
    int stepFps () const;
    int minPointCount () const;
    int maxPointCount () const;
    int stepPointCount () const;
    int minSiteCount () const;
    int maxSiteCount () const;
    int stepSiteCount () const;

private:
    void setDefault();
    void start();

    class PointIndex {
    public:
        PointIndex () {}
        PointIndex (const cv::Point2i& p, int index, double dist) : p(p), index(index), dist(dist) {}
        cv::Point2i p;
        int index;
        double dist;
        bool operator < (const PointIndex& pInd) {
            return dist < pInd.dist;
        }
        class CompareGreater {
        public:
            bool operator () (const PointIndex& p1, const PointIndex& p2) {
                return p1.dist > p2.dist;
            }
        };
    };

    int mFps;
    int mSiteCount;
    int mPointCount;
    StartMode mStartMode;
    ColorMode mColorMode;
    cv::Vec3b mLineColor;
    cv::Vec3b mEmptyColor;
    cv::Mat mOutput;
    std::vector <PointIndex> mPoints;
    std::vector <cv::Point> mSites;


    /*
    int mPointsDef();
    int mSitesDef(StartMode mode);
    StartMode mStartModeDef();
    cv::Vec3b mPointColorDef();
    cv::Vec3b mLineColorDef();
    cv::Vec3b mEmptyColorDef();
    */
};

#endif // DISTANCECRYSTAL_H
