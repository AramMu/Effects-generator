#include "qtutils.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>


QColor toQColor (cv::Vec3b color) {
    return QColor(color[2], color[1], color[0]);
}

cv::Vec3b toCvColor (const QColor& color) {
    return cv::Vec3b (color.blue(), color.green(), color.red());
}

QString getNextFreeNumber(const QString& path, const QString& format) {
    int k = 0;
    while (true) {
        ++k;
        if (k > 100000) {
            return QString("");
        }
        QFileInfo file(path + QString::number(k) + format);
        if (! (file.exists() && file.isFile())) {
            return file.path() + "\\" + file.fileName();
        }
    }
    return QString("");
}


cv::Vec3b swapCvColor (cv::Vec3b color) {
    return cv::Vec3b (color[2], color[1], color[0]);
}
