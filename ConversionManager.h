#ifndef CONVERSIONMANAGER_H
#define CONVERSIONMANAGER_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QRegularExpression>


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}


class ConversionManager : public QObject {
    Q_OBJECT

public:
    explicit ConversionManager(QObject *parent=nullptr);
    void convert(const QString &srcPath,const QString &targetPath,
                 const QString &format, const QString &quality);

    double getFileDuration(const QString &filePath);

signals:
    void conversionStarted();
    void conversionFinished(bool success, const QString &outputPath);
    void conversionProgressUpdated(double);
};


#endif // CONVERSIONMANAGER_H
