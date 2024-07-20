#include "distancecrystal_description.h"


std::string DistanceCrystalDescription::getTitle () {
    return "Crystal growth";
}

DistanceCrystalDescription::DistanceCrystalDescription(DistanceCrystal* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(2);
    //mDoubleDesc = std::vector<DoubleDescription>(2);
    mIntDesc = std::vector<IntDescription>(3);
    mRadioDesc = std::vector<RadioDescription>(2);

    mColorDesc[0] = ColorDescription("Line color", sim->defLineColor());
    mColorDesc[1] = ColorDescription("Empty color", sim->defEmptyColor());

    mIntDesc[0] = IntDescription("Point count", 1, 1000, 100, sim->defPointCount());
    mIntDesc[1] = IntDescription("Site count", 1, 30, 1, sim->defSiteCount());
    mIntDesc[2] = IntDescription("FPS", 0, 10, 1, sim->defFps());

    std::vector<std::string> colorMode(3);
    std::vector<std::string> startMode(3);

    colorMode.at(DistanceCrystal::eColored) = "Colored";
    colorMode.at(DistanceCrystal::eUniform) = "One color";
    colorMode.at(DistanceCrystal::eRGB) = "RGB";

    startMode.at(DistanceCrystal::eCenter) = "Centered";
    startMode.at(DistanceCrystal::eButtom) = "Upward";
    startMode.at(DistanceCrystal::eRandom) = "Random";

    mRadioDesc[0] = RadioDescription("Color mode", colorMode, sim->defColorMode());
    mRadioDesc[1] = RadioDescription("Start mode", startMode, sim->defStartMode());

    mFilePath = "Crystal growth";
}



void DistanceCrystalDescription::changeColor (int index, cv::Vec3b color) {
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

void DistanceCrystalDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setPointCount(value);
        break;
    case 1:
        sim->setSiteCount(value);
        break;
    case 2:
        sim->setFps(value);
        break;
    }
}

void DistanceCrystalDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void DistanceCrystalDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setColorMode(DistanceCrystal::ColorMode (buttonIndex));
        break;
    case 1:
        sim->setStartMode(DistanceCrystal::StartMode (buttonIndex));
        break;
    }
}



