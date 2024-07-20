#ifndef WRAPPER_H
#define WRAPPER_H
#include <string>
#include "Simulation/Descriptor/Simulation/simulation_description.h"

#ifdef GENERATORS_LIBRARY
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

extern "C" {
int EXPORT getSimulationCount();
void EXPORT getTitleAt(int index, std::string& out);
SimulationDescription* EXPORT getSimulationAt(int index, const cv::Size &size);
}

#endif // WRAPPER_H
