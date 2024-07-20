#include "smoke_description.h"
#include <cassert>

std::string SmokeDescription::getTitle () {
    return "Smoke";
}

SmokeDescription::SmokeDescription(Smoke* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(2);
    mDoubleDesc = std::vector<DoubleDescription>(3);
    //mIntDesc = std::vector<IntDescription>(3);
    mRadioDesc = std::vector<RadioDescription>(1);

    mColorDesc[0] = ColorDescription("Smoke color", sim->defSmokeColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());

    mDoubleDesc[0] = DoubleDescription("Smoke probability %", 0, 100, 1, sim->defSmokeProb()*100);
    mDoubleDesc[1] = DoubleDescription("X scale factor", 1, 10, 1, sim->defScaleX());
    mDoubleDesc[2] = DoubleDescription("Y scale factor", 1, 10, 1, sim->defScaleY());

    std::vector <std::string> colorMode(3);

    colorMode.at(Smoke::eColored) = "Colored";
    colorMode.at(Smoke::eUniform) = "One color";
    colorMode.at(Smoke::eRGB) = "RGB";

    mRadioDesc[0] = RadioDescription("Color mode", colorMode, sim->defColorMode());

    mFilePath = "Smoke";
}

void SmokeDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setSmokeColor(color);
        break;
    case 1:
        sim->setEmptyColor(color);
        break;
    }
}

void SmokeDescription::changeInt (int index, int) {
    int DoesntHaveIntDesc = 0;
    assert (DoesntHaveIntDesc > 0);
    assert (index >= 0 && index < mIntDesc.size());
}

enum ColorMode {
    eUniform, eRGB, eColored
};

void SmokeDescription::changeDouble(int index, double value) {
    assert (index >= 0 && index < mDoubleDesc.size());
    switch (index) {
    case 0:
        sim->setSmokeProb(value/100);
        break;
    case 1:
        sim->setScaleX(value);
        break;
    case 2:
        sim->setScaleY(value);
        break;
    }
}


void SmokeDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setColorMode(Smoke::ColorMode (buttonIndex));
        break;
    }

}
