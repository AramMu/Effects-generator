#include "doublebutton.h"
#include <cassert>

#include <QDoubleSpinBox>
#include <QHBoxLayout>

void DoubleButton::construct(double step) {
    assert (mMax >= mMin);
    assert (mIndex >= 0);
    mDoubleSpinBox = new QDoubleSpinBox (this);
    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mLayout->addWidget(mDoubleSpinBox);
    double inf = 1000000;
    mDoubleSpinBox->setRange(-inf, inf);
    mDoubleSpinBox->setSingleStep(step);
    connect (mDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setDouble(double)));
}



DoubleButton::DoubleButton(DoubleDescription *desc, int index, QWidget* parent) :
    QGroupBox(QString::fromStdString(desc->getName()), parent),
    mIndex(index),
    mMin(desc->getMin()),
    mMax(desc->getMax())
{
    construct(desc->getStep());
    mDoubleSpinBox->setValue(desc->getDefValue());
}




DoubleButton::DoubleButton(int index, const QString& name, double min, double max, double step, QWidget* parent) :
    QGroupBox(name, parent),
    mIndex(index),
    mMin(min),
    mMax(max)
{
    construct(step);
}


DoubleButton::~DoubleButton() {
    if (mDoubleSpinBox!=nullptr) delete mDoubleSpinBox;
    mDoubleSpinBox = nullptr;
    if (mLayout!=nullptr) delete mLayout;
    mLayout = nullptr;
}

void DoubleButton::setDouble(double value) {
    if (mValue == value) {
        return;
    }
    mValue = value;
    if (mValue > mMax) {
        mValue = mMax;
    } else if (mValue < mMin) {
        mValue = mMin;
    }

    mDoubleSpinBox->setValue(mValue);
    emit doubleChanged(mIndex, mValue);
}
