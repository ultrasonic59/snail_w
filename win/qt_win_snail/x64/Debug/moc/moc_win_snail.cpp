/****************************************************************************
** Meta object code from reading C++ file 'win_snail.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../win_snail.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'win_snail.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_win_snail_t {
    QByteArrayData data[14];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_win_snail_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_win_snail_t qt_meta_stringdata_win_snail = {
    {
QT_MOC_LITERAL(0, 0, 9), // "win_snail"
QT_MOC_LITERAL(1, 10, 13), // "updateCamView"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "setCamImage"
QT_MOC_LITERAL(4, 37, 3), // "ipm"
QT_MOC_LITERAL(5, 41, 11), // "on_butt_con"
QT_MOC_LITERAL(6, 53, 13), // "on_butt_debug"
QT_MOC_LITERAL(7, 67, 11), // "slot_rd_dbg"
QT_MOC_LITERAL(8, 79, 3), // "num"
QT_MOC_LITERAL(9, 83, 14), // "dbg_dat_req_t*"
QT_MOC_LITERAL(10, 98, 4), // "odat"
QT_MOC_LITERAL(11, 103, 11), // "slot_wr_dbg"
QT_MOC_LITERAL(12, 115, 4), // "idat"
QT_MOC_LITERAL(13, 120, 19) // "__selectVideoSource"

    },
    "win_snail\0updateCamView\0\0setCamImage\0"
    "ipm\0on_butt_con\0on_butt_debug\0slot_rd_dbg\0"
    "num\0dbg_dat_req_t*\0odat\0slot_wr_dbg\0"
    "idat\0__selectVideoSource"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_win_snail[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   52,    2, 0x0a /* Public */,
       5,    0,   55,    2, 0x0a /* Public */,
       6,    0,   56,    2, 0x0a /* Public */,
       7,    2,   57,    2, 0x0a /* Public */,
      11,    2,   62,    2, 0x0a /* Public */,
      13,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    8,   12,
    QMetaType::Void,

       0        // eod
};

void win_snail::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<win_snail *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateCamView((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->setCamImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->on_butt_con(); break;
        case 3: _t->on_butt_debug(); break;
        case 4: _t->slot_rd_dbg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< dbg_dat_req_t*(*)>(_a[2]))); break;
        case 5: _t->slot_wr_dbg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< dbg_dat_req_t*(*)>(_a[2]))); break;
        case 6: _t->__selectVideoSource(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (win_snail::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&win_snail::updateCamView)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject win_snail::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_win_snail.data,
    qt_meta_data_win_snail,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *win_snail::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *win_snail::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_win_snail.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int win_snail::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void win_snail::updateCamView(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
