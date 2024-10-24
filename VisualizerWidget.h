#ifndef VISUALIZERWIDGET_H
#define VISUALIZERWIDGET_H



#include <QWidget>
#include <QAudioBuffer>
#include <QMediaPlayer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QElapsedTimer>
#include <QFile>
#include <QByteArray>
#include <memory>

class VisualizerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizerWidget(QWidget *parent=nullptr);
    ~VisualizerWidget();
    // void processBuffer(const QAudioBuffer &buffer);
    void loadPCMData(const QString &filePath);

private slots:
    void updateVisuals();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<qreal> m_levels;
    QTimer *updateTimer;
    QElapsedTimer elapsedTimer;
};



#endif // VISUALIZERWIDGET_H
