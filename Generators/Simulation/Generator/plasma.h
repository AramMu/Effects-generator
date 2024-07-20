#ifndef CLIMBER_H
#define CLIMBER_H
#include "utils/matrix.h"
#include "abstract_simulation.h"
#include <opencv2/core.hpp>

/* rate: 37
 * func: 9
 * speed: 90
 * total: 72
*/
class Plasma : public AbstractSimulation {
public:
    Plasma (const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setEmptyColor (cv::Vec3b color);
    void setUsedColor (cv::Vec3b color);
    void setBranchProb (double prob);

    cv::Vec3b defEmptyColor () const;
    cv::Vec3b defUsedColor () const;
    double defBranchProb () const;

private:
    void setDefault();
    void start();

    cv::Mat mOutput;
    Matrix<bool> mUsed;

    cv::Vec3b mUsedColor;
    cv::Vec3b mEmptyColor;
    double mBranchProb;
    double mConsumed;
};

#endif // CLIMBER_H
