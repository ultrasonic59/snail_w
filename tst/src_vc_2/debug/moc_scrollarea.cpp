/****************************************************************************
** Meta object code from reading C++ file 'scrollarea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgets/scrollarea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scrollarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScrollArea_t {
    QByteArrayData data[11];
    char stringdata[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScrollArea_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScrollArea_t qt_meta_stringdata_ScrollArea = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 15),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 20),
QT_MOC_LITERAL(4, 49, 7),
QT_MOC_LITERAL(5, 57, 31),
QT_MOC_LITERAL(6, 89, 8),
QT_MOC_LITERAL(7, 98, 8),
QT_MOC_LITERAL(8, 107, 2),
QT_MOC_LITERAL(9, 110, 2),
QT_MOC_LITERAL(10, 113, 9)
    },
    "ScrollArea\0sizeHintRequest\0\0"
    "onContentSizeChanged\0newSize\0"
    "onVerticalScrollBarValueChanged\0"
    "newValue\0onScroll\0dx\0dy\0onPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScrollArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       7,    2,   46,    2, 0x08 /* Private */,
      10,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QSize,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,

       0        // eod
};

void ScrollArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScrollArea *_t = static_cast<ScrollArea *>(_o);
        switch (_id) {
        case 0: _t->sizeHintRequest(); break;
        case 1: _t->onContentSizeChanged((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 2: _t->onVerticalScrollBarValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onScroll((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->onPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScrollArea::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScrollArea::sizeHintRequest)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ScrollArea::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata_ScrollArea.data,
      qt_meta_data_ScrollArea,  qt_static_metacall, 0, 0}
};


const QMetaObject *ScrollArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScrollArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScrollArea.stringdata))
        return static_cast<void*>(const_cast< ScrollArea*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int ScrollArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ScrollArea::sizeHintRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
