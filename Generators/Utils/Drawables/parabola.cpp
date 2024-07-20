#include "parabola.h"
#include "Utils/calc.h"
#include "Functions/colormixerimpl.h"
#include "Utils/randomgenerator.h"
#include <opencv2/imgproc.hpp>
//#include <iostream>

Parabola::Parabola () {}
Parabola::Parabola (double h, double c, double p) : h(h), c(c), p(p) {}


enum DrawType {
    eFill, eGradient, eOutline
};


template <bool isColor1Black, bool isColor2Black, bool isColorMixed, DrawType type>
void _draw (const Parabola& p, cv::Mat& img,
            cv::Vec3b color1, cv::Vec3b color2, int thickness,
            const ColorMixer& mixer, Matrix<bool>& used)
{
    if (isColorMixed) {
        assert (used.size() == img.size());
    }

    cv::Point prev(-1,-1);
    for (int x = 0; x < img.cols; ++x) {
        int maxY = int (p.h + p.p*Calc::sqr(x-p.c));
        if (type == eOutline) {
            if (maxY >= 0) {
                cv::Point next(x, maxY);
                if (prev.x >= 0) {
                    cv::line (img, prev, next, color1, thickness);
                }
                prev = next;
            }
            continue;
        }
        for (int y = 0; y <= maxY && y < img.rows; ++y) {
            double tmpH = y - p.p*Calc::sqr(x-p.c);
            double tmpHdivh = tmpH/p.h;
            cv::Vec3b calcColor;
            if (type == eFill) {
                calcColor = color1;
            } else {
                if (isColor2Black) {
                    calcColor = color1 * tmpHdivh;
                } else if (isColor1Black) {
                    calcColor = color2 * (1-tmpHdivh);
                } else {
                    /*
                    calcColor = {
                        color1[0]*tmpHdivh + color2[0]*(1-tmpHdivh),
                        color1[1]*tmpHdivh + color2[1]*(1-tmpHdivh),
                        color1[2]*tmpHdivh + color2[2]*(1-tmpHdivh)
                    };
                    */
                    calcColor = {
                        uchar(color1[0]*tmpHdivh + color2[0]*(1-tmpHdivh)),
                        uchar(color1[1]*tmpHdivh + color2[1]*(1-tmpHdivh)),
                        uchar(color1[2]*tmpHdivh + color2[2]*(1-tmpHdivh))
                    };
                }
            }
            if (isColorMixed) {
                if (used.at(y,x)) {
                    calcColor = mixer.mix(img.at<cv::Vec3b>(y,x), calcColor);
                }
                used.at(y,x) = true;
            }
            img.at <cv::Vec3b> (y,x) = calcColor;
        }
    }
}

void Parabola::drawFill (cv::Mat& img, cv::Vec3b color, const ColorMixer& mixer, Matrix<bool> &used) {
    _draw<false, false, true, eFill> (*this, img, color, color, 0, mixer, used);
}
void Parabola::drawFill (cv::Mat& img, cv::Vec3b color) {
    LayeredColorMixer mixer;
    Matrix<bool> used(0,0);
    _draw<false, false, false, eFill> (*this, img, color, color, 0, mixer, used);
}

void Parabola::drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2, const ColorMixer& mixer, Matrix<bool> &used) {
    cv::Vec3b BLACK(0,0,0);
    if (color1 == BLACK) {
        _draw<true, false, true, eGradient> (*this, img, color1, color2, 0, mixer, used);
    } else if (color2 == BLACK) {
        _draw<false, true, true, eGradient> (*this, img, color1, color2, 0, mixer, used);
    } else {
        _draw<false, false, true, eGradient> (*this, img, color1, color2, 0, mixer, used);
    }
}

void Parabola::drawGrad (cv::Mat& img, cv::Vec3b color1, cv::Vec3b color2) {
    cv::Vec3b BLACK(0,0,0);
    Matrix<bool> used(0,0);
    LayeredColorMixer mixer;
    if (color1 == BLACK) {
        _draw<true, false, false, eGradient> (*this, img, color1, color2, 0, mixer, used);
    } else if (color2 == BLACK) {
        _draw<false, true, false, eGradient> (*this, img, color1, color2, 0, mixer, used);
    } else {
        _draw<false, false, false, eGradient> (*this, img, color1, color2, 0, mixer, used);
    }
}


void Parabola::drawOutline (cv::Mat& img, cv::Vec3b color, int thick) {
    LayeredColorMixer mixer;
    Matrix<bool> used(0,0);
    _draw<false, false, false, eOutline> (*this, img, color, color, thick, mixer, used);
}
