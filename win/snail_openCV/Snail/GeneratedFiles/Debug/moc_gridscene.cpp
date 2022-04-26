/****************************************************************************
** Meta object code from reading C++ file 'gridscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gridscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gridscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GridScene_t {
    QByteArrayData data[9];
    char stringdata[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GridScene_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GridScene_t qt_meta_stringdata_GridScene = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 20),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 6),
QT_MOC_LITERAL(4, 39, 26),
QT_MOC_LITERAL(5, 66, 10),
QT_MOC_LITERAL(6, 77, 8),
QT_MOC_LITERAL(7, 86, 31),
QT_MOC_LITERAL(8, 118, 4)
    },
    "GridScene\0changeCursorPosition\0\0newPos\0"
    "addPointInBoardPointsModel\0BoardPoint\0"
    "newPoint\0removePointFromBoardPointsModel\0"
    "indx"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GridScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       7,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void GridScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GridScene *_t = static_cast<GridScene *>(_o);
        switch (_id) {
        case 0: _t->changeCursorPosition((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->addPointInBoardPointsModel((*reinterpret_cast< const BoardPoint(*)>(_a[1]))); break;
        case 2: _t->removePointFromBoardPointsModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GridScene::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GridScene::changeCursorPosition)) {
                *result = 0;
            }
        }
        {
            typedef void (GridScene::*_t)(const BoardPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GridScene::addPointInBoardPointsModel)) {
                *result = 1;
            }
        }
        {
            typedef void (GridScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GridScene::removePointFromBoardPointsModel)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject GridScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_GridScene.data,
      qt_meta_data_GridScene,  qt_static_metacall, 0, 0}
};


const QMetaObject *GridScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GridScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GridScene.stringdata))
        return static_cast<void*>(const_cast< GridScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int GridScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GridScene::changeCursorPosition(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GridScene::addPointInBoardPointsModel(const BoardPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GridScene::removePointFromBoardPointsModel(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
