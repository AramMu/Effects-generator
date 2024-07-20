#include "simulation_description.h"

SimulationDescription::SimulationDescription(AbstractSimulation* sim) :
mSim(sim) {}

SimulationDescription::~SimulationDescription() {}

std::vector <ColorDescription> SimulationDescription::getColorDesc() const {
    return mColorDesc;
}
std::vector <IntDescription> SimulationDescription::getIntDesc() const {
    return mIntDesc;
}
std::vector <DoubleDescription> SimulationDescription::getDoubleDesc() const {
    return mDoubleDesc;
}
std::vector <RadioDescription> SimulationDescription::getRadioDesc() const {
    return mRadioDesc;
}
/*
std::string SimulationDescription::getTitle() const {
    return mTitle;
}
*/

AbstractSimulation* SimulationDescription::getSimulation() const {
    return mSim;
}

std::string SimulationDescription::getLongDescription () const {
    return mLongDescription;
}
std::string SimulationDescription::getFilePath () const {
    return mFilePath;
}

