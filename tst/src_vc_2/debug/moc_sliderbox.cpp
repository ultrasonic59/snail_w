/****************************************************************************
** Meta object code from reading C++ file 'sliderbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgets/sliderbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sliderbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SliderBox_t {
    QByteArrayData data[13];
    char stringdata[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SliderBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SliderBox_t qt_meta_stringdata_SliderBox = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 16),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 12),
QT_MOC_LITERAL(4, 41, 7),
QT_MOC_LITERAL(5, 49, 7),
QT_MOC_LITERAL(6, 57, 19),
QT_MOC_LITERAL(7, 77, 27),
QT_MOC_LITERAL(8, 105, 27),
QT_MOC_LITERAL(9, 133, 6),
QT_MOC_LITERAL(10, 140, 24),
QT_MOC_LITERAL(11, 165, 5),
QT_MOC_LITERAL(12, 171, 19)
    },
    "SliderBox\0valueUserChanged\0\0valueChanged\0"
    "toggled\0checked\0onTimerValueChanged\0"
    "on_txtValue_editingFinished\0"
    "on_sliValue_actionTriggered\0action\0"
    "on_sliValue_valueChanged\0value\0"
    "on_chkTitle_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SliderBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   59,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    1,   61,    2, 0x08 /* Private */,
      10,    1,   64,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Bool,    5,

       0        // eod
};

void SliderBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SliderBox *_t = static_cast<SliderBox *>(_o);
        switch (_id) {
        case 0: _t->valueUserChanged(); break;
        case 1: _t->valueChanged(); break;
        case 2: _t->toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onTimerValueChanged(); break;
        case 4: _t->on_txtValue_editingFinished(); break;
        case 5: _t->on_sliValue_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_sliValue_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_chkTitle_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SliderBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SliderBox::valueUserChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (SliderBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SliderBox::valueChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (SliderBox::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SliderBox::toggled)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SliderBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SliderBox.data,
      qt_meta_data_SliderBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *SliderBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SliderBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SliderBox.stringdata))
        return static_cast<void*>(const_cast< SliderBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int SliderBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SliderBox::valueUserChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SliderBox::valueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SliderBox::toggled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
