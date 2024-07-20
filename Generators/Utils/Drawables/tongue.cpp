#include "tongue.h"
#include "Utils/utils.h"
#include <cmath>
#include "Utils/calc.h"
#include "Functions/colormixerimpl.h"
//#include <iostream>

enum DrawType {
    eFill, eGradAbs, eGradRel
};

Tongue::Tongue() {}
Tongue::Tongue (double centerX, double height, double p2hRatio, double ampl, double thick, double buttomY, double offset) :
    centerX(centerX),
    height(height),
    p2hRatio(p2hRatio),
    //periods(p2hRatio*height),
    ampl(ampl),
    thick(thick),
    buttomY(buttomY),
    offset(offset)
{}


template <bool isColor1Black, bool isColor2Black, bool isColorMixed, DrawType type, bool isModulo=true>
void _draw (const Tongue& t, cv::Mat& img,
            cv::Vec3b color1, cv::Vec3b color2,
            const ColorMixer& mixer, Matrix<bool> &used)
{
    if (isColorMixed) {
        assert (img.size() == used.size());
    }

    double periods = Calc::abs (t.height * t.p2hRatio);
    double hz = periods / t.height;
    int y1 = t.buttomY+t.height;
    int y2 = t.buttomY;
    int minY = std::min (y1,y2);
    int maxY = std::max (y1,y2);
    minY = std::max (minY, 0);
    maxY = std::min (maxY, img.rows);


    for (int y = minY; y < maxY; ++y) {
        double xCen = t.ampl*std::sin (2*PI*hz*(Calc::abs(y-t.buttomY)) + t.offset) + t.centerX;
        double xDif = t.thick * ((Calc::abs(t.height) - Calc::abs(y-t.buttomY))/Calc::abs(t.height));

        //if (Calc::abs(xDif) < 1) continue;


        //int xBegin = std::max (0, int(ceil(xCen-xDif)));
        //int xEnd = std::min (img.cols-1, int(floor(xCen+xDif)));

        int xBegin = int(ceil(xCen-xDif));
        int xEnd = int(floor(xCen+xDif));

        if (!isModulo) {
            xBegin = std::max(0, xBegin);
            xEnd = std::min(img.cols-1, xEnd);
        } else {
            //if (xBegin < 0) xBegin += img.cols;
            //if (xEnd >= img.cols) xEnd -= img.cols;
        }

        double thickMinusDif = t.thick - xDif;
        int moduloTmp;
        for (int x = xBegin; x <= xEnd; ++x) {
            double ratio;
            switch (type) {
            case eGradAbs:
                ratio = Calc::sqr ((Calc::abs(x-xCen) + thickMinusDif)/t.thick);
                break;
            case eGradRel:
                ratio = Calc::abs((x-xCen)/xDif);
                break;
            }

            cv::Vec3b calcColor;
            if (type == eFill) {
                calcColor = color1;
            } else {
                if (isColor2Black) {
                    calcColor = color1*ratio;
                } else if (isColor1Black) {
                    calcColor = color2*(1-ratio);
                } else {
                    /*
                    calcColor = {
                        ratio*color1[0] + (1-ratio)*color2[0],
                        ratio*color1[1] + (1-ratio)*color2[1],
                        ratio*color1[2] + (1-ratio)*color2[2]};
                    */
                    calcColor = {
                        uchar(ratio*color1[0] + (1-ratio)*color2[0]),
                        uchar(ratio*color1[1] + (1-ratio)*color2[1]),
                        uchar(ratio*color1[2] + (1-ratio)*color2[2])};
                }
            }
            if (isModulo) {
                moduloTmp = x;
                if (x < 0) {
                    x += img.cols;
                } else if (x >= img.cols) {
                    x -= img.cols;
                }
            }
            if (isColorMixed) {
                if (used.at(y,x)) {
                    calcColor = mixer.mix(img.at<cv::Vec3b>(y,x), calcColor);
                }
                used.at(y,x) = true;
            }
            img.at<cv::Vec3b>(y,x) = calcColor;

            if (isModulo) {
                x = moduloTmp;
            }
        }
    }
}

void Tongue::drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool> &used) {
    _draw<false, false, true, eFill> (*this, img, color, cv::Vec3b(0,0,0), mixer, used);
}

void Tongue::drawFill (cv::Mat& img, cv::Vec3b color) {
    LayeredColorMixer mixer;
    Matrix<bool> used(0,0);
    _draw<false, false, false, eFill> (*this, img, color, cv::Vec3b(0,0,0), mixer, used);
}



void Tongue::drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool> &used) {
    cv::Vec3b BLACK(0,0,0);

    if (color1 == BLACK) {
        _draw<true, false, true, eGradRel> (*this, img, color1, color2, mixer, used);
    } else if (color2 == BLACK) {
        _draw<false, true, true, eGradRel> (*this, img, color1, color2, mixer, used);
    } else {
        _draw<false, false, true, eGradRel> (*this, img, color1, color2, mixer, used);
    }
}


void Tongue::drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool> &used) {
    cv::Vec3b BLACK(0,0,0);

    if (color1 == BLACK) {
        _draw<true, false, true, eGradAbs> (*this, img, color1, color2, mixer, used);
    } else if (color2 == BLACK) {
        _draw<false, true, true, eGradAbs> (*this, img, color1, color2, mixer, used);
    } else {
        _draw<false, false, true, eGradAbs> (*this, img, color1, color2, mixer, used);
    }
}



void Tongue::drawGradRel (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2) {
    cv::Vec3b BLACK(0,0,0);
    Matrix<bool> used(0,0);
    LayeredColorMixer mixer;
    if (color1 == BLACK) {
        _draw<true, false, false, eGradRel> (*this, img, color1, color2, mixer, used);
    } else if (color2 == BLACK) {
        _draw<false, true, false, eGradRel> (*this, img, color1, color2, mixer, used);
    } else {
        _draw<false, false, false, eGradRel> (*this, img, color1, color2, mixer, used);
    }
}


void Tongue::drawGradAbs (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2) {
    cv::Vec3b BLACK(0,0,0);
    Matrix<bool> used(0,0);
    LayeredColorMixer mixer;
    if (color1 == BLACK) {
        _draw<true, false, false, eGradAbs> (*this, img, color1, color2, mixer, used);
    } else if (color2 == BLACK) {
        _draw<false, true, false, eGradAbs> (*this, img, color1, color2, mixer, used);
    } else {
        _draw<false, false, false, eGradAbs> (*this, img, color1, color2, mixer, used);
    }
}
