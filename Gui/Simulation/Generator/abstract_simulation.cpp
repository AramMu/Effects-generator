#include "abstract_simulation.h"

AbstractSimulation::AbstractSimulation(const cv::Size &size) :
    rng(size.height, size.width),
    mSize(size)
{}

AbstractSimulation::~AbstractSimulation() {}
