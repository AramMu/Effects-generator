#ifndef LIGHTNINGTREEDESCRIPTION_H
#define LIGHTNINGTREEDESCRIPTION_H

#include "Simulation/Generator/lightningtree.h"
#include "simulation_description.h"

class LightningTreeDescription : public SimulationDescription {
public:
    LightningTreeDescription(LightningTree* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    LightningTree* sim;
};

#endif // LIGHTNINGTREEDESCRIPTION_H
