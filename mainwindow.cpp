#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    videoPlayer = new QMediaPlayer(this);

    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    audioDecoder = new QAudioDecoder(this);
    visualizerWidget = new VisualizerWidget(this);
    visualizerWidget->hide();


    videoWidget = new KVideoWidget(this);
    videoWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    // videoWidget->hide();
    videoPlayer->setVideoOutput(videoWidget);

    settings = new QSettings("K&K", "Hong", this);

    visualizerPlayer = new QMediaPlayer(this);
    QString visualizerPath =
        "file:///C:/Users/PC/My Drive/Computer works/Hong (1)/videos/17_wire_audio.mov";
    // visualizerPlayer->setSource(QUrl(visualizerPath));

    playListWin = new PlaylistWindow(this);
    addDockWidget(Qt::RightDockWidgetArea, playListWin);

    QWidget *central = new QWidget(this);
    this->setCentralWidget(central);

    debounceTimer = new QTimer(this);
    debounceTimer->setSingleShot(true);
    debounceTimer->setInterval(100);

    setupWidgets();
    setupConnections();
    setupLayout();
    setupShortcuts();

    setWindowTitle(tr("Hong Pro"));
    setWindowIcon(QIcon(":/icons/icons/headphones.png"));

    qApp->installEventFilter(this);
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete audioDecoder;
    delete visualizerWidget;
}

void MainWindow::setupConnections()
{
    connect(btnPlay, &QPushButton::clicked, this,&MainWindow::togglePlayPause);
    connect(btnStop, &QPushButton::clicked, this,&MainWindow::stop);
    connect(btnReplay,&QPushButton::clicked,this,
            &MainWindow::replay);
    connect(btnImport, &QPushButton::clicked, this,&MainWindow::importSongs);

    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::updateProgress);
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::updateDuration);
    connect(videoPlayer,&QMediaPlayer::positionChanged,this,&MainWindow::updateProgress);
    connect(videoPlayer,&QMediaPlayer::durationChanged,this,&MainWindow::updateDuration);


    connect(progressSlider,&QSlider::sliderMoved,this,&MainWindow::setProgress);

    connect(progressSlider,&KSlider::valueChanged,
            this,[this](int pos) {

        if(!progressSlider->isSliderDown()) {

            debounceTimer->start();
        }
    });

    connect(audioOutput,&QAudioOutput::volumeChanged,this,[this](){
        int volume = audioOutput->volume() * 100;
        savedVolume = volume;
        lbVolume->setText(QString::number(volume));
    });

    connect(volumeSlider,&KSlider::valueChanged,this, &MainWindow::onVolumeSliderChange);

    connect(player,&QMediaPlayer::mediaStatusChanged,this,&MainWindow::handleEndOfMedia);
    connect(videoPlayer,&QMediaPlayer::mediaStatusChanged,this,&MainWindow::handleEndOfMedia);
    // connect(player,&QMediaPlayer::,this,&MainWindow::repeatVisualizer);
    connect(visualizerPlayer,&QMediaPlayer::mediaStatusChanged,this,&MainWindow::repeatVisualizer);
    connect(player,&QMediaPlayer::mediaStatusChanged,this,&MainWindow::endVisuFromPlayer);

    connect(debounceTimer,&QTimer::timeout,this,
            &MainWindow::applySliderPos);

    connect(btnConvert,&QPushButton::clicked,this,&MainWindow::onBtnConvert);

    connect(playListWin,&PlaylistWindow::songSelected,this, &MainWindow::onSongSelected);
    connect(btnNxt,&QPushButton::clicked,this,&MainWindow::playNextSong);
    connect(btnPrev,&QPushButton::clicked,this,&MainWindow::playPreviousSong);
    // connect(ckRepeat,&QCheckBox::toggled,this,&MainWindow::saveCheckBxState);

    connect(ckRepeat,&QCheckBox::toggled,this,[this](bool checked){
        repeatChecked = checked;
        saveCheckBxState(repeatChecked);

    });
    // connect(ckShuffle,&QCheckBox::toggled,this,&MainWindow::saveCheckBxState);

    connect(ckShuffle,&QCheckBox::toggled,this,[this](bool checked){
        shuffledChecked = checked;
        saveCheckBxState(shuffledChecked);
        playListWin->toggleShuffle(shuffledChecked);
    });

    connect(videoWidget, &KVideoWidget::playRequested,this,&MainWindow::togglePlayPause);
    connect(videoWidget,&KVideoWidget::pauseRequested,this,&MainWindow::togglePlayPause);
    connect(videoWidget,&KVideoWidget::fullScreenRequested,this,[this](){
        videoWidget->setFullScreen(true);
    });
    connect(videoWidget,&KVideoWidget::exitFullscreenRequested,[this]() {
        videoWidget->setFullScreen(false);
    });

    connect(videoWidget,&KVideoWidget::playPauseToggleReq,this,&MainWindow::togglePlayPause);


    // connect(audioDecoder,&QAudioDecoder::bufferReady,this,&MainWindow::handleBufferReady);

    // connect(audioDecoder,QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error),
    //         this, &MainWindow::handleError);
    // connect(audioDecoder,&QAudioDecoder::finished,this,&MainWindow::handleDecodingFinished);
}


