#include "mstree_description.h"


std::string MSTreeDescription::getTitle () {
    return "Wire connection";
}

MSTreeDescription::MSTreeDescription(MSTree* sim) :
    SimulationDescription(sim),
    sim(sim)
{
    mColorDesc = std::vector<ColorDescription>(3);
    //mDoubleDesc = std::vector<DoubleDescription>(0);
    mIntDesc = std::vector<IntDescription>(2);
    mRadioDesc = std::vector<RadioDescription>(1);

    mColorDesc[0] = ColorDescription("Point color", sim->defPointColor());
    mColorDesc[1] = ColorDescription("Line color", sim->defLineColor());
    mColorDesc[2] = ColorDescription("Empty color", sim->defEmptyColor());


    mIntDesc[0] = IntDescription("Point count", 1, 1000, 100, sim->defPointCount());
    mIntDesc[1] = IntDescription("FPS", 1, 50, 1, sim->defFps());

    std::vector<std::string> distanceMode(2);

    distanceMode.at(MSTree::eShort) = "Shortest";
    distanceMode.at(MSTree::eLong) = "Longest";

    mRadioDesc[0] = RadioDescription("Distance mode", distanceMode, sim->defDistanceMode());

    mFilePath = ("Wire connection");
}



void MSTreeDescription::changeColor (int index, cv::Vec3b color) {
    assert (index >= 0 && index < mColorDesc.size());
    switch (index) {
    case 0:
        sim->setPointColor(color);
        break;
    case 1:
        sim->setLineColor(color);
        break;
    case 2:
        sim->setEmptyColor(color);
        break;
    }
}

void MSTreeDescription::changeInt (int index, int value) {
    assert (index >= 0 && index < mIntDesc.size());
    switch (index) {
    case 0:
        sim->setPointCount(value);
        break;
    case 1:
        sim->setFps(value);
        break;
    }
}

void MSTreeDescription::changeDouble(int index, double) {
    int DoesntHaveDoubleDesc = 0;
    assert(DoesntHaveDoubleDesc > 0);
    assert (index >= 0 && index < mDoubleDesc.size());
}

void MSTreeDescription::changeRadio (int index, int buttonIndex) {
    assert (index >= 0 && index < mRadioDesc.size());
    assert (buttonIndex >= 0 && buttonIndex < mRadioDesc[index].count());
    switch (index) {
    case 0:
        sim->setDistanceMode(MSTree::DistanceMode (buttonIndex));
        break;
    }
}
