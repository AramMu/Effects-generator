#include "tvnoise.h"
//#include "ImageProcessing/noisegenerator.h"
#include <opencv2/core.hpp>
TVNoise::TVNoise(const cv::Size& size) :
    AbstractSimulation(size)
{
    setDefault();
    restart();
}

void TVNoise::start() {}

void TVNoise::setDefault () {
    mColor = defColor();
    mColorMode = defColorMode();
    mDrawMode = defDrawMode();
}

cv::Mat TVNoise::getNextFrame() {
/*
    cv::Mat output(mSize, CV_8UC3);
    if (mDrawMode == eScreen) {
        switch (mColorMode) {
        case eUniform:
        {
            cv::Mat tmp(mSize, CV_8UC1);
            cv::randu(tmp, 0, 255);
            cv::Mat lookup (1, 256, CV_8UC3);

            for (int i = 0; i < lookup.cols; ++i) {
                lookup.at<cv::Vec3b>(0,i) = mColor/255.0 * i;
            }

            cv::cvtColor(tmp, tmp, CV_GRAY2BGR);
            cv::LUT(tmp, lookup, output);

            break;
        }
        case eColored:
        {
            cv::Mat tmp(mSize, CV_8UC3);
            cv::randu(tmp, 0, 255);
            output = tmp;
            break;
        }
        }
    }

    else if (mDrawMode == eHistogram) {
        switch (mColorMode){
        case eUniform:
        {
            cv::Mat tmp(mSize, CV_8UC3);
            for (int j = 0; j < mSize.width; ++j) {
                int h = rng.randInt(0, mSize.width);
                for (int i = 0; i < h; ++i) {
                    tmp.at<cv::Vec3b> (i, j) = mColor;
                }
            }
            flipVertical(tmp);
            output = tmp;
            break;
        }

        case eColored:
        {
            cv::Mat tmp(mSize, CV_8UC3);
            for (int j = 0; j < mSize.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int h = rng.randInt(0, mSize.width);
                    for (int i = 0; i < h; ++i) {
                        tmp.at<cv::Vec3b> (i, j)[k] = mColor[k];
                    }
                }
            }
            flipVertical(tmp);
            output = tmp;
            break;
        }
        }
    }
    return output;
    */
    cv::Mat output (mSize, CV_8UC3, cv::Vec3b(0,0,0));
    switch (mColorMode) {
    case eUniform:
        for (int i = 0; i < output.rows; ++i) {
            for (int j = 0; j < output.cols; ++j) {
                double r = rng.randDouble(0,1);
                cv::Vec3b color(r*mColor[0],r*mColor[1],r*mColor[2]);
                output.at<cv::Vec3b>(i,j) = color;
            }
        }
        break;
    case eColored:
        for (int i = 0; i < output.rows; ++i) {
            for (int j = 0; j < output.cols; ++j) {
                output.at<cv::Vec3b>(i,j) = rng.randColor();
            }
        }
        break;
    }
    return output;
}

bool TVNoise::hasNextFrame() {
    return true;
}
void TVNoise::restart() {
    start();
}
void TVNoise::resetToDefault() {
    setDefault();
}

void TVNoise::setColor (cv::Vec3b color) {
    mColor = color;
}
void TVNoise::setColorMode (ColorMode mode) {
    mColorMode = mode;
}
void TVNoise::setDrawMode (DrawMode mode) {
    mDrawMode = mode;
}



TVNoise::ColorMode TVNoise::defColorMode () const {
    return eUniform;
}
TVNoise::DrawMode TVNoise::defDrawMode () const {
    return eScreen;
}
cv::Vec3b TVNoise::defColor () const {
    return cv::Vec3b(255,255,255);
}
