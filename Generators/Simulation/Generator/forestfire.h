#ifndef FORESTFIRE_H
#define FORESTFIRE_H
#include "abstract_simulation.h"
#include "utils/matrix.h"
#include <opencv2/core.hpp>


/* rate: 46
 * func: 12
 * speed: 63
 * total: 73
*/
class ForestFire : public AbstractSimulation {
public:
    explicit ForestFire(const cv::Size& size);

    void setTreeProb (double prob);
    void setFireProb (double prob);
    void setTreeColor (cv::Vec3b color);
    void setFireColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    double defTreeProb() const;
    double defFireProb() const;
    cv::Vec3b defTreeColor() const;
    cv::Vec3b defFireColor() const;
    cv::Vec3b defEmptyColor() const;

private:
    enum State {
        EMPTY, TREE, FIRE
    };

    void setDefault();
    void start();

    void spread ();
    void replant ();
    void ignite ();
    void updateRandProb ();

    Matrix<int> mMat;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mTreeColor;
    cv::Vec3b mFireColor;
    double mFireProb;
    double mTreeProb;
    int mRandProbInd;
    cv::Mat mRandProb;
};

#endif // FORESTFIRE_H





