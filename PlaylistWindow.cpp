

#include "PlaylistWindow.h"


PlaylistWindow::PlaylistWindow(QWidget *parent):QDockWidget(parent)
{
    setWindowTitle(tr("Playlist"));
    playlistView = new QListWidget(this);
    setWidget(playlistView);

    connect(playlistView,&QListWidget::itemDoubleClicked,this,[this](QListWidgetItem *item) {
        QString songPath = item->data(Qt::UserRole).toString();
        qDebug() << "Double-clicked on song:" << songPath;
        emit songSelected(songPath);
    });
}

void PlaylistWindow::addSongs(const QStringList &songs)
{
     // qDebug() << "Adding songs to playlist:" << songs;
    currIndex = -1;
    for(const QString &song : songs) {
        QListWidgetItem *item = new QListWidgetItem(QFileInfo(song).fileName());
        item->setData(Qt::UserRole, song);
        playlistView->addItem(item);
    }

    updateShuffledIndexes();
}

void PlaylistWindow::clearPlaylist()
{
    playlistView->clear();
    currIndex = -1;
    shuffleIndexes.clear();
}

QString PlaylistWindow::getNxtSong()
{
    qDebug() << __FUNCTION__ << "\n";
    if(shuffleEnabled && !shuffleIndexes.isEmpty()) {
        if(currIndex + 1 < shuffleIndexes.size()) {
            currIndex++;
            int shuffledInex = shuffleIndexes[currIndex];
            // qDebug() << "Shuffled Next song index:" << shuffledInex;
            return songAt(shuffledInex);
        }
    } else {
        if(currIndex + 1 < playlistView->count()) {
            currIndex++;
             // qDebug() << "Next song index:" << currIndex;
            return songAt(currIndex);
        }
    }

    return QString();
}

QString PlaylistWindow::getPrevSong()
{
    if(shuffleEnabled && !shuffleIndexes.isEmpty()) {
        if(currIndex > 0) {
            currIndex--;
            int shuffledIndex = shuffleIndexes[currIndex];
            // qDebug() << "Shuffled Previous song index:" << shuffledIndex;
            return songAt(shuffledIndex);
        }
    } else {
        if(currIndex > 0) {
            currIndex--;
            // qDebug() << "Previous song index:" << currIndex;
            return songAt(currIndex);
        }
    }

    return QString();
}


void PlaylistWindow::setCurrSngPlyLst(int indx)
{
    if(indx >= 0 && indx < playlistView->count()) {
        QListWidgetItem *item = nullptr;

        // Use shuffled indexes if shuffle is enabled
        if(shuffleEnabled && indx < shuffleIndexes.size()) {
            int actualIndex = shuffleIndexes.at(indx);
            item = playlistView->item(actualIndex);
        } else {
            item = playlistView->item(indx);
        }

        if(item) {
            playlistView->setCurrentItem(item);
            playlistView->scrollToItem(item, QAbstractItemView::PositionAtCenter);
        }

        currIndex = indx;
    }
}




int PlaylistWindow::getCurrIndx() const
{
    return currIndex;
}

int PlaylistWindow::findSongIndx(const QString &songPath) const
{
    for(int i = 0; i < playlistView->count(); ++i)
    {
        QListWidgetItem *item = playlistView->item(i);
        if(item->data(Qt::UserRole).toString()
            == songPath) {
            return i;
        }
    }

    // Return -1 if not found
    return -1;
}

QString PlaylistWindow::songAt(int indx) const
{
    if(indx >= 0 && indx < playlistView->count()) {

        QListWidgetItem *item = playlistView->item(indx);
        QString songPath = item ? item->data(Qt::UserRole).toString() : QString();
        // qDebug() << "Song at index" << indx << ":" << songPath;

        return songPath;
    }

    return QString();
}

int PlaylistWindow::playListCount() const
{
    return playlistView->count();
}



bool PlaylistWindow::isEmpty() const
{
    return playlistView->count() <= 0;
}


void PlaylistWindow::toggleShuffle(bool enabled)
{
    shuffleEnabled = enabled;
    // qDebug() << "Shuffle enabled:" << shuffleEnabled;
    updateShuffledIndexes();
}


void PlaylistWindow::updateShuffledIndexes()
{
    shuffleIndexes.clear();

    for(int i = 0; i < playlistView->count(); ++i) {
        shuffleIndexes.append(i);
    }

    if(shuffleEnabled) {
        qDebug() << "Shuffling indexes before:" << shuffleIndexes;
        std::shuffle(shuffleIndexes.begin(), shuffleIndexes.end(),
                     *QRandomGenerator::global());
        qDebug() << "Shuffled indexes after:" << shuffleIndexes;
    }
}


void PlaylistWindow::setShuffle(bool check)
{
    if(check) {
        shuffleEnabled = true;
    } else {
        shuffleEnabled = false;
    }
}

void PlaylistWindow::resetCurrIndx()
{
    currIndex = -1;
}









