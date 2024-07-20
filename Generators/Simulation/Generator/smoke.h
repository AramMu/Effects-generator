#ifndef SMOKE_H
#define SMOKE_H
#include "abstract_simulation.h"
#include <opencv2/core.hpp>



/* rate: 50
 * func: 27
 * speed: 81
 * total: 91
*/
class Smoke : public AbstractSimulation {
public:
    enum ColorMode {
        eUniform, eRGB, eColored
    };

    explicit Smoke(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setSmokeColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setSmokeProb (double prob);
    void setColorMode (ColorMode mode);
    void setScaleX (double scale);
    void setScaleY (double scale);

    cv::Vec3b defSmokeColor ();
    cv::Vec3b defEmptyColor ();
    double defSmokeProb ();
    ColorMode defColorMode ();
    double defScaleX ();
    double defScaleY ();

private:
    void setDefault();
    void start();
    cv::Vec3b calcSum3 (int y, int x);
    cv::Vec3b calcSum4 (int y, int x);
    void generateButtom();
    //cv::Size mSize;
    double mScaleX;
    double mScaleY;
    cv::Mat mMat;
    double mSmokeProb;
    cv::Vec3b mSmokeColor;
    cv::Vec3b mEmptyColor;
    ColorMode mColorMode;
};

#endif // SMOKE_H
