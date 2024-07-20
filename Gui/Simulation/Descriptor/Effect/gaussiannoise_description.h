#ifndef NOISEDESCRIPTION_H
#define NOISEDESCRIPTION_H

#include "effect_description.h"


class GaussianNoiseDescription : public EffectDescription {
public:
    GaussianNoiseDescription();
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    void apply (const cv::Mat &input, cv::Mat &output);
    static std::string getTitle ();
private:
};

#endif // NOISEDESCRIPTION_H
