#include "colorbutton.h"
//#include <QDebug>
#include <QColorDialog>
#include <QPushButton>
#include <QHBoxLayout>
//#include <QPalette>
#include <cassert>
#include "qtutils.h"

void ColorButton::construct () {
    assert (mIndex >= 0);
    mPushButton = new QPushButton (this);
    mLayout = new QHBoxLayout();
    mDialog = new QColorDialog(this);
    this->setLayout(mLayout);
    mLayout->addWidget(mPushButton);

    connect(mDialog, SIGNAL(colorSelected(QColor)), this, SLOT(setColor(QColor)));
    connect(mPushButton, SIGNAL(clicked()), mDialog, SLOT(show()));
}

ColorButton::ColorButton(ColorDescription* desc, int index, QWidget* parent) :
    QGroupBox(QString::fromStdString(desc->getName()), parent),
    mIndex(index)
{
    construct();
    this->setColor(QColor (toQColor(swapCvColor(desc->getCurValue()))));
}


ColorButton::ColorButton(int index, const QString& name, QWidget* parent) :
    QGroupBox(name, parent),
    mIndex(index)
{
    construct();
}

ColorButton::~ColorButton() {
    if(mDialog != nullptr) delete mDialog;
    mDialog = nullptr;
    if(mPushButton != nullptr) delete mPushButton;
    mPushButton = nullptr;
    if(mLayout != nullptr) delete mLayout;
    mLayout = nullptr;
}

void ColorButton::setColor (const QColor& color) {
    mColor = color;
    QString s("border: 1px solid black; background: " + mColor.name() + ";");
    mPushButton->setStyleSheet(s);
    emit colorChanged(mIndex, mColor);
}

