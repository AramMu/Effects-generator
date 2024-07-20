#ifndef DLAGGREGATION_H
#define DLAGGREGATION_H
#include "abstract_simulation.h"




/* rate: 70
 * func: 36
 * speed: 73
 * total: 112
*/
class DLAggregation : public AbstractSimulation {
public:
    enum ShapeMode {
        eCircle, eGravity
    };
    enum Neighbour {
        N4, N8
    };
    enum CoordinateMode {
        eCart, ePolar
    };

    explicit DLAggregation(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setPointColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setFps (int fps);
    void setPointLimit (int count);
    void setShapeMode (ShapeMode mode);
    void setNeighbourMode (Neighbour mode);
    void setCoordinateMode (CoordinateMode mode);

    cv::Vec3b defPointColor () const;
    cv::Vec3b defEmptyColor () const;
    int defFps () const;
    int defPointLimit () const;
    ShapeMode defShapeMode () const;
    Neighbour defNeighbourMode () const;
    CoordinateMode defCoordinateMode () const;

private:
    void setDefault();
    void start();
    cv::Point nearest (const cv::Point& p);
    cv::Point nearestNeighbour (const cv::Point& p, const cv::Point n);

    int mFps;
    //cv::Size mSize;
    std::vector<cv::Point> mPoints;
    int mPointLimit;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mPointColor;

    ShapeMode mShapeMode;
    Neighbour mNeighbourMode;
    CoordinateMode mCoordinateMode;

    ShapeMode tmpShapeMode;
};

#endif // DLAGGREGATION_H