void MainWindow::importSongs()
{
    QString lastDir = settings->value("lastDirectory",QDir::homePath()).toString();

    QStringList songFiles = QFileDialog::getOpenFileNames(this,
                     tr("Open Files"),lastDir,
                     tr("Media Files (*.mp3 *.wav *.flac *.mp4 *.avi *.mov)"));

    if(!songFiles.isEmpty()) {

        settings->setValue("lastDirectory", QFileInfo(songFiles.first()).absolutePath());
        // currentFilePath = songFiles.first();

        playListWin->clearPlaylist();
        playListWin->addSongs(songFiles);

        // // Start decoding the first song for visualization
        // QString firstSong = songFiles.first();
        // audioDecoder->setSource(QUrl::fromLocalFile(firstSong));
        // audioDecoder->start();

        QString firstFile = songFiles.first();

        if(isVideoFile(firstFile)) {
            videoPlayer->setSource(QUrl::fromLocalFile(firstFile));
            videoPlayer->setVideoOutput(videoWidget);
            videoWidget->show();
            videoPlayer->play();

        }

        QString pcmOutput = QFileInfo(songFiles.first()).absolutePath() + ".pcm";

        convertAudioToPCM(songFiles.first(),pcmOutput);


        playNextSong();     
        togglePlayPause();
        // player->play();
        updateTrackInfo();
    }
}


void MainWindow::playVisualizer()
{
    qDebug() << __FUNCTION__;

    // if(!videoWidget->isVisible()) {
    //     videoWidget->setVisible(true);
    //     qDebug() << "Made video widget visible";
    // }

    visualizerPlayer->setVideoOutput(videoWidget);

    visualizerPlayer->play();
    qDebug() << "Playing visualizer";
}

void MainWindow::stop()
{
    btnPlay->setIcon(QIcon(":/icons/icons/play.png"));
    if(isVideoFile(currentFilePath)) {
        videoPlayer->stop();
    } else {

        player->stop();
        visualizerPlayer->stop();
    }
}

void MainWindow::updateProgress(qint64 position)
{
    progressSlider->setValue(static_cast<int>(position));
    lbCurrentTime->setText(millisecondsToTimestamp(position));
}

void MainWindow::updateDuration(qint64 duration)
{
    progressSlider->setMaximum(static_cast<int>(duration));
    lbTotalTime->setText(millisecondsToTimestamp(duration));
}

QString MainWindow::millisecondsToTimestamp(qint64 mllSec)
{
    int seconds = (mllSec / 1000) % 60;
    int minutes = (mllSec / (1000 * 60)) % 60;

    return QString("%1:%2").arg(minutes,2,10,QChar('0')).arg(seconds,2,10, QChar('0'));
}

