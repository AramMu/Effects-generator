#include "frameview.h"
#include <QPainter>
//#include <cassert>
//#include <QDebug>
//#include "Time/sleeper.h"

FrameView::FrameView(const QSize &size, QWidget *parent) :
    QWidget(parent),
    mSize(size)
{
    mImage = QImage(size, QImage::Format_RGB888);
    mMat = cv::Mat (size.height(), size.width(), CV_8UC3);
    this->setFixedSize(size);
}

FrameView::~FrameView() {}

void FrameView::setPixmap (cv::Mat* cvMat) {
    mMat = *cvMat;
    mImage = QImage(mMat.data, mMat.cols, mMat.rows, QImage::Format_RGB888);
    emit conversionFinished();
    update();
}

void FrameView::paintEvent(QPaintEvent* event) {
    QPainter qp(this);
    qp.drawImage(0,0,mImage);
}

void FrameView::save (const QString& fileName) {
    mImage.save(fileName);
}
