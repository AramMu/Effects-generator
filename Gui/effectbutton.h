#ifndef EFFECTBUTTON_H
#define EFFECTBUTTON_H

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Simulation/Descriptor/Effect/effect_description.h"

#include "intbutton.h"
#include "doublebutton.h"
#include "radiobutton.h"
#include "colorbutton.h"


class EffectButton : public QWidget {
    Q_OBJECT

public:
    EffectButton(EffectDescription* desc, QWidget *parent = 0);
private:
    QVBoxLayout* mCentralLayout;

    QHBoxLayout* mColorLayout;
    QHBoxLayout* mIntLayout;
    QHBoxLayout* mDoubleLayout;
    QHBoxLayout* mRadioLayout;

    QVector <ColorButton*> mColorButtons;
    QVector <IntButton*> mIntButtons;
    QVector <DoubleButton*> mDoubleButtons;
    QVector <RadioButton*> mRadioButtons;
};

#endif // EFFECTBUTTON_H
