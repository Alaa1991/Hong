/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "importSongs",
    "",
    "extractMetadata",
    "QMap<QString,QString>",
    "filePath",
    "onVolumeSliderChange",
    "togglePlayPause",
    "stop",
    "replay",
    "updateProgress",
    "position",
    "updateDuration",
    "duration",
    "setProgress",
    "updateTrackInfo",
    "onBtnConvert",
    "eventFilter",
    "watched",
    "QEvent*",
    "event",
    "handleEndOfMedia",
    "QMediaPlayer::MediaStatus",
    "repeatVisualizer",
    "endVisuFromPlayer",
    "applySliderPos",
    "onSongSelected",
    "songPath",
    "isVideoFile",
    "playNextSong",
    "playPreviousSong",
    "savePlayList",
    "savePlaybackPos",
    "convertAudioToPCM"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  152,    2, 0x08,    1 /* Private */,
       3,    1,  153,    2, 0x08,    2 /* Private */,
       6,    1,  156,    2, 0x08,    4 /* Private */,
       7,    0,  159,    2, 0x08,    6 /* Private */,
       8,    0,  160,    2, 0x08,    7 /* Private */,
       9,    0,  161,    2, 0x08,    8 /* Private */,
      10,    1,  162,    2, 0x08,    9 /* Private */,
      12,    1,  165,    2, 0x08,   11 /* Private */,
      14,    1,  168,    2, 0x08,   13 /* Private */,
      15,    0,  171,    2, 0x08,   15 /* Private */,
      16,    0,  172,    2, 0x08,   16 /* Private */,
      17,    2,  173,    2, 0x08,   17 /* Private */,
      21,    1,  178,    2, 0x08,   20 /* Private */,
      23,    1,  181,    2, 0x08,   22 /* Private */,
      24,    1,  184,    2, 0x08,   24 /* Private */,
      25,    0,  187,    2, 0x08,   26 /* Private */,
      26,    1,  188,    2, 0x08,   27 /* Private */,
      28,    1,  191,    2, 0x08,   29 /* Private */,
      29,    0,  194,    2, 0x08,   31 /* Private */,
      30,    0,  195,    2, 0x08,   32 /* Private */,
      31,    0,  196,    2, 0x08,   33 /* Private */,
      32,    0,  197,    2, 0x08,   34 /* Private */,
      33,    2,  198,    2, 0x08,   35 /* Private */,

 // slots: parameters
    QMetaType::Void,
    0x80000000 | 4, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   11,
    QMetaType::Void, QMetaType::LongLong,   13,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 19,   18,   20,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'importSongs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'extractMetadata'
        QtPrivate::TypeAndForceComplete<QMap<QString,QString>, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onVolumeSliderChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'togglePlayPause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'updateDuration'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'setProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateTrackInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBtnConvert'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'eventFilter'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QEvent *, std::false_type>,
        // method 'handleEndOfMedia'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'repeatVisualizer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'endVisuFromPlayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'applySliderPos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSongSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'isVideoFile'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'playNextSong'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playPreviousSong'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'savePlayList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'savePlaybackPos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'convertAudioToPCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->importSongs(); break;
        case 1: { QMap<QString,QString> _r = _t->extractMetadata((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QMap<QString,QString>*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->onVolumeSliderChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->togglePlayPause(); break;
        case 4: _t->stop(); break;
        case 5: _t->replay(); break;
        case 6: _t->updateProgress((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 7: _t->updateDuration((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 8: _t->setProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->updateTrackInfo(); break;
        case 10: _t->onBtnConvert(); break;
        case 11: { bool _r = _t->eventFilter((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QEvent*>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->handleEndOfMedia((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 13: _t->repeatVisualizer((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 14: _t->endVisuFromPlayer((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 15: _t->applySliderPos(); break;
        case 16: _t->onSongSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: { bool _r = _t->isVideoFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->playNextSong(); break;
        case 19: _t->playPreviousSong(); break;
        case 20: _t->savePlayList(); break;
        case 21: _t->savePlaybackPos(); break;
        case 22: _t->convertAudioToPCM((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
