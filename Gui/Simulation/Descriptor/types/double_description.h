#ifndef DOUBLE_DESCRIPTION_H
#define DOUBLE_DESCRIPTION_H
#include "abstract_description.h"

class DoubleDescription : public AbstractDescription {
public:
    DoubleDescription();
    DoubleDescription(const std::string& name, double min, double max, double step, double defValue);
    DoubleDescription(const char* name, double min, double max, double step, double defValue);

    double getMin () const;
    double getMax () const;
    double getStep () const;
    double getDefValue () const;

    double getCurValue () const;
    void setCurValue (double value);

    //void setMin (double min);
    //void setMax (double max);
    //void setStep (double step);

private:
    double min;
    double max;
    double step;
    double defValue;

    double curValue;
};

#endif // DOUBLE_DESCRIPTION_H
