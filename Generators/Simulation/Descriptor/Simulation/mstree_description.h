#ifndef MINIMUMSPANNINGTREEDESCRIPTION_H
#define MINIMUMSPANNINGTREEDESCRIPTION_H

#include "Simulation/Generator/mstree.h"
#include "simulation_description.h"

class MSTreeDescription : public SimulationDescription {
public:
    MSTreeDescription(MSTree* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    MSTree* sim;
};

#endif // MINIMUMSPANNINGTREEDESCRIPTION_H
