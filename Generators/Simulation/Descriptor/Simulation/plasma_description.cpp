#include "plasma_description.h"


std::string PlasmaDescription::getTitle () {
    return "Plasma";
}

PlasmaDescription::PlasmaDescription(Plasma* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(2);
    mDoubleDesc = std::vector<DoubleDescription>(1);
    //mIntDesc = std::vector<IntDescription>(2);
    //mRadioDesc = std::vector<RadioDescription>(2);

    mColorDesc[0] = ColorDescription("Empty color", sim->defEmptyColor());
    mColorDesc[1] = ColorDescription("Point color", sim->defUsedColor());

    mDoubleDesc[0] = DoubleDescription("Branching probability %", 0, 100, 1, sim->defBranchProb()*100);

    mFilePath = ("Plasma");
}




void PlasmaDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setEmptyColor(color);
        break;
    case 1:
        sim->setUsedColor(color);
        break;
    }

}

void PlasmaDescription::changeInt (int index, int) {
    int DoesntHaveIntDesc = 0;
    assert(DoesntHaveIntDesc > 0);
    assert (index >= 0 && index < mIntDesc.size());
}

void PlasmaDescription::changeDouble(int index, double value) {
    assert (index >= 0 && index < mDoubleDesc.size());
    switch (index) {
    case 0:
        sim->setBranchProb(value/100);
        break;
    }
}

void PlasmaDescription::changeRadio (int index, int) {
    int DoesntHaveRadioDesc = 0;
    assert(DoesntHaveRadioDesc > 0);
    assert (index >= 0 && index < mRadioDesc.size());
}
