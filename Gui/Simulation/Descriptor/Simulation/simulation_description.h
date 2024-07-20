#ifndef SIMULATION_DESCRIPTION_H
#define SIMULATION_DESCRIPTION_H
#include "Simulation/Descriptor/types/description_list.h"
#include "Simulation/Generator/abstract_simulation.h"

#include <vector>

class SimulationDescription {
public:
    SimulationDescription(AbstractSimulation* sim);
    virtual ~SimulationDescription();

    std::vector <ColorDescription> getColorDesc() const;
    std::vector <IntDescription> getIntDesc() const;
    std::vector <DoubleDescription> getDoubleDesc() const;
    std::vector <RadioDescription> getRadioDesc() const;

    std::string getLongDescription () const;
    std::string getFilePath () const;
    AbstractSimulation* getSimulation() const;

    //void setLongDescription (const std::string& str);
    //void setFilePath (const std::string& str);

    virtual void changeColor (int index, cv::Vec3b color)=0;
    virtual void changeInt (int index, int value)=0;
    virtual void changeDouble (int index, double value)=0;
    virtual void changeRadio (int index, int buttonIndex)=0;


protected:
    std::vector <ColorDescription> mColorDesc;
    std::vector <IntDescription> mIntDesc;
    std::vector <DoubleDescription> mDoubleDesc;
    std::vector <RadioDescription> mRadioDesc;

    std::string mFilePath;
    std::string mLongDescription;
private:
    AbstractSimulation* mSim;
};

#endif // SIMULATION_DESCRIPTION_H
