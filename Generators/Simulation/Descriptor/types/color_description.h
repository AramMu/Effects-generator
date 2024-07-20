#ifndef COLOR_DESCRIPTION_H
#define COLOR_DESCRIPTION_H
#include "abstract_description.h"
//#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>

class ColorDescription : public AbstractDescription {
public:
    ColorDescription();
    ColorDescription(const std::string& name, cv::Vec3b defValue);
    ColorDescription(const char* name, cv::Vec3b defValue);
    cv::Vec3b getDefValue () const;
    cv::Vec3b getCurValue () const;
    void setCurValue (cv::Vec3b value);

private:
    cv::Vec3b defValue;
    cv::Vec3b curValue;
};

#endif // COLOR_DESCRIPTION_H
