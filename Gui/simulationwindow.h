#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QTimer>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QAction>
#include <QList>

#include "Simulation/Generator/abstract_simulation.h"
#include "Simulation/Descriptor/Simulation/simulation_description.h"
#include "simulationevents.h"
#include "frameprocessor.h"

#include "frameview.h"
#include "colorbutton.h"
#include "intbutton.h"
#include "doublebutton.h"
#include "radiobutton.h"
#include "pushbutton.h"
#include "effectbutton.h"


#include <QDebug>

class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    SimulationWindow(const QSize& size, SimulationDescription* desc, QWidget *parent = 0);
    ~SimulationWindow();

    void start();
    void closeEvent(QCloseEvent*event);

    bool event(QEvent *event);
signals:
    void closed();
    void saveImage(const QString& fileName);

public slots:
    void changeColor (int index, const QColor &color);
    void changeInt (int index, int value);
    void changeDouble (int index, double value);
    void changeRadio (int index, int buttonIndex);

    void addEffect (int index);
    void changeEffectEdit (int index);
    void changeEffectColor (int index, const QColor &color);
    void changeEffectInt (int index, int value);
    void changeEffectDouble (int index, double value);
    void changeEffectRadio (int index, int buttonIndex);


    void pause();
    void resume();
    void restart();
    void resetToDefault ();
    void changeDelay(int, int value);
    void save();

    void changeDisplayOptions(int val);
private:
    void createObjects();
    void manageLayout();
    void createConnections();
    void initProperties();

    QSize mDefSize;
    cv::Size mDefSizeCv;
    int mDelay;
    SimulationDescription* mDesc;
    QThread *mThread;
    FrameProcessor *mFrameProcessor;    
    QWidget *mCentralWidget;

    QHBoxLayout* mCentralLayout;
    QVBoxLayout* mButtonLayout;
    QVBoxLayout* mImageLayout;

    QComboBox* mMenuCombo;
    QStringList mMenuStrings;

    QVBoxLayout* mColorLayout;
    QVBoxLayout* mIntLayout;
    QVBoxLayout* mDoubleLayout;
    QVBoxLayout* mRadioLayout;
    QVBoxLayout* mEffectLayout;
    QVBoxLayout* mHelperLayout;

    QWidget* mColorLayoutWidget;
    QWidget* mIntLayoutWidget;
    QWidget* mDoubleLayoutWidget;
    QWidget* mRadioLayoutWidget;
    QWidget* mEffectLayoutWidget;
    QWidget* mHelperLayoutWidget;


    QVBoxLayout* mEffectAddLayout;
    QVBoxLayout* mEffectVecLayout;
    QLabel* mEffectAddLabel;
    QLabel* mEffectVecLabel;
    QLabel* mEffectEditLabel;
    EffectButton* mEffectEdit;


    FrameView* mFrameView;
    QPushButton* mPauseButton;
    QPushButton* mResumeButton;
    QPushButton* mRestartButton;
    QPushButton* mSetDefaultButton;
    QPushButton* mSaveButton;
    IntButton* mDelayButton;
    //QComboBox* mSaveOption;


    QVector <ColorButton*> mColorButtons;
    QVector <IntButton*> mIntButtons;
    QVector <DoubleButton*> mDoubleButtons;
    QVector <RadioButton*> mRadioButtons;
    QVector <PushButton*> mEffectAddButtons;
    QVector <PushButton*> mEffectVecButtons;

    //QVector <EffectButton*> mEffectButtons;
    bool mPaused;

    enum SelectedOption {
        eColor, eInt, eDouble, eRadio, eEffect
    };

    //QVector<EffectDescription*> effectVector;
};

#endif // SIMULATIONWINDOW_H
