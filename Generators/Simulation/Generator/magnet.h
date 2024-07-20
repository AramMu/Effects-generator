#ifndef MAGNET_H
#define MAGNET_H
#include "abstract_simulation.h"
#include <opencv2/core.hpp>



/* rate: 40
 * func: 37
 * speed: 75
 * total: 84
*/
class Magnet : public AbstractSimulation {
public:
    enum ShapeMode {
        eCross, eCircle, eSquare, eGravity
    };
    enum Neighbour {
        N4, N8
    };

    explicit Magnet (const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setPointLimit (int limit);
    void setPointColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setShapeMode (ShapeMode mode);
    void setNeighbourMode (Neighbour mode);
    void setFps (int fps);

    int defPointLimit () const;
    cv::Vec3b defPointColor () const;
    cv::Vec3b defEmptyColor () const;
    ShapeMode defShapeMode () const;
    Neighbour defNeighbourMode () const;
    int defFps () const;

private:
    void setDefault();
    void start();

    bool check (const cv::Point2d& p);

    cv::Point2d moveCross(const cv::Point2d& pp);
    cv::Point2d moveCircle(const cv::Point2d& pp);
    cv::Point2d moveSquare(const cv::Point2d& pp);
    cv::Point2d moveGravity(const cv::Point2d& pp);

    cv::Mat mOutput;
    ShapeMode mShapeMode;
    Neighbour mNeighbourMode;
    cv::Vec3b mPointColor;
    cv::Vec3b mEmptyColor;

    int mFps;
    int mPointLimit;
    int mPointCount;

    ShapeMode tmpShapeMode;
};

#endif // MAGNET_H

