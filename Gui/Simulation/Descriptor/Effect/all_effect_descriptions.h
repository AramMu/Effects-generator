#ifndef ALLEFFECTDESCRIPTIONS_H
#define ALLEFFECTDESCRIPTIONS_H

#include "effect_description.h"

class AllEffectDescriptions {
public:
    static int getEffectCount();
    static std::string getTitleAt(int index);
    static EffectDescription* getEffectAt (int index);
};

#endif // ALLEFFECTDESCRIPTIONS_H
