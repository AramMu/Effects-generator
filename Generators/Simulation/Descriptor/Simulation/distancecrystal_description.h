#ifndef DISTANCECRYSTALDESCRIPTION_H
#define DISTANCECRYSTALDESCRIPTION_H

#include "Simulation/Generator/distancecrystal.h"
#include "simulation_description.h"

class DistanceCrystalDescription : public SimulationDescription {
public:
    DistanceCrystalDescription(DistanceCrystal* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    DistanceCrystal* sim;
};




#endif // DISTANCECRYSTALDESCRIPTION_H
