#include "flameblaze_description.h"


std::string FlameBlazeDescription::getTitle () {
    return "Flame (blaze)";
}

FlameBlazeDescription::FlameBlazeDescription(FlameBlaze *sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(3);
    //mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(2);
    mRadioDesc = std::vector<RadioDescription>(4);

    mColorDesc[0] = ColorDescription("Flame color", sim->defFlameColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());
    mColorDesc[2] = ColorDescription("Soot color", sim->defSootColor());

    mIntDesc[0] = IntDescription("Flame count", 1, 100, 1, sim->defFlameCount());
    mIntDesc[1] = IntDescription("Noise", 0, 1000, 10, sim->defNoise());

    std::vector<std::string> mergeMode(2);
    std::vector<std::string> fillMode(2);
    std::vector<std::string> colorMode(2);
    std::vector<std::string> lightMode(2);

    mergeMode.at(FlameBlaze::eDarker) = "Intersecting";
    mergeMode.at(FlameBlaze::eLayered) = "Layered";

    fillMode.at(FlameBlaze::eGradient) = "Gradient";
    fillMode.at(FlameBlaze::eGradientLine) = "Gradient (X-only)";

    colorMode.at(FlameBlaze::eColored) = "Colored";
    colorMode.at(FlameBlaze::eUniform) = "One color";

    lightMode.at(FlameBlaze::eNormal) = "Normal";
    lightMode.at(FlameBlaze::eInverted) = "Inverted";

    mRadioDesc[0] = RadioDescription("Merge mode", mergeMode, sim->defMergeMode());
    mRadioDesc[1] = RadioDescription("Fill mode", fillMode, sim->defFillMode());
    mRadioDesc[2] = RadioDescription("Color mode", colorMode, sim->defColorMode());
    mRadioDesc[3] = RadioDescription("Light mode", lightMode, sim->defLightMode());

    mFilePath = ("Flame blaze");
}

void FlameBlazeDescription::changeColor (int index, cv::Vec3b color) {
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


void FlameBlazeDescription::changeInt (int index, int value) {
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

void FlameBlazeDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void FlameBlazeDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());    
    switch (index) {
    case 0:
        sim->setMergeMode(FlameBlaze::MergeMode (buttonIndex));
        break;
    case 1:
        sim->setFillMode(FlameBlaze::FillMode (buttonIndex));
        break;
    case 2:
        sim->setColorMode(FlameBlaze::ColorMode (buttonIndex));
        break;
    case 3:
        sim->setLightMode(FlameBlaze::LightMode (buttonIndex));
        break;
    }

}
