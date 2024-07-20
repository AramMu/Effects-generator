#include "double_description.h"
//#include <cassert>

DoubleDescription::DoubleDescription() {}
DoubleDescription::DoubleDescription(const std::string& name, double min, double max, double step, double defValue) :
    AbstractDescription(name),
    min(min),
    max(max),
    step(step),
    defValue(defValue),
    curValue(defValue)
{}
DoubleDescription::DoubleDescription(const char* name, double min, double max, double step, double defValue) :
    AbstractDescription(name),
    min(min),
    max(max),
    step(step),
    defValue(defValue),
    curValue(defValue)
{}

double DoubleDescription::getMin () const {
    return min;
}

double DoubleDescription::getMax () const {
    return max;
}

double DoubleDescription::getStep () const {
    return step;
}

double DoubleDescription::getDefValue () const {
    return defValue;
}

double DoubleDescription::getCurValue () const {
    return curValue;
}
void DoubleDescription::setCurValue (double value) {
    curValue = value;
}


/*
void doubleValueDescription::setMin (double min) {
    this->min = min;
}
*/
/*
void doubleValueDescription::setMax (double max) {
    this->max = max;
}
*/
/*
void doubleValueDescription::setStep (double step) {
    this->step = step;
}
*/



