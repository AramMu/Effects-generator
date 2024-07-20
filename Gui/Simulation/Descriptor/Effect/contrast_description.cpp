#include "contrast_description.h"
#include "utils/ImageProcessing/imagecorrection.h"


std::string ContrastDescription::getTitle () {
    return "Contrast change";
}

ContrastDescription::ContrastDescription() :
    EffectDescription()
{
    //mColorDesc = std::vector<ColorDescription>(3);
    mDoubleDesc = std::vector<DoubleDescription>(1);
    //mIntDesc = std::vector<IntDescription>(2);
    //mRadioDesc = std::vector<RadioDescription>(3);


    mDoubleDesc[0] = DoubleDescription("Contrast power", 0, 256, 0.5, 1);
}


void ContrastDescription::changeColor (int index, cv::Vec3b color) {
    exit(-1);
}

void ContrastDescription::changeInt (int index, int value) {
    exit(-1);
}

void ContrastDescription::changeDouble(int index, double value) {
    mDoubleDesc[index].setCurValue(value);
}

void ContrastDescription::changeRadio (int index, int buttonIndex) {
    exit(-1);
}

void ContrastDescription::apply (const cv::Mat &input, cv::Mat &output) {
    ImageCorrection::adjustContrast(input, output, mDoubleDesc[0].getCurValue());
}
