#include "int_description.h"
#include <cassert>

IntDescription::IntDescription() {}
IntDescription::IntDescription(const std::string& name, int min, int max, int step, int defValue) :
    AbstractDescription(name),
    min(min),
    max(max),
    step(step),
    defValue(defValue),
    curValue(defValue)
{}
IntDescription::IntDescription(const char* name, int min, int max, int step, int defValue) :
    AbstractDescription(name),
    min(min),
    max(max),
    step(step),
    defValue(defValue),
    curValue(defValue)
{}

int IntDescription::getMin () const {
    return min;
}

int IntDescription::getMax () const {
    return max;
}

int IntDescription::getStep () const {
    return step;
}

int IntDescription::getDefValue () const {
    return defValue;
}


int IntDescription::getCurValue () const {
    return curValue;
}
void IntDescription::setCurValue (int value) {
    curValue = value;
}


/*
void IntValueDescription::setMin (int min) {
    this->min = min;
}
*/
/*
void IntValueDescription::setMax (int max) {
    this->max = max;
}
*/
/*
void IntValueDescription::setStep (int step) {
    this->step = step;
}
*/
