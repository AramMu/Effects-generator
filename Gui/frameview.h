#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H
#include <QWidget>
#include <opencv2/core.hpp>

class FrameView : public QWidget {
    Q_OBJECT
public:
    FrameView(const QSize& size, QWidget* parent = 0);
    ~FrameView();
    void paintEvent(QPaintEvent* event);
public slots:
    void setPixmap (cv::Mat* pixmap);
    void save (const QString& fileName);
signals:
    void conversionFinished();
private:
    cv::Mat mMat;
    QImage mImage;
    QSize mSize;
};

#endif // FRAMEVIEW_H
