#include "flametongue.h"
//#include "Time/timemeasure.h"
#include "utils/utils.h"
#include "Utils/calc.h"
//#include "ImageProcessing/noisegenerator.h"

FlameTongue::FlameTongue(const cv::Size &size) :
    AbstractSimulation(size),
    mAvgSpeed(0.5),
    mUsed(size.height, size.width, false),

    mMinHeight(size.height / 5),
    mMaxHeight(size.height / 1.05),
    mHeightDif( (mMaxHeight - mMinHeight) / 50 * mAvgSpeed),

    mMinCenter(0),
    mMaxCenter(size.width-1),
    mCenterDif( (mMaxCenter - mMinCenter) / 150 * mAvgSpeed),

    mMinAmpl(15),
    mMaxAmpl(20),
    mAmplDif(0.5 * mAvgSpeed),

    mMinPhase(0),
    mMaxPhase(2*PI),
    mPhaseDif(1.0 * mAvgSpeed),

    mMinThick(40),
    mMaxThick(80),
    mThickDif( (mMaxThick - mMinThick) / 50 * mAvgSpeed),

    mMinP2HRatio(1.2 / mMaxHeight),
    mMaxP2HRatio(3.0 / mMaxHeight),
    mP2HRatioDif( (mMaxP2HRatio - mMinP2HRatio) / 50 * mAvgSpeed)
{
    setDefault();
    start();
}

void FlameTongue::setDefault () {
    mFlameColor = defFlameColor();
    mEmptyColor = defEmptyColor();
    mSootColor = defSootColor();

    setMergeMode(defMergeMode());
    setFillMode(defFillMode());
    setColorMode(defColorMode());
    setFlameCount(defFlameCount());
    setNoise(defNoise());
}

void FlameTongue::start() {
    createFlames(0, mTongues.size());
}

cv::Mat FlameTongue::getNextFrame () {
    cv::Mat output(mUsed.rows, mUsed.cols, CV_8UC3, mEmptyColor);

    assert (output.isContinuous());
    for (int i = 0; i < mTongues.size(); ++i) {
        mTongues[i].height = moveValue(mTongues[i].height, mMinHeight, mMaxHeight, mHeightDif);
        mTongues[i].centerX = moveValue(mTongues[i].centerX, mMinCenter, mMaxCenter, mCenterDif);
        mTongues[i].ampl = moveValue(mTongues[i].ampl, mMinAmpl, mMaxAmpl, mAmplDif);
        mTongues[i].thick = moveValue(mTongues[i].thick, mMinThick, mMaxThick, mThickDif);
        mTongues[i].p2hRatio = moveValue(mTongues[i].p2hRatio, mMinP2HRatio, mMaxP2HRatio, mP2HRatioDif);

        mTongues[i].offset -= mPhaseDif/2;
        if (mTongues[i].offset < 0) {
            mTongues[i].offset += 2*PI;
        }
    }

    if (mMergeMode == eDarker) {
        mUsed.fill(false);
    }

    ColorMixer *mixer;
    switch (mLightMode) {
    case eNormal:
        mixer = &mDarkerMixer;
        break;
    case eInverted:
        mixer = &mLighterMixer;
        break;
    }

    for (int i = 0; i < mTongues.size(); ++i) {

        if (mLightMode == eInverted) {
            std::swap (mColors[i], mSootColor);
        }

        if (mMergeMode == eLayered) {
            switch (mFillMode) {
            case eGradient:
                //mTongues[i].drawFill(output, mColors[i]);
                mTongues[i].drawGradAbs(output, mColors[i], mSootColor);
                break;
            case eGradientLine:
                mTongues[i].drawGradRel(output, mColors[i], mSootColor);
                break;
            }
        } else {
            switch (mFillMode) {
            case eGradient:
                mTongues[i].drawGradAbs(output, mColors[i], mSootColor, *mixer, mUsed);
                break;
            case eGradientLine:
                mTongues[i].drawGradRel(output, mColors[i], mSootColor, *mixer, mUsed);
                break;
            }
        }

        if (mLightMode == eInverted) {
            std::swap (mColors[i], mSootColor);
        }
    }
    flipVertical (output);

    return output;
}


bool FlameTongue::hasNextFrame() {
    return true;
}
void FlameTongue::restart() {
    start();
}
void FlameTongue::resetToDefault() {
    setDefault();
}

void FlameTongue::randomizeColors (int b, int e) {
    for (int i = b; i < e; ++i) {
        mColors[i] = rng.randBrightColor();
    }
}

void FlameTongue::createFlames (int b, int e) {
    switch (mColorMode) {
    case eUniform:
        for (int i = b; i < e; ++i) {
            mColors[i] = mFlameColor;
        }
        break;
    case eColored:
        randomizeColors(b, e);
        break;
    }

    for (int i = b; i < e; ++i) {
        mTongues[i] = Tongue (
                    rng.randDouble(mMinCenter, mMaxCenter),
                    rng.randDouble(mMinHeight, mMaxHeight),
                    rng.randDouble(mMinP2HRatio, mMaxP2HRatio),
                    rng.randDouble(mMinAmpl, mMaxAmpl),
                    rng.randDouble(mMinThick, mMaxThick),
                    0,
                    rng.randDouble(mMinPhase, mMaxPhase)
                    );
    }
}



void FlameTongue::setFlameColor (cv::Vec3b color) {
    mFlameColor = color;
    switch (mColorMode) {
    case eUniform:
        for (int i = 0; i < mColors.size(); ++i) {
            mColors[i] = color;
        }
    }
}

void FlameTongue::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}

void FlameTongue::setSootColor (cv::Vec3b color) {
    mSootColor = color;
}

void FlameTongue::setFlameCount (int count) {
    int oldCount = mColors.size();
    mColors.resize(count);
    mTongues.resize(count);
    if (count > oldCount) {
        createFlames (oldCount, count);
    }
}

void FlameTongue::setFillMode (FillMode mode) {
    mFillMode = mode;
}
void FlameTongue::setMergeMode (MergeMode mode) {
    mMergeMode = mode;
}
void FlameTongue::setColorMode (ColorMode mode) {
    mColorMode = mode;
    switch (mode) {
    case eUniform:
        for (int i = 0; i < mColors.size(); ++i) {
            mColors[i] = mFlameColor;
        }
        break;
    case eColored:
        randomizeColors (0, mColors.size());
        break;
    }
}
void FlameTongue::setLightMode (LightMode mode) {
    mLightMode = mode;
}
void FlameTongue::setNoise (int noise) {
    mNoise = noise;
}


cv::Vec3b FlameTongue::defFlameColor() const {
    return cv::Vec3b(0,255,255);
}
cv::Vec3b FlameTongue::defEmptyColor() const {
    return cv::Vec3b(0,0,0);
}
cv::Vec3b FlameTongue::defSootColor() const {
    return cv::Vec3b(0,0,0);
}

int FlameTongue::defFlameCount() const {
    return 10;
}

FlameTongue::FillMode FlameTongue::defFillMode() const {
    return eGradient;
}
FlameTongue::MergeMode FlameTongue::defMergeMode() const {
    return eLayered;
}
FlameTongue::ColorMode FlameTongue::defColorMode() const {
    return eUniform;
}
FlameTongue::LightMode FlameTongue::defLightMode () const {
    return eNormal;
}
int FlameTongue::defNoise () const {
    return 0;
}
