#ifndef SMOKEDESCRIPTION_H
#define SMOKEDESCRIPTION_H

#include "simulation_description.h"
#include "Simulation/Generator/smoke.h"


class SmokeDescription : public SimulationDescription {
public:
    SmokeDescription(Smoke* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int);
    void changeDouble (int index, double);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    Smoke* sim;
};

#endif // SMOKEDESCRIPTION_H
