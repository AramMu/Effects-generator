#ifndef PIXELLIGHTNINGDESCRIPTION_H
#define PIXELLIGHTNINGDESCRIPTION_H

#include "Simulation/Generator/pixellightning.h"
#include "simulation_description.h"

class PixelLightningDescription : public SimulationDescription
{
public:
    PixelLightningDescription(PixelLightning* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    PixelLightning* sim;
};


#endif // PIXELLIGHTNINGDESCRIPTION_H
