#ifndef COLORBUTTON_H
#define COLORBUTTON_H
//#include <QPushButton>
//#include <QWidget>
//#include <QColorDialog>
#include <QGroupBox>
//#include <QHBoxLayout>
#include "Simulation/Descriptor/types/color_description.h"

class QColorDialog;
class QPushButton;
class QHBoxLayout;

class ColorButton : public QGroupBox {
    Q_OBJECT
private:
    ColorButton();
public:
    ColorButton(int index, const QString& name, QWidget* parent=0);
    ColorButton(ColorDescription* desc, int index, QWidget* parent=0);
    ~ColorButton();

public slots:
    void setColor (const QColor& color);

signals:
    void colorChanged (int mIndex, const QColor& color);

private:
    void construct ();

    int mIndex;
    QColor mColor;
    QColorDialog* mDialog;
    QPushButton* mPushButton;
    QHBoxLayout* mLayout;
};

#endif // COLORBUTTON_H


