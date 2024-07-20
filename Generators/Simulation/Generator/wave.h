#ifndef WAVE_H
#define WAVE_H

#include "abstract_simulation.h"
#include "utils/matrix.h"



/* rate: 46
 * func: 12
 * speed: 58
 * total: 71
*/
class Wave : public AbstractSimulation {
public:
    explicit Wave(const cv::Size& size);

    void setStoneProb (double prob);

    void setStoneColor (cv::Vec3b color);
    void setWaterColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    double defStoneProb() const;

    cv::Vec3b defStoneColor() const;
    cv::Vec3b defWaterColor() const;
    cv::Vec3b defEmptyColor() const;

private:
    enum State {
        EMPTY, STONE, WATER
    };

    void setDefault();
    void start();

    void flowWater ();
    void createStones ();

    Matrix<int> mMat;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mStoneColor;
    cv::Vec3b mWaterColor;
    double mStoneProb;
};

#endif // WAVE_H
