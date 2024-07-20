#include "intbutton.h"
#include <cassert>

void IntButton::construct(int step) {
    assert (mMax >= mMin);
    assert (mIndex >= 0);
    mSpinBox = new QSpinBox (this);
    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mLayout->addWidget(mSpinBox);
    int inf = 1000000;
    mSpinBox->setRange(-inf, inf);
    mSpinBox->setSingleStep(step);
    connect (mSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setInt(int)));
}

IntButton::IntButton(IntDescription *desc, int index, QWidget* parent) :
    QGroupBox(QString::fromStdString(desc->getName()), parent),
    mIndex(index),
    mMin(desc->getMin()),
    mMax(desc->getMax())
{
    construct(desc->getStep());
    mSpinBox->setValue(desc->getDefValue());
}


IntButton::IntButton(int index, const QString& name, int min, int max, int step, QWidget* parent) :
    QGroupBox(name, parent),
    mIndex(index),
    mMin(min),
    mMax(max)
{
    construct(step);
}


IntButton::~IntButton() {
    if (mSpinBox!=nullptr) delete mSpinBox;
    mSpinBox = nullptr;
    if (mLayout!=nullptr) delete mLayout;
    mLayout = nullptr;
}

void IntButton::setInt (int value) {
    if (mValue == value) {
        return;
    }
    mValue = value;
    if (mValue > mMax) {
        mValue = mMax;
    } else if (mValue < mMin) {
        mValue = mMin;
    }

    mSpinBox->setValue(mValue);
    emit intChanged(mIndex, mValue);
}
