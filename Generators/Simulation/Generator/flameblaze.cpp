#include "flameblaze.h"
//#include "Time/timemeasure.h"
#include "utils/utils.h"
#include "Utils/calc.h"
//#include "ImageProcessing/noisegenerator.h"

FlameBlaze::FlameBlaze(const cv::Size &size) :
    AbstractSimulation(size),
    mAvgSpeed(0.7),
    mUsed(size.height, size.width, false),

    mMinHeight(size.height / 9.0),
    mMaxHeight(size.height / 3.5),
    mHeightDif( (mMaxHeight - mMinHeight) / 50 * mAvgSpeed),

    mMinCenterX(0),
    mMaxCenterX(size.width-1),
    mCenterXDif( (mMaxCenterX - mMinCenterX) / 150 * mAvgSpeed),

    mMinCenterY(0),
    mMaxCenterY(size.height-1),
    mCenterYDif( (mMaxCenterY - mMinCenterY) / 150 * mAvgSpeed),

    mMinAmpl(20),
    mMaxAmpl(28),
    mAmplDif(0.2 * mAvgSpeed),

    mMinPhase(0),
    mMaxPhase(2*PI),
    mPhaseDif(0.3 * mAvgSpeed),

    mMinThick(40),
    mMaxThick(80),
    mThickDif( (mMaxThick - mMinThick) / 50 * mAvgSpeed),

    mMinPeriods(0.7),
    mMaxPeriods(1.0),
    mPeriodsDif( (mMaxPeriods - mMinPeriods) / 50 * mAvgSpeed),

    mUpwardSpeed(8*mAvgSpeed)
{
    setDefault();
    start();
}

void FlameBlaze::setDefault () {
    mFlameColor = defFlameColor();
    mEmptyColor = defEmptyColor();
    mSootColor = defSootColor();

    setMergeMode(defMergeMode());
    setFillMode(defFillMode());
    setColorMode(defColorMode());
    setFlameCount(defFlameCount());
    setNoise(defNoise());
}

void FlameBlaze::start() {
    mTongues.clear();
    mTongueHeights.clear();
    mColors.clear();
}

