#ifndef RANDOMWALKER_H
#define RANDOMWALKER_H
#include "abstract_simulation.h"
#include <opencv2/core.hpp>



/* rate: 52
 * func: 40
 * speed: 90
 * total: 102
*/
class RandomWalker : public AbstractSimulation
{
public:
    enum ColorMode {
        eUniform, eRGB, eColored
    };

    enum OverflowMode {
        eFixed, eOverflow, eOverwrite
    };


    explicit RandomWalker(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();


    void setColorMode (ColorMode mode);
    void setOverflowMode (OverflowMode mode);
    void setPointColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setPointCount(int count);
    void setSpeed (int speed);
    void setFps (int fps);

    ColorMode defColorMode () const;
    OverflowMode defOverflowMode () const;
    cv::Vec3b defPointColor () const;
    cv::Vec3b defEmptyColor () const;
    int defPointCount () const;
    int defSpeed () const;
    int defFps () const;

private:
    void setDefault();
    void start();

    void createColors(int b, int e);
    void createPoints(int b, int e);

    cv::Mat mOutput;
    ColorMode mColorMode;
    OverflowMode mOverflowMode;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mPointColor;
    int mFps;
    int mSpeed;
    std::vector <cv::Point> mPoints;
    std::vector <cv::Vec3b> mColors;
};

#endif // RANDOMWALKER_H
