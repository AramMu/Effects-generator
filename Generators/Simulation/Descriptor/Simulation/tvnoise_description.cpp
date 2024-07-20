#include "tvnoise_description.h"
#include <cassert>

std::string TVNoiseDescription::getTitle () {
    return "TV Noise";
}

TVNoiseDescription::TVNoiseDescription(TVNoise* sim) :
    SimulationDescription(sim),
    sim(sim)
{

    mColorDesc = std::vector<ColorDescription>(1);
    //mDoubleDesc = std::vector<DoubleDescription>(0);
    //mIntDesc = std::vector<IntDescription>(0);
    mRadioDesc = std::vector<RadioDescription>(1);

    mColorDesc[0] = ColorDescription("Color", sim->defColor());

    std::vector<std::string> colorMode(2);

    colorMode.at(TVNoise::eColored) = "Colored";
    colorMode.at(TVNoise::eUniform) = "One color";

    mRadioDesc[0] = RadioDescription("Color mode", colorMode, sim->defColorMode());

    mFilePath = ("TV noise");
}



void TVNoiseDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setColor(color);
        break;
    }
}

void TVNoiseDescription::changeInt (int index, int) {
    int DoesntHaveIntDesc = 0;
    assert(DoesntHaveIntDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void TVNoiseDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void TVNoiseDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setColorMode(TVNoise::ColorMode (buttonIndex));
        break;
    }
}
