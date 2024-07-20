#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QVector>
#include <QString>
#include "pushbutton.h"
#include "simulationwindow.h"
//#include "Simulation/Descriptor/Simulation/all_simulation_descriptions.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void itemSelected (int index);
    void hasQuited ();

private:

    QWidget* mCentralWidget;
    QVBoxLayout* mCentralLayout;
    QVector <PushButton*> mButtons;

    QSize mDefSize;
    cv::Size mDefSizeCv;

    SimulationWindow* mSimulationWindow;
    SimulationDescription* mDesc;

    QLabel* mByAramMuradyan;

    QStringList mPluginPaths;
};

#endif // MAINWINDOW_H
