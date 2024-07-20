#ifndef FORESTFIRE_DESCRIPTION_H
#define FORESTFIRE_DESCRIPTION_H

#include "Simulation/Generator/forestfire.h"
#include "simulation_description.h"

class ForestFireDescription : public SimulationDescription {
public:
    ForestFireDescription(ForestFire* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    ForestFire* sim;
};

#endif // FORESTFIRE_DESCRIPTION_H
