#ifndef VORONOIDIAGRAMDESCRIPTION_H
#define VORONOIDIAGRAMDESCRIPTION_H

#include "Simulation/Generator/voronoidiagram.h"
#include "simulation_description.h"

class VoronoiDiagramDescription : public SimulationDescription {
public:
    VoronoiDiagramDescription(VoronoiDiagram* sim);
    void changeColor (int index, cv::Vec3b color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    static std::string getTitle ();
private:
    VoronoiDiagram* sim;
};


#endif // VORONOIDIAGRAMDESCRIPTION_H
