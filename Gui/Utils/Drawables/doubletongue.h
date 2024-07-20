#ifndef DOUBLETONGUE_H
#define DOUBLETONGUE_H
#include <opencv2/core.hpp>
#include "Functions/colormixer.h"
#include "Utils/matrix.h"
#include "Drawables/tongue.h"

class DoubleTongue {
public:
    DoubleTongue();
    DoubleTongue (double centerX, double height, double periods, double ampl, double thick, double buttomY = 0, double offset=0);


    //void drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool>& used);
    void drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used);
    void drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2);
    void drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool>& used);
    void drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2);

    double getCenterX() const;
    double getHeight() const;
    double getPeriods() const;
    double getAmpl() const;
    double getThick() const;
    double getOffset() const;
    double getButtomY() const;

    void setCenterX(double val);
    void setHeight(double val);
    void setPeriods(double val);
    void setAmpl(double val);
    void setThick(double val);
    void setOffset(double val);
    void setButtomY(double val);

private:
    Tongue upper;
    Tongue lower;
};

#endif // DOUBLETONGUE_H
