/****************************************************************************
** Meta object code from reading C++ file 'dial_debug.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../dial_debug/dial_debug.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dial_debug.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialDebug_t {
    QByteArrayData data[16];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialDebug_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialDebug_t qt_meta_stringdata_DialDebug = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DialDebug"
QT_MOC_LITERAL(1, 10, 10), // "req_wr_dbg"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "num"
QT_MOC_LITERAL(4, 26, 14), // "dbg_dat_req_t*"
QT_MOC_LITERAL(5, 41, 10), // "req_rd_dbg"
QT_MOC_LITERAL(6, 52, 10), // "SignalTest"
QT_MOC_LITERAL(7, 63, 12), // "slot_butt_rd"
QT_MOC_LITERAL(8, 76, 12), // "slot_butt_wr"
QT_MOC_LITERAL(9, 89, 16), // "req_dbg_data_rdy"
QT_MOC_LITERAL(10, 106, 16), // "req_xil_data_rdy"
QT_MOC_LITERAL(11, 123, 14), // "xil_dat_req_t*"
QT_MOC_LITERAL(12, 138, 11), // "req_str_rdy"
QT_MOC_LITERAL(13, 150, 5), // "char*"
QT_MOC_LITERAL(14, 156, 8), // "SlotTest"
QT_MOC_LITERAL(15, 165, 14) // "clear_textEdit"

    },
    "DialDebug\0req_wr_dbg\0\0num\0dbg_dat_req_t*\0"
    "req_rd_dbg\0SignalTest\0slot_butt_rd\0"
    "slot_butt_wr\0req_dbg_data_rdy\0"
    "req_xil_data_rdy\0xil_dat_req_t*\0"
    "req_str_rdy\0char*\0SlotTest\0clear_textEdit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialDebug[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       5,    2,   69,    2, 0x06 /* Public */,
       6,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      12,    1,   83,    2, 0x08 /* Private */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DialDebug::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DialDebug *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->req_wr_dbg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< dbg_dat_req_t*(*)>(_a[2]))); break;
        case 1: _t->req_rd_dbg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< dbg_dat_req_t*(*)>(_a[2]))); break;
        case 2: _t->SignalTest(); break;
        case 3: _t->slot_butt_rd(); break;
        case 4: _t->slot_butt_wr(); break;
        case 5: _t->req_dbg_data_rdy((*reinterpret_cast< dbg_dat_req_t*(*)>(_a[1]))); break;
        case 6: _t->req_xil_data_rdy((*reinterpret_cast< xil_dat_req_t*(*)>(_a[1]))); break;
        case 7: _t->req_str_rdy((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 8: _t->SlotTest(); break;
        case 9: _t->clear_textEdit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DialDebug::*)(int , dbg_dat_req_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialDebug::req_wr_dbg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DialDebug::*)(int , dbg_dat_req_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialDebug::req_rd_dbg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DialDebug::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialDebug::SignalTest)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DialDebug::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_DialDebug.data,
    qt_meta_data_DialDebug,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DialDebug::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialDebug::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialDebug.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialDebug::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DialDebug::req_wr_dbg(int _t1, dbg_dat_req_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DialDebug::req_rd_dbg(int _t1, dbg_dat_req_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DialDebug::SignalTest()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
