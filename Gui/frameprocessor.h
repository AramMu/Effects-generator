#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H
#include <QObject>
#include <QPixmap>
#include <QVector>

#include "simulationevents.h"
#include "Simulation/Descriptor/Simulation/simulation_description.h"
#include "Simulation/Descriptor/Effect/effect_description.h"

class FrameProcessor : public QObject {
    Q_OBJECT
public:
    FrameProcessor(SimulationDescription* desc, long long delay=0);

    void addIntEvent(const IntEvent& item);
    void addDoubleEvent(const DoubleEvent& item);
    void addColorEvent(const ColorEvent& item);
    void addRadioEvent(const RadioEvent& item);

    void addEffect (int index, int pos) {
        return;
    }
    EffectDescription* getEffectDescription(int index) {
        return NULL;
    }
    void addEffectIntEvent(const IntEvent& item) {}
    void addEffectDoubleEvent(const DoubleEvent& item) {}
    void addEffectColorEvent(const ColorEvent& item) {}
    void addEffectRadioEvent(const RadioEvent& item) {}

    void setMinimumDelayMicro (long long delay);

    void setEffectVector (const QVector<EffectDescription*>& vec);

    bool readyToFinish ();
public slots:
    void resume ();
    void pause ();
    void restart ();
    void resetToDefault();

    void start ();
    void finish ();

signals:
    void imageCreated (cv::Mat* cvMat);

private:
    void process();
    AbstractSimulation* mSim;
    SimulationDescription* mDesc;
    volatile bool mPaused;
    volatile bool mBlocked;
    volatile bool mHasQueueItem;
    volatile bool mRestart;
    volatile bool mDefault;
    volatile bool mFinished;
    QVector <ColorEvent> mColorQueue;
    QVector <IntEvent> mIntQueue;
    QVector <DoubleEvent> mDoubleQueue;
    QVector <RadioEvent> mRadioQueue;

    QVector <EffectDescription*> mEffectVector;

    volatile long long mDelay;
    volatile bool mReadyToFinish;
};

#endif // FRAMEPROCESSOR_H