cv::Mat FlameBlaze::getNextFrame () {
    cv::Mat output(mUsed.rows, mUsed.cols, CV_8UC3, mEmptyColor);

    assert (output.isContinuous());
    for (int i = 0; i < mTongues.size(); ++i) {
        mTongues[i].setAmpl (mTongues[i].getAmpl() * output.rows / (output.rows-mTongues[i].getButtomY()));
        mTongues[i].setThick (mTongues[i].getThick() * output.rows / (output.rows-mTongues[i].getButtomY()));

        mTongues[i].setHeight (mTongueHeights[i] * ((output.rows - mTongues[i].getButtomY())) / output.rows);
        mTongues[i].setButtomY(mTongues[i].getButtomY() + mUpwardSpeed);

        mTongues[i].setAmpl (mTongues[i].getAmpl() / output.rows * (output.rows-mTongues[i].getButtomY()));
        mTongues[i].setThick (mTongues[i].getThick() / output.rows * (output.rows-mTongues[i].getButtomY()));

        if (mTongues[i].getButtomY() - mTongues[i].getHeight() >= output.rows) {
            /*
            mTongues[i] = mTongues.back();
            mTongueHeights[i] = mTongueHeights.back();
            mColors[i] = mColors.back();
            mTongues.pop_back();
            mTongueHeights.pop_back();
            mColors.pop_back();
            */
            for (int k = i+1; k < mTongues.size(); ++k) {
                mTongues[k-1] = mTongues[k];
                mTongueHeights[k-1] = mTongueHeights[k];
                mColors[k-1] = mColors[k];
            }
            mTongues.pop_back();
            mTongueHeights.pop_back();
            mColors.pop_back();
            i--;
        }
        mTongues[i].setOffset(mTongues[i].getOffset() + mPhaseDif);
        /*
        mTongues[i].height = moveValue(mTongues[i].height, mMinHeight, mMaxHeight, mHeightDif);
        mTongues[i].centerX = moveValue(mTongues[i].centerX, mMinCenter, mMaxCenter, mCenterDif);
        mTongues[i].ampl = moveValue(mTongues[i].ampl, mMinAmpl, mMaxAmpl, mAmplDif);
        mTongues[i].thick = moveValue(mTongues[i].thick, mMinThick, mMaxThick, mThickDif);
        mTongues[i].p2hRatio = moveValue(mTongues[i].p2hRatio, mMinP2HRatio, mMaxP2HRatio, mP2HRatioDif);

        mTongues[i].offset -= mPhaseDif/2;
        if (mTongues[i].offset < 0) {
            mTongues[i].offset += 2*PI;
        }
        */
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


    //std::cout << "Current flame count is " << mTongues.size() << std::endl;
    if (mTongues.size() < mFlameLimit) {
        double prob = rng.randProb();
        if (prob < mFlameProb) {
            mTongues.resize(mTongues.size()+1);
            mColors.resize(mColors.size()+1);
            mTongueHeights.resize(mTongueHeights.size()+1);
            createFlames(mTongues.size()-1, mTongues.size());
        }
    }

    return output;
}


bool FlameBlaze::hasNextFrame() {
    return true;
}
void FlameBlaze::restart() {
    start();
}
void FlameBlaze::resetToDefault() {
    setDefault();
}

void FlameBlaze::randomizeColors (int b, int e) {
    for (int i = b; i < e; ++i) {
        mColors[i] = rng.randBrightColor();
    }
}

void FlameBlaze::createFlames (int b, int e) {
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
        mTongues[i] = DoubleTongue (
                    rng.randDouble(mMinCenterX, mMaxCenterX),
                    rng.randDouble(mMinHeight, mMaxHeight),
                    rng.randDouble(mMinPeriods, mMaxPeriods),
                    //rng.randDouble(mMinP2HRatio, mMaxP2HRatio),
                    rng.randDouble(mMinAmpl, mMaxAmpl),
                    rng.randDouble(mMinThick, mMaxThick),
                    0.0,
                    //0.0,
                    //rng.randDouble(mMinCenterY, mMaxCenterY),
                    rng.randDouble(mMinPhase, mMaxPhase)
                    );
        mTongues[i].setButtomY (-mTongues[i].getHeight()*2);
        mTongueHeights[i] = mTongues[i].getHeight();
    }
}



void FlameBlaze::setFlameColor (cv::Vec3b color) {
    mFlameColor = color;
    switch (mColorMode) {
    case eUniform:
        for (int i = 0; i < mColors.size(); ++i) {
            mColors[i] = color;
        }
    }
}

void FlameBlaze::setEmptyColor (cv::Vec3b color) {
    mEmptyColor = color;
}

void FlameBlaze::setSootColor (cv::Vec3b color) {
    mSootColor = color;
}

void FlameBlaze::setFlameCount (int count) {
    mFlameLimit = count;
    mFlameProb = std::min (1/(mUpwardSpeed*mFlameLimit/mUsed.rows), 1.0);
    //std::cout << "Current prob is " << mFlameProb << std::endl;
}

void FlameBlaze::setFillMode (FillMode mode) {
    mFillMode = mode;
}
void FlameBlaze::setMergeMode (MergeMode mode) {
    mMergeMode = mode;
}
void FlameBlaze::setColorMode (ColorMode mode) {
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
void FlameBlaze::setLightMode (LightMode mode) {
    mLightMode = mode;
}
void FlameBlaze::setNoise (int noise) {
    mNoise = noise;
}


cv::Vec3b FlameBlaze::defFlameColor() const {
    return cv::Vec3b(0,255,255);
}
cv::Vec3b FlameBlaze::defEmptyColor() const {
    return cv::Vec3b(0,0,0);
}
cv::Vec3b FlameBlaze::defSootColor() const {
    return cv::Vec3b(0,0,0);
}
int FlameBlaze::defFlameCount() const {
    return 100;
}

FlameBlaze::FillMode FlameBlaze::defFillMode() const {
    return eGradient;
}

FlameBlaze::MergeMode FlameBlaze::defMergeMode() const {
    return eLayered;
}
FlameBlaze::ColorMode FlameBlaze::defColorMode() const {
    return eUniform;
}
FlameBlaze::LightMode FlameBlaze::defLightMode () const {
    return eNormal;
}
int FlameBlaze::defNoise () const {
    return 0;
}