void MainWindow::setupWidgets()
{
    lbTrackInfo = new QLabel("Track Name - Artist", this);

    btnPlay = new QPushButton(this);
    btnPlay->setIcon(QIcon(":/icons/icons/play.png"));
    btnPlay->setFlat(true);
    btnPlay->setIconSize(QSize(40,40));

    btnStop = new QPushButton(this);
    btnStop->setIcon(QIcon(":/icons/icons/music.png"));
    btnStop->setFlat(true);
    btnStop->setIconSize(QSize(40,40));

    btnReplay = new QPushButton(this);
    btnReplay->setIcon(QIcon(":/icons/icons/replay.png"));
    btnReplay->setFlat(true);
    btnReplay->setIconSize(QSize(40,40));

    btnConvert = new QPushButton(this);
    btnConvert->setIcon(QIcon(":/icons/icons/exchange.png"));
    btnConvert->setFlat(true);
    btnConvert->setIconSize(QSize(40,40));

    btnNxt = new QPushButton(this);
    btnNxt->setIcon(QIcon(":/icons/icons/next-button.png"));
    btnNxt->setFlat(true);
    btnNxt->setIconSize(QSize(40,40));

    btnPrev = new QPushButton(this);
    btnPrev->setIcon(QIcon(":/icons/icons/previous.png"));
    btnPrev->setFlat(true);
    btnPrev->setIconSize(QSize(40,40));

    btnImport = new QPushButton(this);
    btnImport->setIcon(QIcon(":/icons/icons/open.png"));
    btnImport->setFlat(true);
    btnImport->setIconSize(QSize(40,60));

    ckRepeat = new QCheckBox(tr("Repeat"));
    ckRepeat->setChecked(repeatChecked);

    ckShuffle = new QCheckBox(tr("Shuffle"));
    ckShuffle->setChecked(shuffledChecked);

    volumeSlider = new KSlider(this, player,videoPlayer);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(savedVolume);

    lbVolume = new QLabel(this);
    lbVolume->setText(QString::number(savedVolume));

    // progressSlider = new KSlider(Qt::Horizontal, this);
    progressSlider = new KSlider(this, player,videoPlayer);
    progressSlider->setOrientation(Qt::Horizontal);

    lbCurrentTime = new QLabel("00:00", this);
    lbTotalTime = new QLabel("00:00", this);
}

void MainWindow::setupLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // visualizerWidget->setMinimumHeight(100);
    // mainLayout->addWidget(visualizerWidget, 1);
    mainLayout->addWidget(videoWidget, 1);

    mainLayout->addWidget(lbTrackInfo);

    QHBoxLayout *volumeSliderLayout = new QHBoxLayout();
    volumeSliderLayout->addWidget(volumeSlider, 1);
    volumeSliderLayout->addWidget(lbVolume, 3);

    QHBoxLayout *toolsLayout = new QHBoxLayout();
    toolsLayout->addWidget(btnConvert);
    toolsLayout->addStretch(5);

    mainLayout->addLayout(volumeSliderLayout);

    QHBoxLayout *progressLayout = new QHBoxLayout();
    progressLayout->addWidget(lbCurrentTime);
    progressLayout->addWidget(progressSlider);
    progressLayout->addWidget(lbTotalTime);
    mainLayout->addLayout(progressLayout);

    mainLayout->addLayout(toolsLayout);

    QHBoxLayout *trackSettingsLayout = new QHBoxLayout();
    trackSettingsLayout->addWidget(ckRepeat, 1);
    trackSettingsLayout->addWidget(ckShuffle, 8);

    mainLayout->addLayout(trackSettingsLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(btnPlay);
    // buttonLayout->addSpacerItem(new QSpacerItem(10,10,
    //              QSizePolicy::Fixed,QSizePolicy::Minimum));
    buttonLayout->addWidget(btnReplay);
    buttonLayout->addWidget(btnStop);
    buttonLayout->addWidget(btnPrev);
    buttonLayout->addWidget(btnNxt);
    buttonLayout->addWidget(btnImport);
    buttonLayout->addStretch(8);

    mainLayout->addLayout(buttonLayout);

    // mainLayout->addWidget(visualizerWidget, 1);

    centralWidget()->setLayout(mainLayout);
}

void MainWindow::setProgress(int position)
{

    if(isVideoFile(currentFilePath)) {
        videoPlayer->setPosition(position);
    } else {
        player->setPosition(position);
    }
}

void MainWindow::updateTrackInfo()
{

    if(!currentFilePath.isEmpty()) {
        QMap<QString,QString> metaData = extractMetadata(currentFilePath);

        //
        QString title = metaData.value("title");
        if(title.isEmpty()) {
            QFileInfo fileInfo(currentFilePath);
            // This gets the file name without the extension and path
            title = fileInfo.completeBaseName();
        }
        QString artist = metaData.value("artist", "Unknown Artist");

        lbTrackInfo->setText(title + " - " + artist);
    } else {
        lbTrackInfo->setText("Unknown Title - Unknown Artist");
    }
}

