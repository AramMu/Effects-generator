#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H
#include <opencv2/core.hpp>

class NoiseGenerator {
public:
    static cv::Mat uniformNoise (const cv::Size& size, int lower, int upper, cv::Vec3b color);
    static cv::Mat GaussianNoise (const cv::Size& size, int median, int deviation, cv::Vec3b color);
    static cv::Mat uniformNoiseColored (const cv::Size& size, int lower, int upper);
    static cv::Mat GaussianNoiseColored (const cv::Size& size, int median, int deviation);


    static void addUniformNoise (const cv::Mat& input, cv::Mat& output, int lower, int upper, cv::Vec3b color);
    static void addGaussianNoise (const cv::Mat& input, cv::Mat& output, int median, int deviation, cv::Vec3b color);
    static void addUniformNoiseColored (const cv::Mat& input, cv::Mat& output, int lower, int upper);
    static void addGaussianNoiseColored (const cv::Mat& input, cv::Mat& output, int median, int deviation);
};

#endif // NOISEGENERATOR_H
