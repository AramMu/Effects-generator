#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H
#include <QPushButton>
#include <QMouseEvent>

class PushButton : public QPushButton {
    Q_OBJECT
public:
    PushButton(int index, QWidget* parent=0);
    PushButton(int index, const QString& name, QWidget *parent=0);
    void mousePressEvent(QMouseEvent* m);

    int getIndex() const;
signals:
    void pressed (int index);

private:
    int index;
//public slots:
};

#endif // PUSHBUTTON_H
