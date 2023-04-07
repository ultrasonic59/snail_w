/****************************************************************************
** Meta object code from reading C++ file 'firm_upd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../firm_upd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'firm_upd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Cfirm_upd_t {
    QByteArrayData data[12];
    char stringdata[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cfirm_upd_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cfirm_upd_t qt_meta_stringdata_Cfirm_upd = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 24),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 18),
QT_MOC_LITERAL(4, 55, 10),
QT_MOC_LITERAL(5, 66, 12),
QT_MOC_LITERAL(6, 79, 11),
QT_MOC_LITERAL(7, 91, 10),
QT_MOC_LITERAL(8, 102, 3),
QT_MOC_LITERAL(9, 106, 18),
QT_MOC_LITERAL(10, 125, 11),
QT_MOC_LITERAL(11, 137, 11)
    },
    "Cfirm_upd\0hardwareResponseFinished\0\0"
    "refresh_used_ports\0connection\0"
    "on_file_path\0progr_flash\0set_pb_val\0"
    "val\0serialDataReceived\0serialError\0"
    "serialReady"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cfirm_upd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    1,   64,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,
      10,    0,   68,    2, 0x0a /* Public */,
      11,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Cfirm_upd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Cfirm_upd *_t = static_cast<Cfirm_upd *>(_o);
        switch (_id) {
        case 0: _t->hardwareResponseFinished(); break;
        case 1: _t->refresh_used_ports(); break;
        case 2: _t->connection(); break;
        case 3: _t->on_file_path(); break;
        case 4: _t->progr_flash(); break;
        case 5: _t->set_pb_val((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->serialDataReceived(); break;
        case 7: _t->serialError(); break;
        case 8: _t->serialReady(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Cfirm_upd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Cfirm_upd::hardwareResponseFinished)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Cfirm_upd::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Cfirm_upd.data,
      qt_meta_data_Cfirm_upd,  qt_static_metacall, 0, 0}
};


const QMetaObject *Cfirm_upd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cfirm_upd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Cfirm_upd.stringdata))
        return static_cast<void*>(const_cast< Cfirm_upd*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Cfirm_upd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Cfirm_upd::hardwareResponseFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
