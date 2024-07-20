#include "pixellightningdescription.h"
#include <cassert>

std::string PixelLightningDescription::getTitle () {
    return "Pixelated lightning";
}

PixelLightningDescription::PixelLightningDescription(PixelLightning* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc.resize(2);
    mIntDesc.resize(2);
    mRadioDesc.resize(2);
    mColorDesc[0] = ColorDescription("Point color", sim->defPointColor());
    mColorDesc[1] = ColorDescription("Background color", sim->defEmptyColor());
    mIntDesc[0] = IntDescription("FPS", 1, 10000, 100, sim->defFps());
    mIntDesc[1] = IntDescription("Point limit", 1, 10000000, 1000, sim->defPointLimit());

    std::vector<std::string> shapeMode(2);
    shapeMode[PixelLightning::ShapeMode::eCircle] = "Circle";
    shapeMode[PixelLightning::ShapeMode::eGravity] = "Upward";

    std::vector<std::string> neighbour(2);
    neighbour[PixelLightning::Neighbour::N4] = "4 sides";
    neighbour[PixelLightning::Neighbour::N8] = "8 sides";

    mRadioDesc[0] = RadioDescription("Shape mode", shapeMode, sim->defShapeMode());
    mRadioDesc[1] = RadioDescription("Sides", neighbour, sim->defNeighbourMode());
    mFilePath = ("Pixeled lightning");
}


void PixelLightningDescription::changeColor (int index, cv::Vec3b color) {
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


void PixelLightningDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setFps(value);
        break;
    case 1:
        sim->setPointLimit(value);
        break;
    }
}

void PixelLightningDescription::changeDouble(int index, double value) {
    assert (index >= 0 && index < mDoubleDesc.size());
}


void PixelLightningDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());

    switch (index) {
    case 0:
        sim->setShapeMode(PixelLightning::ShapeMode(buttonIndex));
        break;
    case 1:
        sim->setNeighbourMode(PixelLightning::Neighbour(buttonIndex));
        break;
    }
}