void MainWindow::onVolumeSliderChange(int val)
{
    // qDebug() << __FUNCTION__;
    if(settings) {
        settings->setValue("volumeLevel", val);
    }
    float volume = val / 100.0f;
    audioOutput->setVolume(volume);
}

void MainWindow::loadSettings()
{
    savedVolume = settings->value("volumeLevel", 50).toInt();
    volumeSlider->setValue(savedVolume);
    lbVolume->setText(QString::number(savedVolume));
    // Default to false if not previously set
    repeatChecked = settings->value("RepeatChecked", false).toBool();
    shuffledChecked = settings->value("shuffle", false).toBool();
    ckRepeat->setChecked(repeatChecked);
    ckShuffle->setChecked(shuffledChecked);

    // if(shuffledChecked) {
    //     playListWin->setShuffle(true);
    // }

    //PlayList and position and last song
    QStringList playlist = settings->value("playlist").toStringList();

     lastSongPath = settings->value("lastSongPath", QString()).toString();
     lastPos = settings->value("lastPos", 0).toInt();
     // qDebug() << "loading last pos: " << lastPos << "\n";
     // qDebug() << "loading lastSongPath: " << lastSongPath << "\n";

    if(!playlist.isEmpty()) {

        playListWin->addSongs(playlist);
        if(!lastSongPath.isEmpty()) {
            int songIndex = playListWin->findSongIndx(lastSongPath);
            if(songIndex != -1) {
                playListWin->setCurrSngPlyLst(songIndex);
                resume();
                updateTrackInfo();
            }
        }
    }
}



void MainWindow::togglePlayPause()
{
    if(playListWin->isEmpty()) {
        QMessageBox::critical(this,tr("Empty"),tr("No songs found"));
        importSongs();
    }
    if(player->playbackState() == QMediaPlayer::PlayingState ||
        videoPlayer->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        videoPlayer->pause();
        visualizerPlayer->pause();
        btnPlay->setIcon(QIcon(":/icons/icons/play.png"));
    }

    else {
        if(isVideoFile(currentFilePath)) {
            videoPlayer->play();
        } else {
            qDebug() << "this else 1\n";
            player->play();
            // visualizerPlayer->play();
            playVisualizer();
        }
        btnPlay->setIcon(QIcon(":/icons/icons/pause.png"));
    }

    savePlaybackPos();
    savePlayList();
}

