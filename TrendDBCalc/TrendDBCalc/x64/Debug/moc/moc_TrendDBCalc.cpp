/****************************************************************************
** Meta object code from reading C++ file 'TrendDBCalc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../TrendDBCalc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrendDBCalc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrendDBCalc_t {
    QByteArrayData data[20];
    char stringdata0[444];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrendDBCalc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrendDBCalc_t qt_meta_stringdata_TrendDBCalc = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TrendDBCalc"
QT_MOC_LITERAL(1, 12, 22), // "on_tableWidget_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 41), // "on_tableWidget_customContextM..."
QT_MOC_LITERAL(5, 84, 3), // "pos"
QT_MOC_LITERAL(6, 88, 40), // "on_treeWidget_customContextMe..."
QT_MOC_LITERAL(7, 129, 22), // "on_tableWidget_entered"
QT_MOC_LITERAL(8, 152, 23), // "on_actionexit_triggered"
QT_MOC_LITERAL(9, 176, 24), // "on_actionstart_triggered"
QT_MOC_LITERAL(10, 201, 22), // "on_actionend_triggered"
QT_MOC_LITERAL(11, 224, 23), // "on_actionconf_triggered"
QT_MOC_LITERAL(12, 248, 22), // "on_actionadd_triggered"
QT_MOC_LITERAL(13, 271, 23), // "on_actionedit_triggered"
QT_MOC_LITERAL(14, 295, 25), // "on_actiondelete_triggered"
QT_MOC_LITERAL(15, 321, 25), // "on_actionimport_triggered"
QT_MOC_LITERAL(16, 347, 25), // "on_actionexport_triggered"
QT_MOC_LITERAL(17, 373, 23), // "on_actionsave_triggered"
QT_MOC_LITERAL(18, 397, 24), // "on_actionclear_triggered"
QT_MOC_LITERAL(19, 422, 21) // "on_pushButton_clicked"

    },
    "TrendDBCalc\0on_tableWidget_clicked\0\0"
    "index\0on_tableWidget_customContextMenuRequested\0"
    "pos\0on_treeWidget_customContextMenuRequested\0"
    "on_tableWidget_entered\0on_actionexit_triggered\0"
    "on_actionstart_triggered\0"
    "on_actionend_triggered\0on_actionconf_triggered\0"
    "on_actionadd_triggered\0on_actionedit_triggered\0"
    "on_actiondelete_triggered\0"
    "on_actionimport_triggered\0"
    "on_actionexport_triggered\0"
    "on_actionsave_triggered\0"
    "on_actionclear_triggered\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrendDBCalc[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x08 /* Private */,
       4,    1,   97,    2, 0x08 /* Private */,
       6,    1,  100,    2, 0x08 /* Private */,
       7,    1,  103,    2, 0x08 /* Private */,
       8,    0,  106,    2, 0x08 /* Private */,
       9,    0,  107,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    0,  109,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QPoint,    5,
    QMetaType::Void, QMetaType::QPoint,    5,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TrendDBCalc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrendDBCalc *_t = static_cast<TrendDBCalc *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_tableWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_tableWidget_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: _t->on_treeWidget_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->on_tableWidget_entered((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_actionexit_triggered(); break;
        case 5: _t->on_actionstart_triggered(); break;
        case 6: _t->on_actionend_triggered(); break;
        case 7: _t->on_actionconf_triggered(); break;
        case 8: _t->on_actionadd_triggered(); break;
        case 9: _t->on_actionedit_triggered(); break;
        case 10: _t->on_actiondelete_triggered(); break;
        case 11: _t->on_actionimport_triggered(); break;
        case 12: _t->on_actionexport_triggered(); break;
        case 13: _t->on_actionsave_triggered(); break;
        case 14: _t->on_actionclear_triggered(); break;
        case 15: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject TrendDBCalc::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TrendDBCalc.data,
      qt_meta_data_TrendDBCalc,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TrendDBCalc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrendDBCalc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrendDBCalc.stringdata0))
        return static_cast<void*>(const_cast< TrendDBCalc*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TrendDBCalc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE