#ifndef MAGNETDESCRIPTION_H
#define MAGNETDESCRIPTION_H

#include "Simulation/Generator/magnet.h"
#include "simulation_description.h"

class MagnetDescription : public SimulationDescription {
public:
    MagnetDescription(Magnet* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    Magnet* sim;
};

#endif // MAGNETDESCRIPTION_H
