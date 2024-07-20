#include "magnet_description.h"
#include <cassert>

std::string MagnetDescription::getTitle () {
    return "Magnetized particle growing";
}

MagnetDescription::MagnetDescription(Magnet* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(2);
    //mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(2);
    mRadioDesc = std::vector<RadioDescription>(2);

    mColorDesc[0] = ColorDescription("Point color", sim->defPointColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());

    mIntDesc[0] = IntDescription("Point count x1000", 1, 50, 5, sim->defPointLimit());
    mIntDesc[1] = IntDescription("FPS", 0, 1000, 100, sim->defFps());

    std::vector<std::string> shapeMode(4);
    std::vector<std::string> neighbourMode(2);

    shapeMode.at(Magnet::eCircle) = "Circle";
    shapeMode.at(Magnet::eSquare) = "Square";
    shapeMode.at(Magnet::eGravity) = "Upward";
    shapeMode.at(Magnet::eCross) = "Cross shaped";

    neighbourMode.at(Magnet::N4) = "4 sides";
    neighbourMode.at(Magnet::N8) = "8 sides";

    mRadioDesc[0] = RadioDescription("Shape mode", shapeMode, sim->defShapeMode());
    mRadioDesc[1] = RadioDescription("Neighbour mode", neighbourMode, sim->defNeighbourMode());

    mFilePath = ("Electrolysis");
}



void MagnetDescription::changeColor (int index, cv::Vec3b color) {
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

void MagnetDescription::changeInt (int index, int value) {
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

void MagnetDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void MagnetDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setShapeMode(Magnet::ShapeMode (buttonIndex));
        break;
    case 1:
        sim->setNeighbourMode(Magnet::Neighbour (buttonIndex));
        break;
    }
}
