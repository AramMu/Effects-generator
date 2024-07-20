#include "flameparabola_description.h"


std::string FlameParabolaDescription::getTitle () {
    return "Flame (candle shaped)";
}

FlameParabolaDescription::FlameParabolaDescription(FlameParabola *sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(3);
    //mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(2);
    mRadioDesc = std::vector<RadioDescription>(3);

    mColorDesc[0] = ColorDescription("Flame color", sim->defFlameColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());
    mColorDesc[2] = ColorDescription("Soot color", sim->defSootColor());

    mIntDesc[0] = IntDescription("Flame count", 1, 20, 1, sim->defFlameCount());
    mIntDesc[1] = IntDescription("Noise", 0, 1000, 10, sim->defNoise());

    std::vector<std::string> colorMode(2);
    std::vector<std::string> mergeMode(2);
    std::vector<std::string> lightMode(2);


    colorMode.at(FlameParabola::eColored) = "Colored";
    colorMode.at(FlameParabola::eUniform) = "One color";

    mergeMode.at(FlameParabola::eIntersecting) = "Intersecting";
    mergeMode.at(FlameParabola::eLayered) = "Layered";

    lightMode.at(FlameParabola::eNormal) = "Normal";
    lightMode.at(FlameParabola::eInverted) = "Inverted";

    mRadioDesc[0] = RadioDescription("Color mode", colorMode, sim->defColorMode());
    mRadioDesc[1] = RadioDescription("Merge mode", mergeMode, sim->defMergeMode());
    mRadioDesc[2] = RadioDescription("Light mode", lightMode, sim->defLightMode());

    mFilePath = "Flame candle";
}


void FlameParabolaDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setFlameColor(color);
        break;
    case 1:
        sim->setEmptyColor(color);
        break;
    case 2:
        sim->setSootColor(color);
        break;
    }
}

void FlameParabolaDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setFlameCount(value);
        break;
    case 1:
        sim->setNoise(value);
        break;
    }
}

void FlameParabolaDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void FlameParabolaDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setColorMode(FlameParabola::ColorMode (buttonIndex));
        break;
    case 1:
        sim->setMergeMode(FlameParabola::MergeMode (buttonIndex));
        break;
    case 2:
        sim->setLightMode(FlameParabola::LightMode (buttonIndex));
        break;
    }
}
