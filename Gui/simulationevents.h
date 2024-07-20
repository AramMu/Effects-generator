#ifndef SIMULATIONEVENTS
#define SIMULATIONEVENTS
#include <opencv2/imgproc.hpp>

struct IntEvent {
    int index;
    int value;
};

struct DoubleEvent {
    int index;
    double value;
};

struct ColorEvent {
    int index;
    cv::Vec3b color;
};

struct RadioEvent {
    int index;
    int buttonIndex;
};

#endif // SIMULATIONEVENTS

