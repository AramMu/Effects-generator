#ifndef RANDOMWALKERDESCRIPTION_H
#define RANDOMWALKERDESCRIPTION_H

#include "Simulation/Generator/randomwalker.h"
#include "simulation_description.h"

class RandomWalkerDescription : public SimulationDescription {
public:
    RandomWalkerDescription(RandomWalker* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    RandomWalker* sim;
};

#endif // RANDOMWALKERDESCRIPTION_H
