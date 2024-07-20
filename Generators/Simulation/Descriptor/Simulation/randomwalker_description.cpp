#include "randomwalker_description.h"


std::string RandomWalkerDescription::getTitle () {
    return "Random moving particle";
}

RandomWalkerDescription::RandomWalkerDescription(RandomWalker* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(2);
    //mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(3);
    mRadioDesc = std::vector<RadioDescription>(2);

    mColorDesc[0] = ColorDescription("Point color", sim->defPointColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());

    mIntDesc[0] = IntDescription("Point count", 1, 1000, 10, sim->defPointCount());
    mIntDesc[1] = IntDescription("Fill intensity", 1, 255, 1, sim->defSpeed());
    mIntDesc[2] = IntDescription("FPS", 1, 3000, 100, sim->defFps());

    std::vector<std::string> colorMode(3);
    std::vector<std::string> overflowMode(3);

    colorMode.at(RandomWalker::eColored) = "Colored";
    colorMode.at(RandomWalker::eUniform) = "One color";
    colorMode.at(RandomWalker::eRGB) = "RGB";

    overflowMode.at(RandomWalker::eFixed) = "Only brighter";
    overflowMode.at(RandomWalker::eOverflow) = "Repeated";
    overflowMode.at(RandomWalker::eOverwrite) = "Overwrite";

    mRadioDesc[0] = RadioDescription("Color mode", colorMode, sim->defColorMode());
    mRadioDesc[1] = RadioDescription("Overwrite mode", overflowMode, sim->defOverflowMode());

    mFilePath = ("Random walker");
}

void RandomWalkerDescription::changeColor (int index, cv::Vec3b color) {
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

void RandomWalkerDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setPointCount(value);
        break;
    case 1:
        sim->setSpeed(value);
        break;
    case 2:
        sim->setFps(value);
        break;
    }
}

void RandomWalkerDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void RandomWalkerDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setColorMode(RandomWalker::ColorMode (buttonIndex));
        break;
    case 1:
        sim->setOverflowMode(RandomWalker::OverflowMode (buttonIndex));
        break;
    }
}
