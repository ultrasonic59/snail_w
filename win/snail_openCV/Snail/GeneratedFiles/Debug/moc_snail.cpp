/****************************************************************************
** Meta object code from reading C++ file 'snail.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../snail.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'snail.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Snail_t {
    QByteArrayData data[9];
    char stringdata[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Snail_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Snail_t qt_meta_stringdata_Snail = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 17),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 18),
QT_MOC_LITERAL(4, 44, 23),
QT_MOC_LITERAL(5, 68, 21),
QT_MOC_LITERAL(6, 90, 26),
QT_MOC_LITERAL(7, 117, 19),
QT_MOC_LITERAL(8, 137, 6)
    },
    "Snail\0adjustImgFinished\0\0on_btnLoad_clicked\0"
    "on_btnAdjustImg_clicked\0on_btnAdjGrid_clicked\0"
    "on_btnUploadPoints_clicked\0"
    "slotSetInitialState\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Snail[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Snail::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Snail *_t = static_cast<Snail *>(_o);
        switch (_id) {
        case 0: _t->adjustImgFinished(); break;
        case 1: _t->on_btnLoad_clicked(); break;
        case 2: _t->on_btnAdjustImg_clicked(); break;
        case 3: _t->on_btnAdjGrid_clicked(); break;
        case 4: _t->on_btnUploadPoints_clicked(); break;
        case 5: _t->slotSetInitialState(); break;
        case 6: _t->update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Snail::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Snail::adjustImgFinished)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Snail::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Snail.data,
      qt_meta_data_Snail,  qt_static_metacall, 0, 0}
};


const QMetaObject *Snail::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Snail::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Snail.stringdata))
        return static_cast<void*>(const_cast< Snail*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Snail::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Snail::adjustImgFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
