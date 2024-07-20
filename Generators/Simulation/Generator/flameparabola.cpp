#include "flameparabola.h"
//#include "Functions/colormixerimpl.h"
//#include "ImageProcessing/noisegenerator.h"

FlameParabola::FlameParabola(const cv::Size &size) :
    AbstractSimulation(size),
    mUsed(size.height, size.width, false),
    mAvgSpeed(1.0),

    mMinHeight(size.height/5.0),
    mMaxHeight(size.height/1.05),
    mHeightDif(15.0/2 * mAvgSpeed),

    mMinCenter(0),
    mMaxCenter(size.width-1),
    mCenterDif(3.0/2 * mAvgSpeed),

    mMinParam(-0.20),
    mMaxParam(-0.05),
    mParamDif(0.01/2 * mAvgSpeed)
{
    setDefault();
    start();
}

void FlameParabola::setDefault() {
    mFlameColor = defFlameColor();
    mEmptyColor = defEmptyColor();
    mSootColor = defSootColor();

    //mDarkerMixer = FlameColorMixer();
    //mLighterMixer = FlameColorInvMixer();
    setMergeMode(defMergeMode());
    setLightMode(defLightMode());
    setColorMode(defColorMode());
    setFlameCount(defFlameCount());
    setNoise(defNoise());
}

void FlameParabola::start() {
    createFlames(0, mParabolas.size());
}


void FlameParabola::randomizeColors(int b, int e) {
    for (int i = b; i < e; ++i) {
        mColors[i] = rng.randBrightColor();
    }
}

void FlameParabola::createFlames (int b, int e) {
    switch (mColorMode) {
    case eUniform:
        for (int i = b; i < e; ++i) {
            mColors[i] = mFlameColor;
        }
        break;
    case eColored:
        randomizeColors(b,e);
        break;
    }


    for (int i = b; i < e; ++i) {
        mParabolas[i] = Parabola(
                    rng.randInt(mMinHeight, mMaxHeight),
                    rng.randInt(mMinCenter, mMaxCenter),
                    rng.randDouble(mMinParam, mMaxParam)
                    );
    }
}

cv::Mat FlameParabola::getNextFrame() {
    for (int i = 0; i < mParabolas.size(); ++i) {
        mParabolas[i].h = moveValue(mParabolas[i].h, mMinHeight, mMaxHeight, mHeightDif);
        mParabolas[i].p = moveValue(mParabolas[i].p, mMinParam, mMaxParam, mParamDif);
        mParabolas[i].c = moveValue(mParabolas[i].c, mMinCenter, mMaxCenter, mCenterDif);
    }
    cv::Mat output(mUsed.rows, mUsed.cols, CV_8UC3, mEmptyColor);
    mUsed.fill(false);
    assert (output.isContinuous());
    ColorMixer* mixer;
    switch (mLightMode) {
    case eNormal:
        mixer = &mDarkerMixer;
        break;
    case eInverted:
        mixer = &mLighterMixer;
        break;
    //default:
        //mixer = &mLayeredMixer;
        //break;
    }

    for (int i = 0; i < mParabolas.size(); ++i) {
        if (mLightMode == eInverted) {
            std::swap (mColors[i], mSootColor);
        }
        switch (mMergeMode) {
        case eLayered:
            mParabolas[i].drawGrad (output, mColors[i], mSootColor);
            break;
        case eIntersecting:
            //mParabolas[i].drawOutline (output, mColors[i], 10);
            mParabolas[i].drawGrad (output, mColors[i], mSootColor, *mixer, mUsed);
            break;
        }

        if (mLightMode == eInverted) {
            std::swap (mColors[i], mSootColor);
        }
    }
    flipVertical (output);

    return output;
}

bool FlameParabola::hasNextFrame() {
    return true;
}
void FlameParabola::restart() {
    start();
}
void FlameParabola::resetToDefault() {
    setDefault();
}

void FlameParabola::setFlameColor (cv::Vec3b color) {
    mFlameColor = color;
    if (mColorMode == eUniform) {
        for (int i = 0; i < mColors.size(); ++i) {
            mColors[i] = mFlameColor;
        }
    }
}

void FlameParabola::setEmptyColor (cv::Vec3b color){
    mEmptyColor = color;
}
void FlameParabola::setSootColor (cv::Vec3b color) {
    mSootColor = color;
}

void FlameParabola::setFlameCount (int count) {
    int oldSize = mParabolas.size();
    mParabolas.resize(count);
    mColors.resize(count);
    if (count > oldSize) {
        createFlames(oldSize, count);
    }
}

void FlameParabola::setMergeMode (MergeMode mode) {
    mMergeMode = mode;
}
void FlameParabola::setColorMode (ColorMode mode) {
    mColorMode = mode;
    switch (mode) {
    case eUniform:
        for (int i = 0; i < mColors.size(); ++i) {
            mColors[i] = mFlameColor;
        }
        break;
    case eColored:
        randomizeColors(0, mColors.size());
        break;
    }
}
void FlameParabola::setLightMode (LightMode mode) {
    mLightMode = mode;
}
void FlameParabola::setNoise (int noise) {
    mNoise = noise;
}


cv::Vec3b FlameParabola::defFlameColor() const {
    return cv::Vec3b(0,255,255);
}
cv::Vec3b FlameParabola::defEmptyColor() const {
    return cv::Vec3b(0,0,0);
}
cv::Vec3b FlameParabola::defSootColor() const {
    return cv::Vec3b(0,0,0);
}
int FlameParabola::defFlameCount() const {
    return 10;
}
FlameParabola::MergeMode FlameParabola::defMergeMode () const {
    return eIntersecting;
}
FlameParabola::ColorMode FlameParabola::defColorMode () const {
    return eUniform;
}
FlameParabola::LightMode FlameParabola::defLightMode () const {
    return eNormal;
}
int FlameParabola::defNoise () const {
    return 0;
}
