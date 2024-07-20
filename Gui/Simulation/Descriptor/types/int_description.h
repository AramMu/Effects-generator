#ifndef INT_DESCRIPTION_H
#define INT_DESCRIPTION_H

#include "abstract_description.h"

class IntDescription : public AbstractDescription {
public:
    IntDescription();
    IntDescription(const std::string& name, int min, int max, int step, int defValue);
    IntDescription(const char* name, int min, int max, int step, int defValue);

    int getMin () const;
    int getMax () const;
    int getStep () const;
    int getDefValue () const;

    int getCurValue () const;
    void setCurValue (int value);

    //void setMin (int min);
    //void setMax (int max);
    //void setStep (int step);

private:
    int min;
    int max;
    int step;
    int defValue;

    int curValue;
};

#endif // INT_DESCRIPTION_H
