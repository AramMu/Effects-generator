#include "radiobutton.h"


RadioButton::RadioButton(RadioDescription* desc, int index, QWidget* parent) :
    QGroupBox(QString::fromStdString(desc->getName()), parent),
    mIndex(index)
{
    mLayout = new QHBoxLayout ();
    this->setLayout(mLayout);
    std::vector <std::string> names = desc->getNames();
    int count = names.size();
    mRadios = QVector <IndexedRadio*>(count);
    for (int i = 0; i < mRadios.size(); ++i) {
        mRadios[i] = new IndexedRadio(i);
        mRadios[i]->setText (QString::fromStdString(names[i]));
        mLayout->addWidget(mRadios[i]);
        connect (mRadios[i], SIGNAL(radioChecked(int)), this, SLOT(setRadio(int)));
    }
    this->setRadio(desc->getCurValue());
}


RadioButton::RadioButton(int index, const std::vector<std::string>& names, const QString &text, QWidget *parent) :
    QGroupBox(text, parent),
    mIndex(index)
{
    mLayout = new QHBoxLayout ();
    this->setLayout(mLayout);
    int count = names.size();
    mRadios = QVector <IndexedRadio*>(count);
    for (int i = 0; i < mRadios.size(); ++i) {
        mRadios[i] = new IndexedRadio(i);
        mRadios[i]->setText (QString::fromStdString(names[i]));
        mLayout->addWidget(mRadios[i]);
        connect (mRadios[i], SIGNAL(radioChecked(int)), this, SLOT(setRadio(int)));
    }
}

RadioButton::~RadioButton() {
    for (int i = 0; i < mRadios.size(); ++i) {
        if (mRadios[i] != nullptr) delete mRadios[i];
        mRadios[i] = nullptr;
    }
}

void RadioButton::setRadio (int buttonIndex) {
    if (!mRadios[buttonIndex]->isChecked()) {
        mRadios[buttonIndex]->setChecked(true);
    } else {
        emit radioChanged(mIndex, buttonIndex);
    }
}


IndexedRadio::IndexedRadio (int index, QWidget* parent) :
    QRadioButton(parent),
    mIndex(index)
{
    connect(this, SIGNAL(clicked(bool)), this, SLOT(radioCheckedSlot(bool)));
}

void IndexedRadio::radioCheckedSlot (bool isChecked) {
    if (isChecked) {
        emit radioChecked(mIndex);
    }
}
