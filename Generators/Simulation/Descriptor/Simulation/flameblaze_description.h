#ifndef FLAMEBLAZEDESCRIPTION_H
#define FLAMEBLAZEDESCRIPTION_H

#include "simulation_description.h"
#include "Simulation/Generator/flameblaze.h"

class FlameBlazeDescription : public SimulationDescription {
public:
    FlameBlazeDescription(FlameBlaze *sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    FlameBlaze* sim;
};

#endif // FLAMEBLAZEDESCRIPTION_H
