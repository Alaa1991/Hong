#ifndef KVIDEOWIDGET_H
#define KVIDEOWIDGET_H

#include <QVideoWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QAction>
#include <QMenu>

class KVideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit KVideoWidget(QWidget *parent = nullptr);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
   void playRequested();
   void pauseRequested();
   void fullScreenRequested();
   void exitFullscreenRequested();
   void playPauseToggleReq();

private:
    void showContextMenu(const QPoint &pos);
};


#endif // KVIDEOWIDGET_H
