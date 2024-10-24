
#include "VisualizerWidget.h"

VisualizerWidget::VisualizerWidget(QWidget *parent)
    :QWidget(parent)
{
    updateTimer = new QTimer(this);

    connect(updateTimer,&QTimer::timeout,this,&VisualizerWidget::updateVisuals);
    updateTimer->start(100);
    elapsedTimer.start();
}

VisualizerWidget::~VisualizerWidget()
{
    updateTimer->stop();
}



// void VisualizerWidget::processBuffer(const QAudioBuffer &buffer)
// {
//     if (!buffer.isValid()) {
//         return;
//     }

//     const qint16* data = buffer.constData<qint16>();
//     int numSamples = buffer.sampleCount();

//     qreal maxLevel = 0;
//     int sampleStep = 50;  // Define a fixed step size for averaging to reduce data rate

//     for (int i = 0; i < numSamples; i++) {
//         qreal level = qAbs(data[i]) / 32768.0;  // Normalize the sample value
//         maxLevel = qMax(maxLevel, level);

//         if (i % sampleStep == sampleStep - 1) {  // Collect data every 'sampleStep' samples
//             m_levels.append(maxLevel);
//             maxLevel = 0;  // Reset for the next batch
//         }
//     }

//     // Keep the size of m_levels within reasonable limits to avoid lag
//     if (m_levels.size() > 300) {  // Limit the size to maintain responsiveness
//         m_levels.remove(0, m_levels.size() - 300);
//     }
// }

void VisualizerWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black); // Background

    if (m_levels.isEmpty())
        return;

    QPainterPath path;
    path.moveTo(0, height() / 2);
    qreal xStep = qreal(width()) / qreal(m_levels.size());
    for (int i = 0; i < m_levels.size(); ++i) {
        path.lineTo(i * xStep, height() / 2 * (1.0 - m_levels.at(i)));
    }

    painter.setPen(Qt::green); // Draw waveform in green
    painter.drawPath(path);
}

void VisualizerWidget::updateVisuals() {
    if (elapsedTimer.elapsed() > 50) {
        update(); // Redraw the widget
        elapsedTimer.restart();
    }
}

void VisualizerWidget::loadPCMData(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open PCM file: " << filePath;
        return;
    }

    QByteArray data = file.readAll();
    const qint16* dataPtr = reinterpret_cast<const qint16*>(data.constData());
    int sampleCount = data.size() / sizeof(qint16);
    m_levels.clear();
    m_levels.reserve(sampleCount);
    for (int i = 0; i < sampleCount; i++) {
        m_levels.append(qAbs(dataPtr[i]) / 32768.0); // Normalize and store
    }

    update(); // Request a redraw after data is loaded
}













