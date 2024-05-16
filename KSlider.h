#ifndef KSLIDER_H
#define KSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QWidget>
#include <QMediaPlayer>
#include <QTimer>

class KSlider : public QSlider
{
    Q_OBJECT

public:
    explicit KSlider(QWidget *parent=nullptr);
    // explicit KSlider(QWidget *parent,QMediaPlayer *p);
    explicit KSlider(QWidget *parent,QMediaPlayer *player,QMediaPlayer *vidPlayer);
    explicit KSlider(Qt::Orientation orientaion, QWidget *parent)
        :QSlider(orientaion, parent) {}

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void resumePlayback();

private:
    QMediaPlayer *player;
    QMediaPlayer *videoPlayer;
    QTimer *timer;
};

#endif // KSLIDER_H
