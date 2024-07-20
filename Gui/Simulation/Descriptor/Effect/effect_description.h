#ifndef EFFECTDESCRIPTION_H
#define EFFECTDESCRIPTION_H

#include "Simulation/Descriptor/types/description_list.h"

class EffectDescription {
public:
    EffectDescription();
    virtual ~EffectDescription();

    std::vector <ColorDescription> getColorDesc() const;
    std::vector <IntDescription> getIntDesc() const;
    std::vector <DoubleDescription> getDoubleDesc() const;
    std::vector <RadioDescription> getRadioDesc() const;

    std::string getLongDescription () const;

    virtual void changeColor (int index, cv::Vec3b color)=0;
    virtual void changeInt (int index, int value)=0;
    virtual void changeDouble (int index, double value)=0;
    virtual void changeRadio (int index, int buttonIndex)=0;

    virtual void apply (const cv::Mat& input, cv::Mat& output)=0;
protected:
    std::vector <ColorDescription> mColorDesc;
    std::vector <IntDescription> mIntDesc;
    std::vector <DoubleDescription> mDoubleDesc;
    std::vector <RadioDescription> mRadioDesc;

    std::string mLongDescription;
private:
};

#endif // EFFECTDESCRIPTION_H
