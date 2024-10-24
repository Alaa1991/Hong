#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QFileDialog>
#include <QStringList>
#include <QUrl>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMediaMetaData>
#include <QString>
#include <QLocale>
#include <QAudioOutput>
#include <QSettings>
#include <QIcon>
#include <QKeyEvent>
#include <QApplication>
#include <QCheckBox>
#include "KSlider.h"
#include <QTimer>
#include <QMap>
#include "ConvertDialog.h"
#include <QMessageBox>
#include <QVideoWidget>
#include "PlaylistWindow.h"
#include <QShortcut>
#include <QKeySequence>
#include <QCloseEvent>
#include <QMetaObject>
#include <QAudioDecoder>
#include <QAudioBuffer>

#include "VisualizerWidget.h"
#include "KVideoWidget.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void importSongs();
    QMap<QString,QString> extractMetadata(const QString &filePath);
    void onVolumeSliderChange(int);
    void togglePlayPause();


    void stop();
    void replay();
    void updateProgress(qint64 position);
    void updateDuration(qint64 duration);
    void setProgress(int position);
    void updateTrackInfo();

    void onBtnConvert();

    bool eventFilter(QObject *watched, QEvent *event);
    void handleEndOfMedia(QMediaPlayer::MediaStatus);
    void repeatVisualizer(QMediaPlayer::MediaStatus);
    void endVisuFromPlayer(QMediaPlayer::MediaStatus);
    void applySliderPos();
    void onSongSelected(const QString &songPath);
    bool isVideoFile(const QString &filePath);

    void playNextSong();
    void playPreviousSong();
    void savePlayList();
    void savePlaybackPos();

    // void handleBufferReady();
    // void handleError(QAudioDecoder::Error);
    // void handleDecodingFinished();
    void convertAudioToPCM(const QString&,const QString&);


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent*) override;


private:
    void setupConnections();
    void setupLayout();
    void setupWidgets();
    void setupShortcuts();
    QString millisecondsToTimestamp(qint64 milliseconds);
    void loadSettings();
    void playVisualizer();
    void saveCheckBxState(bool checked);
    void resume();


    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QLabel *lbTrackInfo;

    QPushButton *btnPlay;
    QPushButton *btnStop;
    QPushButton *btnReplay;
    QPushButton *btnConvert;
    QPushButton *btnNxt;
    QPushButton *btnPrev;

    QPushButton *btnImport;
    KSlider *volumeSlider;
    KSlider *progressSlider;
    QLabel *lbCurrentTime;
    QLabel *lbTotalTime;
    QLabel *lbVolume;
    bool pauseClicked = false;
    int savedVolume;

    QCheckBox *ckRepeat;
    QCheckBox *ckShuffle;

    bool repeatChecked;
    bool shuffledChecked;

    QSettings *settings;
    bool userSliderChange = false;
    QTimer *debounceTimer;
    QString currentFilePath;

    KVideoWidget *videoWidget;

    QMediaPlayer *videoPlayer;
    QMediaPlayer *visualizerPlayer;

    PlaylistWindow *playListWin;

    QShortcut *shortcutNext;
    QShortcut *shortcutPrev;
    QString lastSongPath;
    int lastPos;

    QMetaObject::Connection loadMediaConnection;

    VisualizerWidget *visualizerWidget;
    QAudioDecoder *audioDecoder;
};