void MainWindow::replay()
{
    if(isVideoFile(currentFilePath)) {
        videoPlayer->setPosition(0);
        videoPlayer->play();
    } else {

        player->setPosition(0);
        player->play();
        visualizerPlayer->play();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() & Qt::ControlModifier) {

        if(event->key() == Qt::Key_O)
            importSongs();

    } else {
        switch(event->key()) {

        case Qt::Key_S:
            stop();
            break;

        case Qt::Key_R:
            replay();
            break;


        default:
            QMainWindow::keyPressEvent(event);
        }
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if(keyEvent->key() == Qt::Key_Space) {
            togglePlayPause();
            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::handleEndOfMedia(QMediaPlayer::MediaStatus status) {

    if(isVideoFile(currentFilePath)) {
        if(ckRepeat->isChecked() && status == QMediaPlayer::EndOfMedia) {
            replay();
        }
    } else {

        if(ckRepeat->isChecked() && status == QMediaPlayer::EndOfMedia) {
            replay();
        } else if(!ckRepeat->isChecked() && status == QMediaPlayer::EndOfMedia) {
            playNextSong();
        }
    }
}

void MainWindow::repeatVisualizer(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::EndOfMedia && player->playbackState() == QMediaPlayer::PlayingState ) {
        visualizerPlayer->setPosition(0);
        visualizerPlayer->play();
    }
}

// Slot to apply the position
void MainWindow::applySliderPos()
{
    if(isVideoFile(currentFilePath)) {
        videoPlayer->setPosition(progressSlider->value());
    } else {

        player->setPosition(progressSlider->value());
        // togglePlayPause();
        // playVisualizer();
    }
}

QMap<QString,QString> MainWindow::extractMetadata(const QString &filePath)
{
     // Initialize libavformat and register all formats and codecs
     avformat_network_init();
     AVFormatContext *formatCtx = nullptr;

     // Open the media file
     if(avformat_open_input(&formatCtx,filePath.toLocal8Bit().data(),
                             nullptr, nullptr) != 0) {
         qDebug() << "Couldn't open file";
         return QMap<QString,QString>();
     }

     // Retrieve stream information
     if(avformat_find_stream_info(formatCtx, nullptr) < 0) {
         qDebug() << "Could't find stream information";
         avformat_close_input(&formatCtx);
          return QMap<QString,QString>();
     }

     // Create a QMap to hold metadata key-value pairs
     QMap<QString,QString>  metaDataMp;

     // Get the metadata in a dictionary
     AVDictionary *metaData = formatCtx->metadata;
     // Iterate over all entries in the dictionary
     AVDictionaryEntry *tag = nullptr;
     while ((tag = av_dict_get(metaData, "", tag, AV_DICT_IGNORE_SUFFIX))) {
         QString key = QString(tag->key);
         QString value = QString(tag->value);
         metaDataMp.insert(key, value);
         qDebug() << key << ":" << value;
     }

     avformat_close_input(&formatCtx);

     return metaDataMp;
}


void MainWindow::onBtnConvert()
{
    if(currentFilePath.isEmpty()) {
        // qDebug() << "No file is loaded\n";
        QMessageBox::critical(this, "Error", "No File has been selected");
        return;
    }

    ConvertDialog *convertDialog = new ConvertDialog(this);
    convertDialog->setSourcePath(currentFilePath);

    convertDialog->exec();
}


bool MainWindow::isVideoFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);

    return fileInfo.suffix().toLower() == "mov" ||
           fileInfo.suffix().toLower() == "avi" ||
           fileInfo.suffix().toLower() == "mp4";
}

void MainWindow::endVisuFromPlayer(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::EndOfMedia) {
        visualizerPlayer->stop();
    }
}

void MainWindow::onSongSelected(const QString &songPath)
{
    if(!songPath.isEmpty()) {
        currentFilePath = songPath;

        if(isVideoFile(songPath)) {
            videoPlayer->setSource(QUrl::fromLocalFile(songPath));
            videoPlayer->setVideoOutput(videoWidget);
            videoWidget->show();
            videoPlayer->play();
            // togglePlayPause();
        } else {
            player->setSource(QUrl::fromLocalFile(songPath));
            audioOutput->setVolume(savedVolume / 100.0f);
            player->play();
        }

        updateTrackInfo();

        int indx = playListWin->findSongIndx(songPath);

        if(indx != -1) {
            playListWin->setCurrSngPlyLst(indx);
        }
    }
}
// void MainWindow::onSongSelected(const QString &songPath)
// {
//     qDebug() << __FUNCTION__;



//     if(!songPath.isEmpty()) {

//         player->setSource(QUrl::fromLocalFile(songPath));
//         int vol = settings->value("volumeLevel").toInt();
//         audioOutput->setVolume(vol/100.0f);
//         player->play();
//         currentFilePath = songPath;
//         updateTrackInfo();
//         // playListWin->setCurrSngPlyLst(playListWin->getCurrIndx());
//         togglePlayPause();
//         playVisualizer();
//         updateTrackInfo();

//         audioDecoder->setSource(QUrl::fromLocalFile(songPath));
//         audioDecoder->start();

//         int indx = playListWin->findSongIndx(songPath);
//         if(indx != -1) {
//             playListWin->setCurrSngPlyLst(indx);

//         }
//     }
// }

