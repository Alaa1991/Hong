


#include "KVideoWidget.h"


KVideoWidget::KVideoWidget(QWidget *parent):QVideoWidget(parent)
{

}


void KVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        // Toggle between fullscreen and windowed mode
        if(isFullScreen()) {
            setFullScreen(false);
        } else {
            setFullScreen(true);
        }
    }

    // Pass the event to the base class for any additional handling
    QVideoWidget::mouseDoubleClickEvent(event);
}

void KVideoWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && isFullScreen()) {
        setFullScreen(false);
    } else {
        QVideoWidget::keyPressEvent(event);
    }
}

void KVideoWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        showContextMenu(event->pos());
    }

    else if(event->button() == Qt::LeftButton) {
        emit playPauseToggleReq();
    }

    else {
        QVideoWidget::mousePressEvent(event);
    }
}


void KVideoWidget::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(this);

    QAction *playAction = contextMenu.addAction("Play");
    QAction *pauseAction = contextMenu.addAction("Pause");
    QAction *fullScreenAction = contextMenu.addAction("Fullscreen");
    QAction *exitFullscreenAction = contextMenu.addAction("Exit Fullscreen");

    connect(playAction,&QAction::triggered,this, [this]() {
        emit playRequested();
    });

    connect(pauseAction,&QAction::triggered,this, [this] {
        emit pauseRequested();
    });

    connect(fullScreenAction,&QAction::triggered,this,[this] {
        emit fullScreenRequested();
    });

    connect(exitFullscreenAction,&QAction::triggered,this,[this] {
        emit exitFullscreenRequested();
    });

    // Show the menu at the cursor position
    contextMenu.exec(mapToGlobal(pos));
}










