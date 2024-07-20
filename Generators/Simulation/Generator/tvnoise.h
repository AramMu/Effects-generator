#ifndef TVNOISE_H
#define TVNOISE_H
#include "abstract_simulation.h"




/* rate: 22
 * func: 7
 * speed: 75
 * total: 51
*/
class TVNoise : public AbstractSimulation {
public:
    enum ColorMode {
        eUniform, eColored
    };

    enum DrawMode {
        eScreen, eHistogram
    };

    explicit TVNoise(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setColorMode (ColorMode mode);
    void setDrawMode (DrawMode mode);
    void setColor (cv::Vec3b color);

    ColorMode defColorMode () const;
    DrawMode defDrawMode () const;
    cv::Vec3b defColor () const;
private:
    void setDefault();
    void start();

    //cv::Size mSize;
    ColorMode mColorMode;
    DrawMode mDrawMode;
    cv::Vec3b mColor;

    //static cv::Vec3b mColorDef();
};

#endif // TVNOISE_H
