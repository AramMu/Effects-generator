#include "forestfire_description.h"


std::string ForestFireDescription::getTitle () {
    return "Forest fire spread";
}

ForestFireDescription::ForestFireDescription(ForestFire *sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(3);
    mDoubleDesc = std::vector<DoubleDescription>(2);
    //mIntDesc = std::vector<IntDescription>(2);
    mColorDesc[0] = ColorDescription("Background color", sim->defEmptyColor());
    mColorDesc[1] = ColorDescription("Tree color", sim->defTreeColor());
    mColorDesc[2] = ColorDescription("Fire color", sim->defFireColor());
    mDoubleDesc[0] = DoubleDescription("Tree growth rate %", 0, 100, 0.01, sim->defTreeProb()*100);
    mDoubleDesc[1] = DoubleDescription("Fire ignition rate %", 0, 100, 0.01, sim->defFireProb()*100);

    mFilePath = ("Forest fire");
}

void ForestFireDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setEmptyColor(color);
        break;
    case 1:
        sim->setTreeColor(color);
        break;
    case 2:
        sim->setFireColor(color);
        break;
    }
}

void ForestFireDescription::changeInt (int index, int) {
    int DoesntHaveIntDesc = 0;
    assert(DoesntHaveIntDesc > 0);
    assert (index >= 0 && index < mIntDesc.size());
}

void ForestFireDescription::changeDouble(int index, double value) {
    assert (index >= 0 && index < mDoubleDesc.size());
    assert (value >= mDoubleDesc[index].getMin() && value <= mDoubleDesc[index].getMax());
    switch (index) {
    case 0:
        sim->setTreeProb(value/100);
        break;
    case 1:
        sim->setFireProb(value/100);
        break;
    }
}

void ForestFireDescription::changeRadio (int index, int buttonIndex) {
    int DoesntHaveRadioDesc = 0;
    assert(DoesntHaveRadioDesc > 0);
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
}
