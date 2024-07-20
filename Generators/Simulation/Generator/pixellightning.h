#ifndef PIXELLIGHTNING_H
#define PIXELLIGHTNING_H
#include "abstract_simulation.h"
#include <queue>


/* rate: 70
 * func: 36
 * speed: 73
 * total: 112
*/
class PixelLightning : public AbstractSimulation {
public:
    enum ShapeMode {
        eCircle, eGravity
    };
    enum Neighbour {
        N4, N8
    };

    explicit PixelLightning(const cv::Size& size);

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

    cv::Vec3b defPointColor () const;
    cv::Vec3b defEmptyColor () const;
    int defFps () const;
    int defPointLimit () const;
    ShapeMode defShapeMode () const;
    Neighbour defNeighbourMode () const;
private:
    void setDefault();
    void start();

    int mFps;
    std::vector<cv::Point> mPoints;
    int mPointLimit;
    struct PointData {
        cv::Point p;
        double val;
        bool operator < (const PointData& x) const {
            return val > x.val;
        }
    };

    std::priority_queue<PointData> mQueue;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mPointColor;

    ShapeMode mShapeMode;
    Neighbour mNeighbourMode;
};

#endif // PIXELLIGHTNING_H
