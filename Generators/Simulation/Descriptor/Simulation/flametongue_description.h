#ifndef FLAMETONGUEDESCRIPTION_H
#define FLAMETONGUEDESCRIPTION_H

#include "Simulation/Generator/flametongue.h"
#include "simulation_description.h"

class FlameTongueDescription : public SimulationDescription {
public:
    FlameTongueDescription(FlameTongue* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    FlameTongue* sim;
};


#endif // FLAMETONGUEDESCRIPTION_H
