#ifndef FLAMEBLAZE_H
#define FLAMEBLAZE_H
#include "abstract_simulation.h"
#include "Drawables/doubletongue.h"
#include "Functions/colormixerimpl.h"


/* rate: 65
 * func: 45
 * speed: 47
 * total: 103
*/
class FlameBlaze : public AbstractSimulation {
public:
    enum MergeMode {
        eDarker, eLayered
    };

    enum FillMode {
        eGradient, eGradientLine
    };

    enum ColorMode {
        eUniform, eColored
    };

    enum LightMode {
        eNormal, eInverted
    };

    explicit FlameBlaze(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setFlameColor (cv::Vec3b color);
    void setEmptyColor (cv::Vec3b color);
    void setSootColor (cv::Vec3b color);
    void setFlameCount (int count);
    void setFillMode (FillMode mode);
    void setMergeMode (MergeMode mode);
    void setColorMode (ColorMode mode);
    void setLightMode (LightMode mode);
    void setNoise (int noise);

    cv::Vec3b defFlameColor() const;
    cv::Vec3b defEmptyColor() const;
    cv::Vec3b defSootColor() const;
    int defFlameCount() const;
    FillMode defFillMode () const;
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
    Matrix<bool> mUsed;

    MergeMode mMergeMode;
    FillMode mFillMode;
    ColorMode mColorMode;
    LightMode mLightMode;

    cv::Vec3b mFlameColor;
    cv::Vec3b mEmptyColor;
    cv::Vec3b mSootColor;
    std::vector <DoubleTongue> mTongues;
    std::vector <double> mTongueHeights;
    std::vector <cv::Vec3b> mColors;


    const double mMinHeight;
    const double mMaxHeight;
    const double mHeightDif;

    const double mMinCenterX;
    const double mMaxCenterX;
    const double mCenterXDif;

    const double mMinCenterY;
    const double mMaxCenterY;
    const double mCenterYDif;

    const double mMinAmpl;
    const double mMaxAmpl;
    const double mAmplDif;

    const double mMinThick;
    const double mMaxThick;
    const double mThickDif;

    const double mMinPeriods;
    const double mMaxPeriods;
    const double mPeriodsDif;

    const double mMinPhase;
    const double mMaxPhase;
    const double mPhaseDif;

    double mFlameProb;
    const double mUpwardSpeed;

    FlameColorMixer mDarkerMixer;
    FlameColorInvMixer mLighterMixer;
    int mFlameLimit;
    int mNoise;
};

#endif // FLAMEBLAZE_H
