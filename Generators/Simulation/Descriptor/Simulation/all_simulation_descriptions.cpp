#include "all_simulation_descriptions.h"

#include "distancecrystal_description.h"
#include "dlaggregation_description.h"
#include "flameblaze_description.h"
#include "flameparabola_description.h"
#include "flametongue_description.h"
#include "forestfire_description.h"
#include "lightningtree_description.h"
#include "magnet_description.h"
#include "mstree_description.h"
#include "plasma_description.h"
#include "randomwalker_description.h"
#include "smoke_description.h"
#include "tvnoise_description.h"
#include "voronoidiagram_description.h"

#include "pixellightningdescription.h"


enum SimulationName {
    eForestFire,
    eDistanceCrystal,
    eDLAggregation,
    eMagnet,
    eLightningTree,
    ePlasma,
    eFlameParabola,
    eFlameTongue,
    eSmoke,
    eMSTree,
    eRandomWalker,
    eVoronoiDiagram,
    eTVNoise,

    ePixelLightning
};

SimulationDescription* AllSimulationDescriptions::getSimulationAt (int index, const cv::Size &size) {
    SimulationDescription* res;
    switch (index) {
    case eForestFire:
    {
        ForestFire* sim = new ForestFire(size);
        res = new ForestFireDescription(sim);
        break;
    }
    case eDistanceCrystal:
    {
        DistanceCrystal* sim = new DistanceCrystal(size);
        res = new DistanceCrystalDescription(sim);
        break;
    }
    case eDLAggregation:
    {
        DLAggregation* sim = new DLAggregation(size);
        res = new DLAggregationDescription(sim);
        break;
    }
    case eMagnet:
    {
        Magnet* sim = new Magnet(size);
        res = new MagnetDescription(sim);
        break;
    }
    case eLightningTree:
    {
        LightningTree* sim = new LightningTree(size);
        res = new LightningTreeDescription(sim);
        break;
    }
    case ePlasma:
    {
        Plasma* sim = new Plasma(size);
        res = new PlasmaDescription(sim);
        break;
    }
    case eFlameParabola:
    {
        FlameParabola* sim = new FlameParabola(size);
        res = new FlameParabolaDescription(sim);
        break;
    }
    case eFlameTongue:
    {
        FlameTongue* sim = new FlameTongue(size);
        res = new FlameTongueDescription(sim);
        break;
    }
    case eSmoke:
    {
        Smoke* sim = new Smoke(size);
        res = new SmokeDescription(sim);
        break;
    }
    case eMSTree:
    {
        MSTree* sim = new MSTree(size);
        res = new MSTreeDescription(sim);
        break;
    }
    case eRandomWalker:
    {
        RandomWalker* sim = new RandomWalker(size);
        res = new RandomWalkerDescription(sim);
        break;
    }
    case eVoronoiDiagram:
    {
        VoronoiDiagram* sim = new VoronoiDiagram(size);
        res = new VoronoiDiagramDescription(sim);
        break;
    }
    case eTVNoise:
    {
        TVNoise* sim = new TVNoise(size);
        res = new TVNoiseDescription(sim);
        break;
    }
    case ePixelLightning:
    {
        PixelLightning* sim = new PixelLightning(size);
        res = new PixelLightningDescription(sim);
        break;
    }

    default:
        exit(-1);
    }
    return res;
}

/*
std::pair <AbstractSimulation*, SimulationDescription*> AllDescriptions::getSimulationAt (int index, const cv::Size &size) {
    std::pair <AbstractSimulation*, SimulationDescription*> res;
    switch (index) {
    case eForestFire:
    {
        ForestFire* sim = new ForestFire(size);
        res.first = sim;
        res.second = new ForestFireDescription(sim);
        break;
    }
    case eDistanceCrystal:
    {
        DistanceCrystal* sim = new DistanceCrystal(size);
        res.first = sim;
        res.second = new DistanceCrystalDescription(sim);
        break;
    }
    case eDLAggregation:
    {
        DLAggregation* sim = new DLAggregation(size);
        res.first = sim;
        res.second = new DLAggregationDescription(sim);
        break;
    }
    case eMagnet:
    {
        Magnet* sim = new Magnet(size);
        res.first = sim;
        res.second = new MagnetDescription(sim);
        break;
    }
    case eLightningTree:
    {
        LightningTree* sim = new LightningTree(size);
        res.first = sim;
        res.second = new LightningTreeDescription(sim);
        break;
    }
    case ePlasma:
    {
        Plasma* sim = new Plasma(size);
        res.first = sim;
        res.second = new PlasmaDescription(sim);
        break;
    }
    case eFlameParabola:
    {
        FlameParabola* sim = new FlameParabola(size);
        res.first = sim;
        res.second = new FlameParabolaDescription(sim);
        break;
    }
    case eFlameTongue:
    {
        FlameTongue* sim = new FlameTongue(size);
        res.first = sim;
        res.second = new FlameTongueDescription(sim);
        break;
    }
    case eSmoke:
    {
        Smoke* sim = new Smoke(size);
        res.first = sim;
        res.second = new SmokeDescription(sim);
        break;
    }
    case eMSTree:
    {
        MSTree* sim = new MSTree(size);
        res.first = sim;
        res.second = new MSTreeDescription(sim);
        break;
    }
    case eRandomWalker:
    {
        RandomWalker* sim = new RandomWalker(size);
        res.first = sim;
        res.second = new RandomWalkerDescription(sim);
        break;
    }
    case eVoronoiDiagram:
    {
        VoronoiDiagram* sim = new VoronoiDiagram(size);
        res.first = sim;
        res.second = new VoronoiDiagramDescription(sim);
        break;
    }
    case eTVNoise:
    {
        TVNoise* sim = new TVNoise(size);
        res.first = sim;
        res.second = new TVNoiseDescription(sim);
        break;
    }

    default:
        exit(-1);
    }
    return res;
}
*/



int AllSimulationDescriptions::getSimulationCount() {
    return 14;
}


std::string AllSimulationDescriptions::getTitleAt(int index) {
    switch (index) {
    case eDistanceCrystal:
        return DistanceCrystalDescription::getTitle();
    case eDLAggregation:
        return DLAggregationDescription::getTitle();
    case eFlameParabola:
        return FlameParabolaDescription::getTitle();
    case eFlameTongue:
        return FlameTongueDescription::getTitle();
    case eForestFire:
        return ForestFireDescription::getTitle();
    case eLightningTree:
        return LightningTreeDescription::getTitle();
    case eMagnet:
        return MagnetDescription::getTitle();
    case eMSTree:
        return MSTreeDescription::getTitle();
    case ePlasma:
        return PlasmaDescription::getTitle();
    case eRandomWalker:
        return RandomWalkerDescription::getTitle();
    case eSmoke:
        return SmokeDescription::getTitle();
    case eTVNoise:
        return TVNoiseDescription::getTitle();
    case eVoronoiDiagram:
        return VoronoiDiagramDescription::getTitle();

    case ePixelLightning:
        return PixelLightningDescription::getTitle();
    default:
        exit(-1);
    }
}

