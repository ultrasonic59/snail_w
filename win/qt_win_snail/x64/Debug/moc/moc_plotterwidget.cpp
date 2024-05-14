/****************************************************************************
** Meta object code from reading C++ file 'plotterwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../widgets/plotterwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotterwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_plotterwidget_t {
    QByteArrayData data[11];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_plotterwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_plotterwidget_t qt_meta_stringdata_plotterwidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "plotterwidget"
QT_MOC_LITERAL(1, 14, 9), // "_setImage"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "updateImage"
QT_MOC_LITERAL(4, 37, 8), // "cv::Mat&"
QT_MOC_LITERAL(5, 46, 6), // "_cvmat"
QT_MOC_LITERAL(6, 53, 14), // "QImage::Format"
QT_MOC_LITERAL(7, 68, 7), // "_format"
QT_MOC_LITERAL(8, 76, 12), // "_updateImage"
QT_MOC_LITERAL(9, 89, 5), // "_qimg"
QT_MOC_LITERAL(10, 95, 7) // "cv::Mat"

    },
    "plotterwidget\0_setImage\0\0updateImage\0"
    "cv::Mat&\0_cvmat\0QImage::Format\0_format\0"
    "_updateImage\0_qimg\0cv::Mat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plotterwidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       3,    2,   37,    2, 0x0a /* Public */,
       8,    1,   42,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::QImage,    9,
    QMetaType::Void, 0x80000000 | 10,    5,

       0        // eod
};

void plotterwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<plotterwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_setImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->updateImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QImage::Format(*)>(_a[2]))); break;
        case 2: _t->_updateImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 3: _t->_updateImage((*reinterpret_cast< const cv::Mat(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject plotterwidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_plotterwidget.data,
    qt_meta_data_plotterwidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *plotterwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plotterwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_plotterwidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int plotterwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
