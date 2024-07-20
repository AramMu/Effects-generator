#ifndef PLASMADESCRIPTION_H
#define PLASMADESCRIPTION_H

#include "Simulation/Generator/plasma.h"
#include "simulation_description.h"

class PlasmaDescription : public SimulationDescription {
public:
    PlasmaDescription(Plasma* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int);
    void changeDouble (int index, double value);
    void changeRadio (int index, int);

    static std::string getTitle ();
private:
    Plasma* sim;
};


#endif // PLASMADESCRIPTION_H