void MainWindow::playNextSong()
{
    QString nextSongPath = playListWin->getNxtSong();

    qDebug() << "Playing next song:" << nextSongPath;
    qDebug() << "Current Shuffle State:" << ckShuffle->isChecked();

    audioOutput->setVolume(savedVolume/100.0f);
    volumeSlider->setValue(savedVolume);

    if(!nextSongPath.isEmpty()) {
        playListWin->setCurrSngPlyLst(playListWin->getCurrIndx());
        currentFilePath = nextSongPath;
        updateTrackInfo();

        if(isVideoFile(nextSongPath)) {
            videoPlayer->setSource(QUrl::fromLocalFile(nextSongPath));
            videoPlayer->setVideoOutput(videoWidget);
            videoPlayer->play();
            togglePlayPause();
        } else {
            player->setSource(QUrl::fromLocalFile(nextSongPath));
            player->play();
            // playVisualizer();
            togglePlayPause();

            // Start decoding the new song for visualization
            audioDecoder->setSource(QUrl::fromLocalFile(nextSongPath));
            audioDecoder->start();
        }

    } else if(ckShuffle->isChecked() && playListWin->playListCount() > 0) {
        // Reset the index to start from the beginning in shuffle mode
        playListWin->resetCurrIndx();
        // Recursively call to play the next song from the start
        playNextSong();
    }


    else {
        QMessageBox::information(this,tr("No more songs"),
                                 tr("No more songs to paly"));
        shuffledChecked = false;
        ckShuffle->setChecked(shuffledChecked);
        playListWin->toggleShuffle(shuffledChecked);
        return;
    }
}

void MainWindow::playPreviousSong()
{
    QString prevSongPath = playListWin->getPrevSong();

    if(!prevSongPath.isEmpty()) {
        playListWin->setCurrSngPlyLst(playListWin->getCurrIndx());
        currentFilePath = prevSongPath;
        updateTrackInfo();

        if(isVideoFile(prevSongPath)) {
            videoPlayer->setSource(QUrl::fromLocalFile(prevSongPath));
            videoPlayer->play();
        } else {

            player->setSource(QUrl::fromLocalFile(prevSongPath));
            player->play();
            playVisualizer();
        }
    } else {
        QMessageBox::information(this,tr("No previous song"),
    tr("This is the first song in the playlist"));
    }
}

void MainWindow::setupShortcuts()
{
    shortcutNext = new QShortcut(QKeySequence("Ctrl+Right"), this);
    shortcutPrev = new QShortcut(QKeySequence("Ctrl+Left"), this);

    connect(shortcutNext,&QShortcut::activated,this,&MainWindow::playNextSong);
    connect(shortcutPrev,&QShortcut::activated,this,&MainWindow::playPreviousSong);
}


void MainWindow::saveCheckBxState(bool checked)
{
    if(settings) {
        settings->setValue("RepeatChecked", repeatChecked);
        settings->setValue("shuffle", shuffledChecked);
    }
}


void MainWindow::savePlayList()
{
    QStringList songPaths;

    for(int i = 0; i < playListWin->playListCount(); ++i) {
        songPaths << playListWin->songAt(i);
    }

    settings->setValue("playlist", songPaths);
}

void MainWindow::savePlaybackPos()
{
    if(player->mediaStatus() == QMediaPlayer::LoadedMedia) {
        int pos = player->position();

        settings->setValue("lastPos", pos);
        settings->setValue("lastSongPath", currentFilePath);
        qDebug() << "saveing lastPos: " << pos << " lastSongPath " << currentFilePath << "\n";
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvent\n";
    savePlayList();
    savePlaybackPos();

    QMainWindow::closeEvent(event);
}

void MainWindow::resume()
{
    currentFilePath = lastSongPath;
    player->setSource(QUrl::fromLocalFile(currentFilePath));

    int vol = settings->value("volumeLevel", 50).toInt();
    audioOutput->setVolume(vol/100.0f);
    // player->setPosition(lastPos);
    // player->pause();
   loadMediaConnection = connect(player,&QMediaPlayer::mediaStatusChanged,this,
            [this](QMediaPlayer::MediaStatus status) {
                if(status == QMediaPlayer::LoadedMedia) {
                    qDebug() << "Inside connect load settings\n";
                    player->setPosition(lastPos);
                    player->pause();
                    // disconnect(player,&QMediaPlayer::mediaStatusChanged,this,nullptr);
                    disconnect(loadMediaConnection);
                }
            });
}


void MainWindow::convertAudioToPCM(const QString &sourcePath, const QString &destPath)
{
    QProcess *ffmpegProcess = new QProcess(this);

    connect(ffmpegProcess,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),
            [this,destPath](int exitCode,QProcess::ExitStatus exitStatus) {
        visualizerWidget->loadPCMData(destPath);
    });

    ffmpegProcess->start("ffmpeg",QStringList() << "-i" << sourcePath
      << "-f" << "s16le" << "-acodec" << "pcm_s16le" << destPath);
}





















