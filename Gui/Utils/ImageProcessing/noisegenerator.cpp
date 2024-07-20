#include "noisegenerator.h"

enum NoiseType {
    eUniform, eGaussian
};

cv::Mat _noise (const cv::Size& size, NoiseType type, int val1, int val2, cv::Vec3b color) {
    cv::Mat noise (size, CV_32SC1);
    switch (type) {
    case eUniform:
        cv::randu(noise, val1, val2);
        break;
    case eGaussian:
        cv::randn(noise, val1, val2);
        break;
    }

    std::vector <cv::Mat> matrixes (3);
    for (int i = 0; i < 3; ++i) {
        if (color[i] == 0) {
            matrixes[i] = cv::Mat(size, CV_32SC1);
        } else if (color[i] == 255) {
            matrixes[i] = noise;
        } else {
            matrixes[i] = noise/255.0 * color[i];
        }
    }
    cv::Mat output;
    cv::merge(matrixes, output);
    if (!output.isContinuous()) {
        exit(-1);
    }
    return output;
}


cv::Mat _noiseColored (const cv::Size& size, NoiseType type, int val1, int val2) {
    cv::Mat noise (size, CV_32SC3);
    switch (type) {
    case eUniform:
        cv::randu(noise, val1, val2);
        break;
    case eGaussian:
        cv::randn(noise, val1, val2);
        break;
    }
    return noise;
}



cv::Mat NoiseGenerator::uniformNoise (const cv::Size& size, int lower, int upper, cv::Vec3b color) {
    return _noise (size, eUniform, lower, upper, color);
}

cv::Mat NoiseGenerator::GaussianNoise (const cv::Size& size, int median, int deviation, cv::Vec3b color) {
    return _noise (size, eGaussian, median, deviation, color);
}

cv::Mat NoiseGenerator::uniformNoiseColored (const cv::Size& size, int lower, int upper) {
    return _noiseColored(size, eUniform, lower, upper);
}

cv::Mat NoiseGenerator::GaussianNoiseColored (const cv::Size& size, int median, int deviation) {
    return _noiseColored(size, eGaussian, median, deviation);
}





void NoiseGenerator::addUniformNoise (const cv::Mat &input, cv::Mat& output, int lower, int upper, cv::Vec3b color) {
    cv::Mat noise = uniformNoise(input.size(), lower, upper, color);
    cv::add(input, noise, output, cv::noArray(), CV_8UC3);
}

void NoiseGenerator::addGaussianNoise (const cv::Mat &input, cv::Mat& output, int median, int deviation, cv::Vec3b color) {
    cv::Mat noise = GaussianNoise(input.size(), median, deviation, color);
    cv::add(input, noise, output, cv::noArray(), CV_8UC3);
}

void NoiseGenerator::addUniformNoiseColored (const cv::Mat &input, cv::Mat& output, int lower, int upper) {
    cv::Mat noise = uniformNoiseColored(input.size(), lower, upper);
    cv::add(input, noise, output, cv::noArray(), CV_8UC3);
}

void NoiseGenerator::addGaussianNoiseColored (const cv::Mat &input, cv::Mat& output, int median, int deviation) {
    cv::Mat noise = GaussianNoiseColored(input.size(), median, deviation);
    cv::add(input, noise, output, cv::noArray(), CV_8UC3);
}
