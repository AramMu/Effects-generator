#ifndef QTUTILS
#define QTUTILS
#include <QColor>
#include <opencv2/imgproc.hpp>

QColor toQColor (cv::Vec3b color);
cv::Vec3b toCvColor (const QColor& color);
cv::Vec3b swapCvColor (cv::Vec3b color);
QString getNextFreeNumber(const QString& path, const QString& format);

#endif // QTUTILS

