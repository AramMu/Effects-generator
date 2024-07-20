#ifndef TVNOISEDESCRIPTION_H
#define TVNOISEDESCRIPTION_H

#include "Simulation/Generator/tvnoise.h"
#include "simulation_description.h"


class TVNoiseDescription : public SimulationDescription {
public:
    TVNoiseDescription(TVNoise* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    TVNoise* sim;
};

#endif // TVNOISEDESCRIPTION_H
