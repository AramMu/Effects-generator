#include "simulationwindow.h"
#include <QImage>
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QFile>
#include "Time/timemeasure.h"
#include "Time/sleeper.h"
#include "qtutils.h"
#include "Simulation/Descriptor/Effect/all_effect_descriptions.h"
#include <QApplication>

SimulationWindow::SimulationWindow(const QSize& size, SimulationDescription* desc, QWidget *parent):
    QMainWindow(parent),
    mDefSize(size),
    mDefSizeCv(size.width(), size.height()),
    mDelay(15),
    mDesc(desc),
    mPaused(false)
{
    this->setWindowTitle("Effect window");
    createObjects();
    manageLayout();
    createConnections();
    initProperties();
    resetToDefault();
    /*
    effectVector = QVector<EffectDescription*> (2);
    effectVector[0] = new ContrastDescription();
    effectVector[0]->changeDouble(0, 4);
    effectVector[1] = new GaussianNoiseDescription();
    effectVector[1]->changeInt(0, 100);

    mFrameProcessor->setEffectVector(effectVector);
    */
}

void SimulationWindow::createObjects() {
    mCentralWidget = new QWidget(this);
    mThread = new QThread (this);
    mFrameProcessor = new FrameProcessor(mDesc, mDelay*1000);

    mCentralLayout = new QHBoxLayout();
    mButtonLayout = new QVBoxLayout();
    mImageLayout = new QVBoxLayout();

    mMenuCombo = new QComboBox();



    mColorLayoutWidget = new QWidget();
    mIntLayoutWidget = new QWidget();
    mDoubleLayoutWidget = new QWidget();
    mRadioLayoutWidget = new QWidget();
    mEffectLayoutWidget = new QWidget();
    mHelperLayoutWidget = new QWidget();


    mColorLayout = new QVBoxLayout();
    mIntLayout = new QVBoxLayout();
    mDoubleLayout = new QVBoxLayout();
    mRadioLayout = new QVBoxLayout();
    mEffectLayout = new QVBoxLayout();
    mEffectAddLayout = new QVBoxLayout();
    mEffectVecLayout = new QVBoxLayout();
    mHelperLayout = new QVBoxLayout();

    mFrameView = new FrameView(mDefSize, this);
    mPauseButton = new QPushButton("Pause", this);
    mResumeButton = new QPushButton("Resume", this);
    mRestartButton = new QPushButton("Restart", this);
    mSetDefaultButton = new QPushButton("Reset to default", this);
    mSaveButton = new QPushButton("Save", this);
    mDelayButton = new IntButton(0, "Delay per frame ms", 0, 1000, 1, this);

    mEffectEditLabel = new QLabel ("Current effect to be edited");
    mEffectAddLabel = new QLabel ("Add effects");
    mEffectVecLabel = new QLabel ("Effects to be applied");
    mEffectEdit = new EffectButton(NULL);

    std::vector <ColorDescription> colorDesc = mDesc->getColorDesc();
    mColorButtons = QVector<ColorButton*> (colorDesc.size());
    for (int i = 0; i < mColorButtons.size(); ++i) {
        mColorButtons[i] = new ColorButton (&colorDesc[i], i, this);
    }
    std::vector <IntDescription> intDesc = mDesc->getIntDesc();
    mIntButtons = QVector <IntButton*>(intDesc.size());
    for (int i = 0; i < mIntButtons.size(); ++i) {
        mIntButtons[i] = new IntButton (&intDesc[i], i, this);
    }
    std::vector <DoubleDescription> doubleDesc = mDesc->getDoubleDesc();
    mDoubleButtons = QVector <DoubleButton*>(doubleDesc.size());
    for (int i = 0; i < mDoubleButtons.size(); ++i) {
        mDoubleButtons[i] = new DoubleButton (&doubleDesc[i], i, this);
    }
    std::vector<RadioDescription> radioDesc = mDesc->getRadioDesc();
    mRadioButtons = QVector <RadioButton*>(radioDesc.size());
    for (int i = 0; i < mRadioButtons.size(); ++i) {
        mRadioButtons[i] = new RadioButton (&radioDesc[i], i, this);
    }

    mEffectAddButtons = QVector<PushButton*>(AllEffectDescriptions::getEffectCount());
    for (int i = 0; i < mEffectAddButtons.size(); ++i) {
        mEffectAddButtons[i] = new PushButton(i, QString::fromStdString(AllEffectDescriptions::getTitleAt(i)));
    }

    /*
    mEffectButtons = QVector<EffectButton*>(AllEffectDescriptions::getEffectCount());
    for (int i = 0; i < mEffectButtons.size(); ++i) {
        mEffectButtons[i] = new EffectButton(AllEffectDescriptions::getEffectAt(i), this);
    }
    */
}

