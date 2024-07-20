#ifndef COLORMIXER_H
#define COLORMIXER_H
#include <opencv2/core/types.hpp>

class ColorMixer {
public:
    ColorMixer() {}
    virtual ~ColorMixer() {}
    virtual cv::Vec3b mix (cv::Vec3b c1, cv::Vec3b c2) const = 0;
};

#endif // COLORMIXER_H
