#include "effect_description.h"

EffectDescription::EffectDescription() {}

EffectDescription::~EffectDescription() {}

std::vector <ColorDescription> EffectDescription::getColorDesc() const {
    return mColorDesc;
}
std::vector <IntDescription> EffectDescription::getIntDesc() const {
    return mIntDesc;
}
std::vector <DoubleDescription> EffectDescription::getDoubleDesc() const {
    return mDoubleDesc;
}
std::vector <RadioDescription> EffectDescription::getRadioDesc() const {
    return mRadioDesc;
}

std::string EffectDescription::getLongDescription () const {
    return mLongDescription;
}
