#include "radio_description.h"
#include <cassert>
RadioDescription::RadioDescription():
    AbstractDescription()
{}


RadioDescription::RadioDescription(const std::string& name, const std::vector<std::string>& names, int defValue):
    AbstractDescription(name),
    names(names),
    defValue(defValue),
    curValue(defValue)
{
    assert (defValue >= 0 && defValue < names.size());
}

RadioDescription::RadioDescription(const char* name, const std::vector<std::string>& names, int defValue):
    AbstractDescription(name),
    names(names),
    defValue(defValue),
    curValue(defValue)
{
    assert (defValue >= 0 && defValue < names.size());
}

std::vector <std::string> RadioDescription::getNames () const {
    return names;
}

int RadioDescription::getDefValue () const {
    return defValue;
}

int RadioDescription::count () const {
    return names.size();
}

int RadioDescription::getCurValue () const {
    return curValue;
}
void RadioDescription::setCurValue (int value) {
    curValue = value;
}
