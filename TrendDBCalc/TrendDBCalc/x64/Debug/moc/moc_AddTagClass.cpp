/****************************************************************************
** Meta object code from reading C++ file 'AddTagClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../AddTagClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddTagClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddTagClass_t {
    QByteArrayData data[11];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddTagClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddTagClass_t qt_meta_stringdata_AddTagClass = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AddTagClass"
QT_MOC_LITERAL(1, 12, 8), // "OkSignal"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "addName"
QT_MOC_LITERAL(4, 30, 8), // "describe"
QT_MOC_LITERAL(5, 39, 9), // "addscript"
QT_MOC_LITERAL(6, 49, 11), // "addinterval"
QT_MOC_LITERAL(7, 61, 10), // "TestSignal"
QT_MOC_LITERAL(8, 72, 24), // "on_pushButton_ok_clicked"
QT_MOC_LITERAL(9, 97, 28), // "on_pushButton_cancel_clicked"
QT_MOC_LITERAL(10, 126, 26) // "on_pushButton_test_clicked"

    },
    "AddTagClass\0OkSignal\0\0addName\0describe\0"
    "addscript\0addinterval\0TestSignal\0"
    "on_pushButton_ok_clicked\0"
    "on_pushButton_cancel_clicked\0"
    "on_pushButton_test_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddTagClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   39,    2, 0x06 /* Public */,
       7,    2,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   53,    2, 0x08 /* Private */,
       9,    0,   54,    2, 0x08 /* Private */,
      10,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddTagClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddTagClass *_t = static_cast<AddTagClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OkSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->TestSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->on_pushButton_ok_clicked(); break;
        case 3: _t->on_pushButton_cancel_clicked(); break;
        case 4: _t->on_pushButton_test_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AddTagClass::*_t)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AddTagClass::OkSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AddTagClass::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AddTagClass::TestSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject AddTagClass::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AddTagClass.data,
      qt_meta_data_AddTagClass,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AddTagClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddTagClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddTagClass.stringdata0))
        return static_cast<void*>(const_cast< AddTagClass*>(this));
    return QWidget::qt_metacast(_clname);
}

int AddTagClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void AddTagClass::OkSignal(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AddTagClass::TestSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE