#ifndef FLAMEPARABOLA_DESCRIPTION_H
#define FLAMEPARABOLA_DESCRIPTION_H

#include "simulation_description.h"
#include "Simulation/Generator/flameparabola.h"

class FlameParabolaDescription : public SimulationDescription {
public:
    FlameParabolaDescription(FlameParabola* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    FlameParabola* sim;
};

#endif // FLAMEPARABOLA_DESCRIPTION_H
