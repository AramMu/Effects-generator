#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H
#include <QWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include "Simulation/Descriptor/types/radio_description.h"


class IndexedRadio : public QRadioButton {
    Q_OBJECT
public:
    IndexedRadio (int index, QWidget* parent=0);
public slots:
    void radioCheckedSlot (bool isChecked);
signals:
    void radioChecked (int buttonIndex);
private:
    int mIndex;
};



class RadioButton : public QGroupBox {
    Q_OBJECT
public:
    RadioButton(RadioDescription* desc, int index, QWidget* parent=0);
    RadioButton(int index, const std::vector<std::string>& names, const QString& text, QWidget* parent=0);
    ~RadioButton();

public slots:
    void setRadio (int buttonIndex);

signals:
    void radioChanged (int index, int buttonIndex);

private:
    int mIndex;
    int mButtonIndex;
    QVector <IndexedRadio*> mRadios;
    QHBoxLayout* mLayout;
};



#endif // RADIOBUTTON_H




