#ifndef CLOTHGHOST_H
#define CLOTHGHOST_H

#include "abstract_simulation.h"
#include "Functions/colormixer.h"
//#include "Drawables/parabola.h"
#include "Functions/colormixerimpl.h"
#include "Utils/Drawables/ghost.h"

/* rate: 115
 * func: 76
 * speed: 47
 * total: 169
 *
 * rate + func/2 + speed/3
*/
class ClothGhost : public AbstractSimulation {
public:
    enum MergeMode {
        eIntersecting, eLayered
    };

    enum ColorMode {
        eUniform, eColored
    };

    enum LightMode {
        eNormal, eInverted
    };

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    explicit ClothGhost(const cv::Size& size);
    void setFlameColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setSootColor (cv::Vec3b color);
    void setFlameCount (int count);
    void setMergeMode (MergeMode mode);
    void setColorMode (ColorMode mode);
    void setLightMode (LightMode mode);
    void setNoise (int noise);

    cv::Vec3b defFlameColor() const;
    cv::Vec3b defEmptyColor() const;
    cv::Vec3b defSootColor() const;
    int defFlameCount() const;
    MergeMode defMergeMode () const;
    ColorMode defColorMode () const;
    LightMode defLightMode () const;
    int defNoise () const;
private:
    void setDefault();
    void start();
    void randomizeColors (int b, int e);
    void createFlames (int b, int e);

    const double mAvgSpeed;
    Matrix <bool> mUsed;

    MergeMode mMergeMode;
    ColorMode mColorMode;
    LightMode mLightMode;

    std::vector <Ghost> mParabolas;
    cv::Vec3b mFlameColor;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mSootColor;
    std::vector <cv::Vec3b> mColors;

    const double mHeightDif;
    const double mCenterDif;
    const double mParamDif;
    const double mMinHeight;
    const double mMaxHeight;
    const double mMinCenter;
    const double mMaxCenter;
    const double mMinParam;
    const double mMaxParam;

    FlameColorMixer mDarkerMixer;
    FlameColorInvMixer mLighterMixer;
    LayeredColorMixer mLayeredMixer;
    int mNoise;
};



#endif // CLOTHGHOST_H
