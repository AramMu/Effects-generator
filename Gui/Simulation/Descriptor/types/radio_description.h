#ifndef RADIO_DESCRIPTION_H
#define RADIO_DESCRIPTION_H
#include "abstract_description.h"
#include <vector>

class RadioDescription : public AbstractDescription {
public:
    RadioDescription();
    RadioDescription(const std::string& name, const std::vector<std::string>& names, int defValue);
    RadioDescription(const char* name, const std::vector<std::string>& names, int defValue);

    std::vector <std::string> getNames () const;
    int getDefValue () const;
    int count () const;

    int getCurValue () const;
    void setCurValue (int value);

private:
    std::vector <std::string> names;
    int defValue;

    int curValue;
};

#endif // RADIODESCRIPTION_H
