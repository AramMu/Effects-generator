#ifndef IMAGECORRECTION_H
#define IMAGECORRECTION_H
#include <opencv2/core.hpp>

class ImageCorrection {
public:
    static void adjustContrast (const cv::Mat& input, cv::Mat& out, double value);
};

#endif // IMAGECORRECTION_H
