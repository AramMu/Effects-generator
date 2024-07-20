#include "doubletongue.h"

DoubleTongue::DoubleTongue() {}
DoubleTongue::DoubleTongue (double centerX, double height, double periods, double ampl, double thick, double buttomY, double offset) :
    upper (centerX, height, periods/height, ampl, thick, buttomY, offset),
    lower (centerX, -height, periods/height, ampl, thick, buttomY, offset)
{}

/*
void DoubleTongue::drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool>& used) {
    upper.drawFill(img, color, mixer, used);
    lower.drawFill(img, color, mixer, used);
}
*/

void DoubleTongue::drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used) {
    upper.drawGradRel(img, color1, color2, mixer, used);
    lower.drawGradRel(img, color1, color2, mixer, used);
}

void DoubleTongue::drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2) {
    upper.drawGradRel(img, color1, color2);
    lower.drawGradRel(img, color1, color2);
}

void DoubleTongue::drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used) {
    upper.drawGradAbs(img, color1, color2, mixer, used);
    lower.drawGradAbs(img, color1, color2, mixer, used);
}

void DoubleTongue::drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2) {
    upper.drawGradAbs(img, color1, color2);
    lower.drawGradAbs(img, color1, color2);
}



double DoubleTongue::getCenterX() const {
    return upper.centerX;
}
double DoubleTongue::getHeight() const {
    return upper.height;
}
double DoubleTongue::getPeriods() const {
    return upper.p2hRatio*upper.height;
}
double DoubleTongue::getAmpl() const {
    return upper.ampl;
}
double DoubleTongue::getThick() const {
    return upper.thick;
}
double DoubleTongue::getOffset() const {
    return upper.offset;
}
double DoubleTongue::getButtomY() const {
    return upper.buttomY;
}

void DoubleTongue::setCenterX(double val) {
    upper.centerX = val;
    lower.centerX = val;
}

void DoubleTongue::setHeight(double val) {
    upper.height = val;
    lower.height = -val;
}

void DoubleTongue::setPeriods(double val) {
    upper.p2hRatio = val/upper.height;
    lower.p2hRatio = -val/lower.height;
}

void DoubleTongue::setAmpl(double val) {
    upper.ampl = val;
    lower.ampl = val;
}

void DoubleTongue::setThick(double val) {
    upper.thick = val;
    lower.thick = val;
}

void DoubleTongue::setOffset(double val) {
    upper.offset = val;
    lower.offset = val;
}

void DoubleTongue::setButtomY(double val) {
    upper.buttomY = val;
    lower.buttomY = val;
}
