#include "gaussiannoise_description.h"

#include "utils/ImageProcessing/noisegenerator.h"

enum ColorMode {
    eUniform, eColored
};

std::string GaussianNoiseDescription::getTitle () {
    return "Gaussian noise";
}

GaussianNoiseDescription::GaussianNoiseDescription() :
    EffectDescription()
{
    mColorDesc = std::vector<ColorDescription>(1);
    //mDoubleDesc = std::vector<DoubleDescription>(1);
    mIntDesc = std::vector<IntDescription>(1);
    mRadioDesc = std::vector<RadioDescription>(1);

    mColorDesc[0] = ColorDescription("Noise color", cv::Vec3b(255,255,255));

    mIntDesc[0] = IntDescription("Noise level", 0, 300, 1, 0);

    std::vector<std::string> colorMode(2);

    colorMode.at(eUniform) = "One color";
    colorMode.at(eColored) = "Colored";

    mRadioDesc[0] = RadioDescription("Color mode", colorMode, 0);
}


void GaussianNoiseDescription::changeColor (int index, cv::Vec3b color) {
    mColorDesc[index].setCurValue(color);
}

void GaussianNoiseDescription::changeInt (int index, int value) {
    mIntDesc[index].setCurValue(value);
}

void GaussianNoiseDescription::changeDouble(int index, double value) {
    exit(-1);
}

void GaussianNoiseDescription::changeRadio (int index, int buttonIndex) {
    mRadioDesc[index].setCurValue(buttonIndex);
}

void GaussianNoiseDescription::apply (const cv::Mat &input, cv::Mat &output) {
    switch (mRadioDesc[0].getCurValue()) {
    case eUniform:
        NoiseGenerator::addGaussianNoise(input, output, 0, mIntDesc[0].getCurValue(), mColorDesc[0].getCurValue());
        break;
    case eColored:
        NoiseGenerator::addGaussianNoiseColored(input, output, 0, mIntDesc[0].getCurValue());
        break;
    }
}