void SimulationWindow::manageLayout() {
    this->setCentralWidget(mCentralWidget);
    mCentralWidget->setLayout(mCentralLayout);

    mCentralLayout->addLayout(mButtonLayout);
    mCentralLayout->addLayout(mImageLayout);

    mImageLayout->addWidget(mFrameView);

    mButtonLayout->addWidget(mMenuCombo);
    mButtonLayout->addWidget(mColorLayoutWidget);
    mButtonLayout->addWidget(mIntLayoutWidget);
    mButtonLayout->addWidget(mDoubleLayoutWidget);
    mButtonLayout->addWidget(mRadioLayoutWidget);
    mButtonLayout->addWidget(mEffectLayoutWidget);
    mButtonLayout->addWidget(mHelperLayoutWidget);

    mColorLayoutWidget->setLayout(mColorLayout);
    mIntLayoutWidget->setLayout(mIntLayout);
    mDoubleLayoutWidget->setLayout(mDoubleLayout);
    mRadioLayoutWidget->setLayout(mRadioLayout);
    mEffectLayoutWidget->setLayout(mEffectLayout);
    mHelperLayoutWidget->setLayout(mHelperLayout);

    mHelperLayout->addWidget(mSaveButton);
    mHelperLayout->addWidget(mPauseButton);
    mHelperLayout->addWidget(mResumeButton);
    mHelperLayout->addWidget(mRestartButton);
    mHelperLayout->addWidget(mSetDefaultButton);
    mHelperLayout->addWidget(mDelayButton);



    //std::vector <ColorDescription> colorDesc = mDesc->getColorDesc();
    for (int i = 0; i < mColorButtons.size(); ++i) {
        mColorLayout->addWidget(mColorButtons[i]);
    }
    //std::vector <IntDescription> intDesc = mDesc->getIntDesc();
    for (int i = 0; i < mIntButtons.size(); ++i) {
        mIntLayout->addWidget(mIntButtons[i]);
    }
    //std::vector <DoubleDescription> doubleDesc = mDesc->getDoubleDesc();
    for (int i = 0; i < mDoubleButtons.size(); ++i) {
        mDoubleLayout->addWidget(mDoubleButtons[i]);
    }
    //std::vector<RadioDescription> radioDesc = mDesc->getRadioDesc();
    for (int i = 0; i < mRadioButtons.size(); ++i) {
        mRadioLayout->addWidget(mRadioButtons[i]);
    }

    mEffectEditLabel = new QLabel ("Current effect to be edited");
    mEffectAddLabel = new QLabel ("Add effects");
    mEffectVecLabel = new QLabel ("Effects to be applied");

    mEffectLayout->addWidget(mEffectAddLabel);
    mEffectLayout->addLayout(mEffectAddLayout);
    mEffectLayout->addWidget(mEffectVecLabel);
    mEffectLayout->addLayout(mEffectVecLayout);
    mEffectLayout->addWidget(mEffectEditLabel);
    mEffectLayout->addWidget(mEffectEdit);

    for (int i = 0; i < mEffectAddButtons.size(); ++i) {
        mEffectAddLayout->addWidget(mEffectAddButtons[i]);
    }

    /*
    for (int i = 0; i < mEffectButtons.size(); ++i) {
        mEffectLayout->addWidget(mEffectButtons[i]);
    }
    */
}
void SimulationWindow::createConnections() {
    connect (mSaveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect (mPauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect (mResumeButton, SIGNAL(clicked()), this, SLOT(resume()));
    connect (mRestartButton, SIGNAL(clicked()), this, SLOT(restart()));
    connect (mSetDefaultButton, SIGNAL(clicked()), this, SLOT(resetToDefault()));
    connect (mDelayButton, SIGNAL(intChanged(int,int)), this, SLOT(changeDelay(int,int)));
    connect (this, SIGNAL(saveImage(QString)), mFrameView, SLOT(save(QString)));
    for (int i = 0; i < mColorButtons.size(); ++i) {
        connect (mColorButtons[i], SIGNAL(colorChanged(int,QColor)), this, SLOT(changeColor(int,QColor)));
    }
    for (int i = 0; i < mIntButtons.size(); ++i) {
        connect (mIntButtons[i], SIGNAL(intChanged(int,int)), this, SLOT(changeInt(int,int)));
    }
    for (int i = 0; i < mDoubleButtons.size(); ++i) {
        connect (mDoubleButtons[i], SIGNAL(doubleChanged(int,double)), this, SLOT(changeDouble(int,double)));
    }
    for (int i = 0; i < mRadioButtons.size(); ++i) {
        connect (mRadioButtons[i], SIGNAL(radioChanged(int,int)), this, SLOT(changeRadio(int,int)));
    }

    for (int i = 0; i < mEffectAddButtons.size(); ++i) {
        connect(mEffectAddButtons[i], SIGNAL(pressed(int)), this, SLOT(addEffect(int)));
    }

    mFrameProcessor->moveToThread(mThread);

    connect (mFrameProcessor, SIGNAL(imageCreated(cv::Mat*)), mFrameView, SLOT(setPixmap(cv::Mat*)), Qt::BlockingQueuedConnection);
    //connect (mFrameView, SIGNAL(conversionFinished()), this, SLOT(unBlock()));
    connect (mThread, SIGNAL(started()), mFrameProcessor, SLOT(start()));
    connect (mThread, SIGNAL(finished()), mFrameProcessor, SLOT(finish()));
    connect (mThread, SIGNAL(destroyed()), mFrameProcessor, SLOT(finish()));
}

enum SelectedOption {
    eColor, eInt, eDouble, eRadio, eEffect, eHelper
};

void SimulationWindow::initProperties() {
    mMenuStrings = QStringList();
    for (int i = 0; i < 6; ++i) {
        mMenuStrings.append(QString());
    }
    //mMenuStrings.reserve(4);
    /*
    mMenuStrings.append(QString("Color buttons"));
    mMenuStrings.append(QString("Integer buttons"));
    mMenuStrings.append(QString("Decimal buttons"));
    mMenuStrings.append(QString("Radio buttons"));
    mMenuStrings.append(QString("Effect buttons"));
    */
    mMenuStrings[eColor] = QString("Color buttons");
    mMenuStrings[eInt] = QString("Integer buttons");
    mMenuStrings[eDouble] = QString("Decimal buttons");
    mMenuStrings[eRadio] = QString("Radio buttons");
    mMenuStrings[eEffect] = QString("Effect buttons");
    mMenuStrings[eHelper] = QString("Helper buttons");


    mMenuCombo->addItems(mMenuStrings);
    connect (mMenuCombo, SIGNAL(activated(int)), this, SLOT(changeDisplayOptions(int)));
    mMenuCombo->setCurrentIndex(eHelper);
    changeDisplayOptions(eHelper);
}


SimulationWindow::~SimulationWindow() {
    //mThread->quit();
    mFrameProcessor->finish();
    /*
    if (mFrameProcessor->readyToFinish()) {
        qDebug() << "Successfully finished";
    } else {
        qDebug() << "failed to finish";
    }
*/
    while (!mFrameProcessor->readyToFinish()) {
        mFrameProcessor->finish();
        QApplication::processEvents();
        Sleeper::sleep(100);
        //qDebug() << "waiting";
    }
    //delete mThread;
    //delete mFrameProcessor;
    mThread->quit();
    delete mFrameView;
    delete mPauseButton;
    delete mResumeButton;
    delete mRestartButton;
    delete mSetDefaultButton;
    delete mSaveButton;
    delete mDelayButton;

    for (int i = 0; i < mColorButtons.size(); ++i) {
        delete mColorButtons[i];
    }
    for (int i = 0; i < mIntButtons.size(); ++i) {
        delete mIntButtons[i];
    }
    for (int i = 0; i < mDoubleButtons.size(); ++i) {
        delete mDoubleButtons[i];
    }
    for (int i = 0; i < mRadioButtons.size(); ++i) {
        delete mRadioButtons[i];
    }

    delete mColorLayout;
    delete mIntLayout;
    delete mDoubleLayout;
    delete mRadioLayout;
    delete mHelperLayout;

    delete mButtonLayout;
    delete mImageLayout;
    delete mCentralLayout;

    delete mCentralWidget;
    delete mThread;
    delete mFrameProcessor;
    /*
    for (int i = 0; i < effectVector.size(); ++i) {
        delete effectVector[i];
    }
    */
}




void SimulationWindow::changeDisplayOptions(int index) {
    mIntLayoutWidget->setVisible(false);
    mDoubleLayoutWidget->setVisible(false);
    mColorLayoutWidget->setVisible(false);
    mRadioLayoutWidget->setVisible(false);
    mEffectLayoutWidget->setVisible(false);
    mHelperLayoutWidget->setVisible(false);

    switch (index) {
    case eInt:
        mIntLayoutWidget->setVisible(true);
        break;
    case eDouble:
        mDoubleLayoutWidget->setVisible(true);
        break;
    case eColor:
        mColorLayoutWidget->setVisible(true);
        break;
    case eRadio:
        mRadioLayoutWidget->setVisible(true);
        break;
    case eEffect:
        mEffectLayoutWidget->setVisible(true);
        break;
    case eHelper:
        mHelperLayoutWidget->setVisible(true);
        break;
    }
}


void SimulationWindow::changeColor (int index, const QColor &color) {
    mFrameProcessor->addColorEvent({index, toCvColor(color)});
}
void SimulationWindow::changeInt (int index, int value) {
    mFrameProcessor->addIntEvent({index, value});
}
void SimulationWindow::changeDouble (int index, double value) {
    mFrameProcessor->addDoubleEvent({index, value});
}
void SimulationWindow::changeRadio (int index, int buttonIndex){
    mFrameProcessor->addRadioEvent({index, buttonIndex});
}


void SimulationWindow::addEffect (int index) {
    mFrameProcessor->addEffect(index, -1);
    mEffectVecButtons.push_back(
                new PushButton(mEffectVecButtons.size(), QString::fromStdString(AllEffectDescriptions::getTitleAt(index))));
    mEffectVecLayout->addWidget(mEffectVecButtons.back());
    connect(mEffectVecButtons.back(), SIGNAL(pressed(int)), this, SLOT(changeEffectEdit(int)));
}

void SimulationWindow::changeEffectEdit (int index) {
    mEffectLayout->removeWidget(mEffectEdit);
    delete mEffectEdit;
    qDebug() << "Description pointer value " << mEffectVecButtons[index]->getIndex();
    mEffectEdit = new EffectButton(mFrameProcessor->getEffectDescription(mEffectVecButtons[index]->getIndex()));
    mEffectLayout->addWidget(mEffectEdit);
    update();
}

void SimulationWindow::changeEffectColor (int index, const QColor &color){
    mFrameProcessor->addEffectColorEvent({index, toCvColor(color)});
}
void SimulationWindow::changeEffectInt (int index, int value){
    mFrameProcessor->addEffectIntEvent({index, value});
}
void SimulationWindow::changeEffectDouble (int index, double value){
    mFrameProcessor->addEffectDoubleEvent({index, value});
}
void SimulationWindow::changeEffectRadio (int index, int buttonIndex){
    mFrameProcessor->addEffectRadioEvent({index, buttonIndex});
}




void SimulationWindow::resetToDefault() {
    mFrameProcessor->resetToDefault();

    mDelayButton->setInt(mDelay);
    std::vector <ColorDescription> colorDesc = mDesc->getColorDesc();
    for (int i = 0; i < mColorButtons.size(); ++i) {
        mColorButtons[i]->setColor(toQColor(colorDesc[i].getDefValue()));
    }
    std::vector <IntDescription> intDesc = mDesc->getIntDesc();
    for (int i = 0; i < mIntButtons.size(); ++i) {
        mIntButtons[i]->setInt(intDesc[i].getDefValue());
    }
    std::vector <DoubleDescription> doubleDesc = mDesc->getDoubleDesc();
    for (int i = 0; i < mDoubleButtons.size(); ++i) {
        mDoubleButtons[i]->setDouble(doubleDesc[i].getDefValue());
    }
    std::vector<RadioDescription> radioDesc = mDesc->getRadioDesc();
    for (int i = 0; i < mRadioButtons.size(); ++i) {
        mRadioButtons[i]->setRadio(radioDesc[i].getDefValue());
    }
}
void SimulationWindow::pause() {
    mPaused = true;
    mFrameProcessor->pause();
}
void SimulationWindow::resume() {
    mPaused = false;
    mFrameProcessor->resume();
}
void SimulationWindow::restart() {
    mFrameProcessor->restart();
}
void SimulationWindow::changeDelay(int, int value) {
    mDelay = value;
    mFrameProcessor->setMinimumDelayMicro(mDelay*1000);
}

void SimulationWindow::save() {
    QString gallery("gallery");
    QString path(QString::fromStdString(mDesc->getFilePath()));

    QDir q;
    if (!q.exists(gallery)) {
        if (!q.mkdir(gallery)) {
            return;
        }
    }
    if (!q.exists(gallery + "\\" + path)) {
        if (!q.mkdir(gallery + "\\" + path)) {
            return;
        }
    }
    QString fileName = getNextFreeNumber (gallery + "\\" + path + "\\", ".png");
    emit saveImage(fileName);
}

void SimulationWindow::start() {
    mThread->start();
}
void SimulationWindow::closeEvent(QCloseEvent* event) {
    if (!mFrameProcessor->readyToFinish()) {
        mFrameProcessor->finish();
        QApplication::processEvents();
    }
    emit closed();
}

bool SimulationWindow::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::WindowActivate:
        if (mPaused) {
            pause();
        } else {
            resume();
        }
        return true;
    case QEvent::WindowDeactivate:
    {
        bool tmp = mPaused;
        pause();
        mPaused = tmp;
    }
        return true;
    }
    return QWidget::event(event);
}
