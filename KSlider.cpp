

#include "KSlider.h"


KSlider::KSlider(QWidget *parent) :QSlider(parent)
{

}

KSlider::KSlider(QWidget *parent, QMediaPlayer *p,
                 QMediaPlayer *vidPlayer)
    :QSlider(parent),player(p),videoPlayer(vidPlayer)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(100);

    connect(timer,&QTimer::timeout, this, &KSlider::resumePlayback);
}


void KSlider::mousePressEvent(QMouseEvent *event)
{
    qDebug() << __FUNCTION__;
    if(event->button() == Qt::LeftButton) {

        if(player) {
            player->pause();
        }

        if(videoPlayer) {
            videoPlayer->pause();
        }

        double newPos;

        if(orientation() == Qt::Horizontal) {
            newPos = minimum() +(maximum()-minimum())*
        static_cast<double>(event->position().x())/width();
        } else {
            if(orientation() == Qt::Vertical) {
                newPos = minimum() +(maximum()-minimum())*
        static_cast<double>(event->position().y()) / height();
            }
        }

        setValue(static_cast<int>(newPos));

        if(player) {
            player->setPosition(static_cast<int>(newPos));
        }

        if(videoPlayer) {
            videoPlayer->setPosition(static_cast<int>(newPos));
        }

        timer->start();

        QSlider::mousePressEvent(event);
    } else {
        QSlider::mousePressEvent(event);
    }
}

void KSlider::resumePlayback()
{
    if(player) {
        player->play();
    }

    if(videoPlayer) {
        videoPlayer->play();
    }
}

