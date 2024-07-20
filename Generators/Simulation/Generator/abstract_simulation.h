#ifndef ABSTRACTSIMULATION_H
#define ABSTRACTSIMULATION_H

//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/types.hpp>
#include "utils/randomgenerator.h"
#include "utils/utils.h"

class AbstractSimulation {
public:
    explicit AbstractSimulation(const cv::Size& size);

    virtual cv::Mat getNextFrame () = 0;
    virtual bool hasNextFrame() = 0;
    virtual void restart() = 0;
    virtual void resetToDefault() = 0;

    virtual ~AbstractSimulation();
protected:
    RandomGenerator rng;
    cv::Size mSize;
};

#endif // ABSTRACTSIMULATION_H
