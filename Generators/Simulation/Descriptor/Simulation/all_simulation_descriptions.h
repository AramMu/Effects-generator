#ifndef ALL_DESCRIPTIONS
#define ALL_DESCRIPTIONS

#include "simulation_description.h"


class AllSimulationDescriptions {
public:
    static int getSimulationCount();
    static std::string getTitleAt(int index);
    static SimulationDescription* getSimulationAt (int index, const cv::Size& size);
    //static std::pair<AbstractSimulation*, SimulationDescription*> getSimulationAt(int index, const cv::Size& size);
};

#endif // ALL_DESCRIPTIONS

