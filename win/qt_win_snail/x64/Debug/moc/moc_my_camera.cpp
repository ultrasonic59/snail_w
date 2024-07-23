/****************************************************************************
** Meta object code from reading C++ file 'my_camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../camera/my_camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyCamera_t {
    QByteArrayData data[23];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyCamera_t qt_meta_stringdata_MyCamera = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyCamera"
QT_MOC_LITERAL(1, 9, 12), // "frameUpdated"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "cv::Mat&"
QT_MOC_LITERAL(4, 32, 6), // "_cvmat"
QT_MOC_LITERAL(5, 39, 14), // "QImage::Format"
QT_MOC_LITERAL(6, 54, 6), // "format"
QT_MOC_LITERAL(7, 61, 12), // "selectDevice"
QT_MOC_LITERAL(8, 74, 4), // "open"
QT_MOC_LITERAL(9, 79, 5), // "pause"
QT_MOC_LITERAL(10, 85, 6), // "resume"
QT_MOC_LITERAL(11, 92, 5), // "close"
QT_MOC_LITERAL(12, 98, 13), // "nextTransform"
QT_MOC_LITERAL(13, 112, 12), // "setTransform"
QT_MOC_LITERAL(14, 125, 14), // "FrameTransform"
QT_MOC_LITERAL(15, 140, 9), // "transform"
QT_MOC_LITERAL(16, 150, 21), // "setViewfinderSettings"
QT_MOC_LITERAL(17, 172, 16), // "__transformFrame"
QT_MOC_LITERAL(18, 189, 7), // "cv::Mat"
QT_MOC_LITERAL(19, 197, 4), // "_mat"
QT_MOC_LITERAL(20, 202, 9), // "__onError"
QT_MOC_LITERAL(21, 212, 14), // "QCamera::Error"
QT_MOC_LITERAL(22, 227, 6) // "_error"

    },
    "MyCamera\0frameUpdated\0\0cv::Mat&\0_cvmat\0"
    "QImage::Format\0format\0selectDevice\0"
    "open\0pause\0resume\0close\0nextTransform\0"
    "setTransform\0FrameTransform\0transform\0"
    "setViewfinderSettings\0__transformFrame\0"
    "cv::Mat\0_mat\0__onError\0QCamera::Error\0"
    "_error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyCamera[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,
      13,    1,   80,    2, 0x0a /* Public */,
      16,    0,   83,    2, 0x0a /* Public */,
      17,    2,   84,    2, 0x08 /* Private */,
      20,    1,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 5,   19,    6,
    QMetaType::Void, 0x80000000 | 21,   22,

       0        // eod
};

void MyCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyCamera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->frameUpdated((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QImage::Format(*)>(_a[2]))); break;
        case 1: _t->selectDevice(); break;
        case 2: { bool _r = _t->open();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->pause(); break;
        case 4: _t->resume(); break;
        case 5: _t->close(); break;
        case 6: _t->nextTransform(); break;
        case 7: _t->setTransform((*reinterpret_cast< FrameTransform(*)>(_a[1]))); break;
        case 8: _t->setViewfinderSettings(); break;
        case 9: _t->__transformFrame((*reinterpret_cast< const cv::Mat(*)>(_a[1])),(*reinterpret_cast< QImage::Format(*)>(_a[2]))); break;
        case 10: _t->__onError((*reinterpret_cast< QCamera::Error(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCamera::Error >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyCamera::*)(cv::Mat & , QImage::Format );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyCamera::frameUpdated)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyCamera::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MyCamera.data,
    qt_meta_data_MyCamera,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyCamera.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MyCamera::frameUpdated(cv::Mat & _t1, QImage::Format _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
