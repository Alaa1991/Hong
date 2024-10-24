/****************************************************************************
** Meta object code from reading C++ file 'KVideoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../KVideoWidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KVideoWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSKVideoWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSKVideoWidgetENDCLASS = QtMocHelpers::stringData(
    "KVideoWidget",
    "playRequested",
    "",
    "pauseRequested",
    "fullScreenRequested",
    "exitFullscreenRequested",
    "playPauseToggleReq"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSKVideoWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,
       3,    0,   45,    2, 0x06,    2 /* Public */,
       4,    0,   46,    2, 0x06,    3 /* Public */,
       5,    0,   47,    2, 0x06,    4 /* Public */,
       6,    0,   48,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject KVideoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QVideoWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSKVideoWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSKVideoWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSKVideoWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<KVideoWidget, std::true_type>,
        // method 'playRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pauseRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fullScreenRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitFullscreenRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playPauseToggleReq'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void KVideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KVideoWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->playRequested(); break;
        case 1: _t->pauseRequested(); break;
        case 2: _t->fullScreenRequested(); break;
        case 3: _t->exitFullscreenRequested(); break;
        case 4: _t->playPauseToggleReq(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KVideoWidget::*)();
            if (_t _q_method = &KVideoWidget::playRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KVideoWidget::*)();
            if (_t _q_method = &KVideoWidget::pauseRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (KVideoWidget::*)();
            if (_t _q_method = &KVideoWidget::fullScreenRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (KVideoWidget::*)();
            if (_t _q_method = &KVideoWidget::exitFullscreenRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (KVideoWidget::*)();
            if (_t _q_method = &KVideoWidget::playPauseToggleReq; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *KVideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KVideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSKVideoWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QVideoWidget::qt_metacast(_clname);
}

int KVideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVideoWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void KVideoWidget::playRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void KVideoWidget::pauseRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void KVideoWidget::fullScreenRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void KVideoWidget::exitFullscreenRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void KVideoWidget::playPauseToggleReq()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
