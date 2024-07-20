#ifndef DOUBLEBUTTON_H
#define DOUBLEBUTTON_H
#include <QGroupBox>
//#include <QDoubleSpinBox>
//#include <QWidget>
//#include <QHBoxLayout>
//#include <QLabel>
#include "Simulation/Descriptor/types/double_description.h"

class QDoubleSpinBox;
class QHBoxLayout;

class DoubleButton : public QGroupBox {
    Q_OBJECT
public:
    DoubleButton(DoubleDescription* desc, int index, QWidget* parent=0);
    DoubleButton(int index, const QString& name, double min, double max, double step, QWidget* parent=0);
    ~DoubleButton();

public slots:
    void setDouble (double value);

signals:
    void doubleChanged(int index, double value);
private:
    void construct(double step);

    int mIndex;
    double mMin;
    double mMax;
    double mValue;
    QDoubleSpinBox* mDoubleSpinBox;
    QHBoxLayout* mLayout;
};


#endif // DOUBLEBUTTON_H
