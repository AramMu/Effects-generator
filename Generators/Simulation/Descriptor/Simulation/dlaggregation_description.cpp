#include "dlaggregation_description.h"
#include <cassert>

std::string DLAggregationDescription::getTitle () {
    return "Diffusion limited aggregation";
}

DLAggregationDescription::DLAggregationDescription(DLAggregation* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(2);
    //mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(2);
    mRadioDesc = std::vector<RadioDescription>(3);

    mColorDesc[0] = ColorDescription("Point color", sim->defPointColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());

    mIntDesc[0] = IntDescription("Point count x1000", 1, 20, 5, sim->defPointLimit()/1000);
    mIntDesc[1] = IntDescription("FPS", 0, 1000, 100, sim->defFps());

    std::vector<std::string> shapeMode(2);
    std::vector<std::string> neighbourMode(2);
    std::vector<std::string> coordinateMode(2);

    shapeMode.at(DLAggregation::eCircle) = "Circle";
    shapeMode.at(DLAggregation::eGravity) = "Upward";

    neighbourMode.at(DLAggregation::N4) = "4 sides";
    neighbourMode.at(DLAggregation::N8) = "8 sides";

    coordinateMode.at(DLAggregation::eCart) = "Cartesian";
    coordinateMode.at(DLAggregation::ePolar) = "Polar";

    mRadioDesc[0] = RadioDescription("Shape mode", shapeMode, sim->defShapeMode());
    mRadioDesc[1] = RadioDescription("Neighbour mode", neighbourMode, sim->defNeighbourMode());
    mRadioDesc[2] = RadioDescription("Coordinate mode", coordinateMode, sim->defCoordinateMode());

    mFilePath = "DLA";
}


void DLAggregationDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setPointColor(color);
        break;
    case 1:
        sim->setEmptyColor(color);
        break;
    }
}


enum ShapeMode {
    eCircle, eGravity
};
enum Neighbour {
    N4, N8
};
enum CoordinateMode {
    eCart, ePolar
};


void DLAggregationDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setPointLimit(value*1000);
        break;
    case 1:
        sim->setFps(value);
        break;
    }
}

void DLAggregationDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}


void DLAggregationDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setShapeMode(DLAggregation::ShapeMode (buttonIndex));
        break;
    case 1:
        sim->setNeighbourMode(DLAggregation::Neighbour (buttonIndex));
        break;
    case 2:
        sim->setCoordinateMode(DLAggregation::CoordinateMode (buttonIndex));
        break;
    }

}

