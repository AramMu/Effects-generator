/********************************************************************************
** Form generated from reading UI file 'simulationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONWINDOW_H
#define UI_SIMULATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationWindow
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SimulationWindow)
    {
        if (SimulationWindow->objectName().isEmpty())
            SimulationWindow->setObjectName(QStringLiteral("SimulationWindow"));
        SimulationWindow->resize(800, 600);
        menubar = new QMenuBar(SimulationWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        SimulationWindow->setMenuBar(menubar);
        centralwidget = new QWidget(SimulationWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        SimulationWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SimulationWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SimulationWindow->setStatusBar(statusbar);

        retranslateUi(SimulationWindow);

        QMetaObject::connectSlotsByName(SimulationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SimulationWindow)
    {
        SimulationWindow->setWindowTitle(QApplication::translate("SimulationWindow", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SimulationWindow: public Ui_SimulationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONWINDOW_H
