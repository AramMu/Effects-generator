#include "pushbutton.h"

PushButton::PushButton(int index, QWidget *parent) :
    QPushButton(parent),
    index(index)
{}

PushButton::PushButton(int index, const QString& name, QWidget *parent) :
    QPushButton(name, parent),
    index(index)
{}



void PushButton::mousePressEvent(QMouseEvent* m) {
    emit pressed(index);
}

int PushButton::getIndex() const {
    return index;
}

