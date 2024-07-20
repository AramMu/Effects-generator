#include "lightningtree_description.h"
#include <cassert>

std::string LightningTreeDescription::getTitle () {
    return "Lightning strike";
}

LightningTreeDescription::LightningTreeDescription(LightningTree* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(2);
    mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(4);
    //mRadioDesc = std::vector<RadioDescription>(2);

    mColorDesc[0] = ColorDescription("Point color", sim->defLineColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());

    mDoubleDesc[0] = DoubleDescription("Voltage", -1, 2, 0.1, sim->defPower());
    mDoubleDesc[1] = DoubleDescription("Strike probability %", 0, 100, 1, sim->defStrikeProb()*100);

    mIntDesc[0] = IntDescription("Point count", 1, 2000, 100, sim->defPointCount());
    mIntDesc[1] = IntDescription("Line thickness", 1, 10, 1, sim->defLineThickness());
    mIntDesc[2] = IntDescription("Light frame count", 1, 10, 1, sim->defLightFrames());
    mIntDesc[3] = IntDescription("Empty frame count", 0, 50, 1, sim->defEmptyFrames());

    mFilePath = ("Lightning");
}



void LightningTreeDescription::changeColor (int index, cv::Vec3b color) {

    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setLineColor(color);
        break;
    case 1:
        sim->setEmptyColor(color);
        break;
    }
}


void LightningTreeDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setPointCount(value);
        break;
    case 1:
        sim->setLineThickness(value);
        break;
    case 2:
        sim->setLightFrames(value);
        break;
    case 3:
        sim->setEmptyFrames(value);
        break;
    }
}

void LightningTreeDescription::changeDouble(int index, double value) {
    assert (index >= 0 && index < mDoubleDesc.size());
    switch (index) {
    case 0:
        sim->setPower(value);
        break;
    case 1:
        sim->setStrikeProb(value/100);
        break;
    }
}


void LightningTreeDescription::changeRadio (int index, int) {
    int DoesntHaveRadioDesc = 0;
    assert(DoesntHaveRadioDesc > 0);
    assert (index >= 0 && index < mRadioDesc.size());
}

