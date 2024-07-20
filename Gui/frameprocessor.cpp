#include "frameprocessor.h"
#include "Time/timemeasure.h"
#include "Time/sleeper.h"
#include <QDebug>
#include "qtutils.h"

#include "Simulation/Descriptor/Effect/gaussiannoise_description.h"
#include "Simulation/Descriptor/Effect/contrast_description.h"

FrameProcessor::FrameProcessor(SimulationDescription* desc, long long delay) :
    mSim(desc->getSimulation()),
    mDesc(desc),
    mPaused(false),
    mHasQueueItem(false),
    mRestart(false),
    mDefault(false),
    mFinished(false),
    mDelay(delay),
    mReadyToFinish(true),
    mBlocked(false)
{}

void FrameProcessor::addIntEvent(const IntEvent& item) {
    mIntQueue.push_back(item);
    mHasQueueItem = true;
}
void FrameProcessor::addDoubleEvent(const DoubleEvent& item) {
    mDoubleQueue.push_back(item);
    mHasQueueItem = true;
}
void FrameProcessor::addColorEvent(const ColorEvent& item) {
    mColorQueue.push_back(item);
    mHasQueueItem = true;
}
void FrameProcessor::addRadioEvent(const RadioEvent& item) {
    mRadioQueue.push_back(item);
    mHasQueueItem = true;
}

void FrameProcessor::resume () {
    mPaused = false;
}
void FrameProcessor::pause () {
    mPaused = true;
}
void FrameProcessor::restart () {
    mRestart = true;
}
void FrameProcessor::resetToDefault() {
    mDefault = true;
}
void FrameProcessor::start () {
    mReadyToFinish = false;
    process();
}
void FrameProcessor::finish () {
    mFinished = true;
}

void FrameProcessor::setMinimumDelayMicro (long long delay) {
    mDelay = delay;
}

void FrameProcessor::setEffectVector (const QVector<EffectDescription*>& vec) {
    mEffectVector = vec;
}

void FrameProcessor::process() {
    while (!mFinished) {
        while (! (mFinished || !mPaused || mHasQueueItem || mRestart || mDefault)) {
            Sleeper::sleep(100);
        }
        if (mHasQueueItem) {
            mHasQueueItem = false;
            for (int i = 0; i < mIntQueue.size(); ++i) {
                mDesc->changeInt(mIntQueue[i].index, mIntQueue[i].value);
            }
            for (int i = 0; i < mDoubleQueue.size(); ++i) {
                mDesc->changeDouble(mDoubleQueue[i].index, mDoubleQueue[i].value);
            }
            for (int i = 0; i < mRadioQueue.size(); ++i) {
                mDesc->changeRadio(mRadioQueue[i].index, mRadioQueue[i].buttonIndex);
            }
            for (int i = 0; i < mColorQueue.size(); ++i) {
                mDesc->changeColor(mColorQueue[i].index, swapCvColor(mColorQueue[i].color));
            }
            mIntQueue.clear();
            mDoubleQueue.clear();
            mRadioQueue.clear();
            mColorQueue.clear();
        }

        if (mDefault) {
            mDefault = false;
            mSim->resetToDefault();
            std::vector <ColorDescription> col = mDesc->getColorDesc();
            for (int i = 0; i < col.size(); ++i) {
                mDesc->changeColor(i, swapCvColor(col[i].getDefValue()));
            }
        }

        if (mRestart) {
            mRestart = false;
            mPaused = false;
            mSim->restart();
        }

        if (mSim->hasNextFrame()) {
            TimeMeasure tm;
            tm.start();
            cv::Mat cvMat = mSim->getNextFrame();
            for (int i = 0; i < mEffectVector.size(); ++i) {
                mEffectVector[i]->apply(cvMat, cvMat);
            }

            tm.finish();
            long long tmp = tm.getDifMicro();
            qDebug() << "Delay is " << tmp;
            if (tmp < mDelay) {
                Sleeper::sleepMicro(mDelay - tmp);
            }

            emit imageCreated(&cvMat);
        } else {
            mPaused = true;
        }
    }
    mReadyToFinish = true;
}

bool FrameProcessor::readyToFinish() {
    return mReadyToFinish;
}
