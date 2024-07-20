#include "color_description.h"

ColorDescription::ColorDescription(){}
ColorDescription::ColorDescription(const std::string& name, cv::Vec3b defValue) :
    AbstractDescription(name),
    defValue(defValue),
    curValue(defValue)
{}
ColorDescription::ColorDescription(const char* name, cv::Vec3b defValue) :
    AbstractDescription(name),
    defValue(defValue),
    curValue(defValue)
{}

cv::Vec3b ColorDescription::getDefValue () const {
    return defValue;
}

cv::Vec3b ColorDescription::getCurValue () const {
    return curValue;
}

void ColorDescription::setCurValue (cv::Vec3b value) {
    curValue = value;
}
