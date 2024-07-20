#ifndef INTBUTTON_H
#define INTBUTTON_H
#include <QSpinBox>
#include <QGroupBox>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "Simulation/Descriptor/types/int_description.h"


class IntButton : public QGroupBox {
    Q_OBJECT
public:
    IntButton(int index, const QString& name, int min, int max, int step, QWidget* parent=0);
    IntButton(IntDescription* desc, int index, QWidget* parent=0);
    ~IntButton();

public slots:
    void setInt (int value);

signals:
    void intChanged(int mIndex, int value);
private:
    void construct(int step);

    int mIndex;
    int mMin;
    int mMax;
    int mValue;
    QSpinBox* mSpinBox;
    QHBoxLayout* mLayout;
};

#endif // INTBUTTON_H
