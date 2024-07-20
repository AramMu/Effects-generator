#ifndef DLAAGGREGATIONDESCRIPTION_H
#define DLAAGGREGATIONDESCRIPTION_H

#include "Simulation/Generator/dlaggregation.h"
#include "simulation_description.h"

class DLAggregationDescription : public SimulationDescription {
public:
    DLAggregationDescription(DLAggregation* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    DLAggregation* sim;
};

#endif // DLAAGGREGATIONDESCRIPTION_H
