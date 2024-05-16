#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <QDockWidget>
#include <QListWidget>
#include <QStringList>
#include <QFileInfo>
#include <algorithm>
#include <QRandomGenerator>

class PlaylistWindow : public QDockWidget
{
    Q_OBJECT

public:
    explicit PlaylistWindow(QWidget *parent=nullptr);
    void addSongs(const QStringList &songs);
    void clearPlaylist();

    QString getNxtSong();
    QString getPrevSong();

    void setCurrSngPlyLst(int indx);
    int getCurrIndx() const;
    int findSongIndx(const QString&) const;
    QString songAt(int indx) const;
    int playListCount() const;
    bool isEmpty() const;

    void shufflePlayList();
    void toggleShuffle(bool enabled);
    void updateShuffledIndexes();

    void setShuffle(bool);
    void resetCurrIndx();

signals:
    void songSelected(const QString &songPath);

private:
    QListWidget *playlistView;
    int currIndex = -1;
    QVector<int> shuffleIndexes;
    bool shuffleEnabled = false;

};

#endif // PLAYLISTWINDOW_H
