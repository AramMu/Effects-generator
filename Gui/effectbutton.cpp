#include "effectbutton.h"

EffectButton::EffectButton(EffectDescription* desc, QWidget* parent) :
    QWidget(parent)
{
    if (desc == NULL) {
        return;
    }
    QVBoxLayout* mCentralLayout = new QVBoxLayout();

    mColorLayout = new QHBoxLayout();
    mIntLayout = new QHBoxLayout();
    mDoubleLayout = new QHBoxLayout();
    mRadioLayout = new QHBoxLayout();

    std::vector <IntDescription> intDesc = desc->getIntDesc();
    std::vector <ColorDescription> colorDesc = desc->getColorDesc();
    std::vector <DoubleDescription> doubleDesc = desc->getDoubleDesc();
    std::vector <RadioDescription> radioDesc = desc->getRadioDesc();

    mIntButtons = QVector <IntButton*> (intDesc.size());
    mDoubleButtons = QVector <DoubleButton*> (doubleDesc.size());
    mColorButtons = QVector <ColorButton*> (colorDesc.size());
    mRadioButtons = QVector <RadioButton*> (radioDesc.size());

    for (int i = 0; i < mIntButtons.size(); ++i) {
        mIntButtons[i] = new IntButton(i, QString::fromStdString(intDesc[i].getName()), intDesc[i].getMin(), intDesc[i].getMax(), intDesc[i].getStep(), this);
    }
    for (int i = 0; i < mDoubleButtons.size(); ++i) {
        mDoubleButtons[i] = new DoubleButton(i, QString::fromStdString(doubleDesc[i].getName()), doubleDesc[i].getMin(), doubleDesc[i].getMax(), doubleDesc[i].getStep(), this);
    }
    for (int i = 0; i < mColorButtons.size(); ++i) {
        mColorButtons[i] = new ColorButton(i, QString::fromStdString(colorDesc[i].getName()), this);
    }
    for (int i = 0; i < mRadioButtons.size(); ++i) {
        mRadioButtons[i] = new RadioButton(i, radioDesc[i].getNames(), QString::fromStdString(radioDesc[i].getName()), this);
    }

    this->setLayout(mCentralLayout);
    mCentralLayout->addLayout(mColorLayout);
    mCentralLayout->addLayout(mIntLayout);
    mCentralLayout->addLayout(mDoubleLayout);
    mCentralLayout->addLayout(mRadioLayout);


    for (int i = 0; i < mIntButtons.size(); ++i) {
        mIntLayout->addWidget(mIntButtons[i]);
    }
    for (int i = 0; i < mDoubleButtons.size(); ++i) {
        mDoubleLayout->addWidget(mDoubleButtons[i]);
    }
    for (int i = 0; i < mColorButtons.size(); ++i) {
        mColorLayout->addWidget(mColorButtons[i]);
    }
    for (int i = 0; i < mRadioButtons.size(); ++i) {
        mRadioLayout->addWidget(mRadioButtons[i]);
    }
}

