#ifndef CONTRASTDESCRIPTION_H
#define CONTRASTDESCRIPTION_H

#include "effect_description.h"


class ContrastDescription : public EffectDescription {
public:
    ContrastDescription();
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    void apply (const cv::Mat &input, cv::Mat &output);
    static std::string getTitle ();
};

#endif // CONTRASTDESCRIPTION_H
