#include "voronoidiagram_description.h"


std::string VoronoiDiagramDescription::getTitle () {
    return "Voronoi diagram";
}

VoronoiDiagramDescription::VoronoiDiagramDescription(VoronoiDiagram* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(3);
    //mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(1);
    mRadioDesc = std::vector<RadioDescription>(1);

    mColorDesc[0] = ColorDescription("Empty color", sim->defEmptyColor());
    mColorDesc[1] = ColorDescription("Point color", sim->defPointColor());
    mColorDesc[2] = ColorDescription("Line color", sim->defLineColor());

    mIntDesc[0] = IntDescription("Point count", 1, 50, 5, sim->defPointCount());

    std::vector<std::string> distanceMode(3);

    distanceMode.at(VoronoiDiagram::eEuclid) = "Euclidian";
    distanceMode.at(VoronoiDiagram::eCity) = "City";
    distanceMode.at(VoronoiDiagram::eChess) = "Chess";

    mRadioDesc[0] = RadioDescription("Distance type", distanceMode, sim->defDistanceMode());

    mFilePath = "Voronoi diagram";
}



void VoronoiDiagramDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setEmptyColor(color);
        break;
    case 1:
        sim->setPointColor(color);
        break;
    case 2:
        sim->setLineColor(color);
        break;
    }
}

void VoronoiDiagramDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setPointCount(value);
        break;
    }
}

void VoronoiDiagramDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void VoronoiDiagramDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setDistanceMode(VoronoiDiagram::DistanceMode (buttonIndex));
        break;
    }
}
