/****************************************************************************
** Meta object code from reading C++ file 'groupbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgets/groupbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'groupbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GroupBox_t {
    QByteArrayData data[9];
    char stringdata[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GroupBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GroupBox_t qt_meta_stringdata_GroupBox = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 10),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 2),
QT_MOC_LITERAL(4, 24, 2),
QT_MOC_LITERAL(5, 27, 12),
QT_MOC_LITERAL(6, 40, 13),
QT_MOC_LITERAL(7, 54, 7),
QT_MOC_LITERAL(8, 62, 4)
    },
    "GroupBox\0mouseMoved\0\0dx\0dy\0mousePressed\0"
    "mouseReleased\0resized\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GroupBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    0,   39,    2, 0x06 /* Public */,
       6,    0,   40,    2, 0x06 /* Public */,
       7,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,    8,

       0        // eod
};

void GroupBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GroupBox *_t = static_cast<GroupBox *>(_o);
        switch (_id) {
        case 0: _t->mouseMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->mousePressed(); break;
        case 2: _t->mouseReleased(); break;
        case 3: _t->resized((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GroupBox::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupBox::mouseMoved)) {
                *result = 0;
            }
        }
        {
            typedef void (GroupBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupBox::mousePressed)) {
                *result = 1;
            }
        }
        {
            typedef void (GroupBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupBox::mouseReleased)) {
                *result = 2;
            }
        }
        {
            typedef void (GroupBox::*_t)(QSize );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupBox::resized)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject GroupBox::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_GroupBox.data,
      qt_meta_data_GroupBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *GroupBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GroupBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GroupBox.stringdata))
        return static_cast<void*>(const_cast< GroupBox*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int GroupBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GroupBox::mouseMoved(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GroupBox::mousePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GroupBox::mouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GroupBox::resized(QSize _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
