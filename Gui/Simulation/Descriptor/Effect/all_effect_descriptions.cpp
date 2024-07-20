#include "all_effect_descriptions.h"
#include "effect_description.h"
#include "contrast_description.h"
#include "gaussiannoise_description.h"

enum EffectName {
    eContrast, eGaussianNoise
};

int AllEffectDescriptions::getEffectCount() {
    return 2;
}

std::string AllEffectDescriptions::getTitleAt(int index) {
    std::string res;
    switch (index) {
    case eContrast:
        res = ContrastDescription::getTitle();
        break;
    case eGaussianNoise:
        res = GaussianNoiseDescription::getTitle();
        break;
    }
    return res;
}

EffectDescription* AllEffectDescriptions::getEffectAt (int index) {
    EffectDescription* res;
    switch (index) {
    case eContrast:
        res = new ContrastDescription();
        break;
    case eGaussianNoise:
        res = new GaussianNoiseDescription();
        break;
    }
    return res;
}
