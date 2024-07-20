#include "clothghost.h"
//#include "Functions/colormixerimpl.h"
//#include "ImageProcessing/noisegenerator.h"


ClothGhost::ClothGhost(const cv::Size &size) :
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

void ClothGhost::setDefault() {
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

void ClothGhost::start() {
    createFlames(0, mParabolas.size());
}


void ClothGhost::randomizeColors(int b, int e) {
    for (int i = b; i < e; ++i) {
        mColors[i] = rng.randBrightColor();
    }
}

void ClothGhost::createFlames (int b, int e) {
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
        mParabolas[i] = Ghost(
                    rng.randInt(mMinHeight, mMaxHeight),
                    rng.randInt(mMinCenter, mMaxCenter),
                    rng.randDouble(mMinParam, mMaxParam)
                    );
    }
}

cv::Mat ClothGhost::getNextFrame() {
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
//            mParabolas[i].drawGrad (output, mColors[i], mSootColor);
            mParabolas[i].drawFill(output, mColors[i]);
            break;
        case eIntersecting:
            //mParabolas[i].drawOutline (output, mColors[i], 10);
            mParabolas[i].drawFill(output, mColors[i], *mixer, mUsed);
//            mParabolas[i].drawGrad (output, mColors[i], mSootColor, *mixer, mUsed);
            break;
        }

        if (mLightMode == eInverted) {
            std::swap (mColors[i], mSootColor);
        }
    }
    for (int i = 0; i < mParabolas.size(); ++i) {
         mParabolas[i].drawEyes(output, mColors[i]);
    }

    flipVertical (output);

    return output;
}

bool ClothGhost::hasNextFrame() {
    return true;
}
void ClothGhost::restart() {
    start();
}
void ClothGhost::resetToDefault() {
    setDefault();
}

void ClothGhost::setFlameColor (cv::Vec3b color) {
    mFlameColor = color;
    if (mColorMode == eUniform) {
        for (int i = 0; i < mColors.size(); ++i) {
            mColors[i] = mFlameColor;
        }
    }
}

void ClothGhost::setEmptyColor (cv::Vec3b color){
    mEmptyColor = color;
}
void ClothGhost::setSootColor (cv::Vec3b color) {
    mSootColor = color;
}

void ClothGhost::setFlameCount (int count) {
    int oldSize = mParabolas.size();
    mParabolas.resize(count);
    mColors.resize(count);
    if (count > oldSize) {
        createFlames(oldSize, count);
    }
}

void ClothGhost::setMergeMode (MergeMode mode) {
    mMergeMode = mode;
}
void ClothGhost::setColorMode (ColorMode mode) {
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
void ClothGhost::setLightMode (LightMode mode) {
    mLightMode = mode;
}
void ClothGhost::setNoise (int noise) {
    mNoise = noise;
}


cv::Vec3b ClothGhost::defFlameColor() const {
    return cv::Vec3b(255,255,255);
}
cv::Vec3b ClothGhost::defEmptyColor() const {
    return cv::Vec3b(0,0,0);
}
cv::Vec3b ClothGhost::defSootColor() const {
    return cv::Vec3b(0,0,0);
}
int ClothGhost::defFlameCount() const {
    return 10;
}
ClothGhost::MergeMode ClothGhost::defMergeMode () const {
    return eIntersecting;
}
ClothGhost::ColorMode ClothGhost::defColorMode () const {
    return eUniform;
}
ClothGhost::LightMode ClothGhost::defLightMode () const {
    return eNormal;
}
int ClothGhost::defNoise () const {
    return 0;
}
