#include "wrapper.h"
#include "Simulation/Descriptor/Simulation/all_simulation_descriptions.h"
extern "C" {
int EXPORT getSimulationCount() {
    return AllSimulationDescriptions::getSimulationCount();
}

void EXPORT getTitleAt(int index, std::string& out) {
    out = AllSimulationDescriptions::getTitleAt(index);
}

SimulationDescription* EXPORT getSimulationAt(int index, const cv::Size &size) {
    return AllSimulationDescriptions::getSimulationAt(index, size);
}
}
