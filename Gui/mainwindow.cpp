#include "mainwindow.h"
#include <QDebug>
#include <QLibrary>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mCentralWidget(new QWidget(this)),
    mCentralLayout(new QVBoxLayout()),
    mDefSize(500,500),
    mSimulationWindow(NULL),
    mDesc(NULL)
{
    mByAramMuradyan = new QLabel ("By Aram Muradyan");
    mDefSizeCv = cv::Size(mDefSize.width(), mDefSize.height());
    this->setWindowTitle("Main menu");
    mCentralLayout->addWidget(mByAramMuradyan);

    mPluginPaths.append("Plugins/generators.dll");
    QLibrary lib(mPluginPaths[0]);
    if (!lib.load()) {
        qDebug() << "Can't load plugin";
        exit(-1);
    }
    //mButtons = QVector<PushButton*>(AllSimulationDescriptions::getSimulationCount());

    typedef int (*GetSimulationCount)(void);
    typedef void(*GetTitleAt) (int,std::string&);

    GetSimulationCount fGetSimulationCount = (GetSimulationCount) lib.resolve("getSimulationCount");
    GetTitleAt fGetTitleAt = (GetTitleAt) lib.resolve("getTitleAt");
    if (!fGetSimulationCount || !fGetTitleAt) {
        qDebug() << "Can't resolve symbols";
        exit(-1);
    }
    mButtons = QVector<PushButton*>(fGetSimulationCount());
    for (int i = 0; i < mButtons.size(); ++i) {
        mButtons[i] = new PushButton(i);
        std::string name;
        fGetTitleAt(i, name);
        //mButtons[i]->setText(QString::fromStdString(AllSimulationDescriptions::getTitleAt(i)));
        mButtons[i]->setText(QString::fromStdString(name));
        mCentralLayout->addWidget(mButtons[i]);
        connect (mButtons[i], SIGNAL (pressed(int)), this, SLOT(itemSelected(int)));
    }

    mCentralWidget->setLayout(mCentralLayout);
    this->setCentralWidget(mCentralWidget);
}

MainWindow::~MainWindow() {
    for (int i = 0; i < mButtons.size(); ++i) {
        delete mButtons[i];
    }
    delete mCentralLayout;
    delete mCentralWidget;
}

void MainWindow::itemSelected (int index) {
    this->setVisible(false);

    QLibrary lib(mPluginPaths[0]);
    if (!lib.load()) {
        qDebug() << "Can't load plugin";
        exit(-1);
    }
    typedef SimulationDescription* (*GetSimulationAt)(int, const cv::Size&);

    GetSimulationAt fGetSimulationAt = (GetSimulationAt) lib.resolve("getSimulationAt");
    if (!fGetSimulationAt) {
        qDebug() << "Can't resolve symbols";
        exit(-1);
    }

    //mDesc = AllSimulationDescriptions::getSimulationAt(index, mDefSizeCv);
    mDesc = fGetSimulationAt(index, mDefSizeCv);
    mSimulationWindow = new SimulationWindow(mDefSize, mDesc);

    mSimulationWindow->show();
    connect (mSimulationWindow, SIGNAL(closed()), this, SLOT(hasQuited()));
    mSimulationWindow->start();
}

void MainWindow::hasQuited () {
    assert (mSimulationWindow != NULL);
    assert (mDesc != NULL);
    if (mSimulationWindow != NULL) {
        delete mSimulationWindow;
        mSimulationWindow = NULL;
    }
    if (mDesc != NULL) {
        if (mDesc->getSimulation() != NULL) {
            delete mDesc->getSimulation();
        }
        delete mDesc;
        mDesc = NULL;
    }
    this->setVisible(true);
}




