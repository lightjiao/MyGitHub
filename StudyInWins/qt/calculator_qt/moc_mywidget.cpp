/****************************************************************************
** Meta object code from reading C++ file 'mywidget.h'
**
** Created: Wed Sep 7 02:38:39 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mywidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mywidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   24,    9,    9, 0x0a,
      53,   47,    9,    9, 0x0a,
      72,    9,    9,    9, 0x2a,
      87,   47,    9,    9, 0x0a,
     106,    9,    9,    9, 0x2a,
     121,   47,    9,    9, 0x0a,
     140,    9,    9,    9, 0x2a,
     155,   47,    9,    9, 0x0a,
     174,    9,    9,    9, 0x2a,
     189,   47,    9,    9, 0x0a,
     208,    9,    9,    9, 0x2a,
     223,   47,    9,    9, 0x0a,
     242,    9,    9,    9, 0x2a,
     257,   47,    9,    9, 0x0a,
     276,    9,    9,    9, 0x2a,
     291,   47,    9,    9, 0x0a,
     310,    9,    9,    9, 0x2a,
     325,   47,    9,    9, 0x0a,
     344,    9,    9,    9, 0x2a,
     359,   47,    9,    9, 0x0a,
     378,    9,    9,    9, 0x2a,
     393,   47,    9,    9, 0x0a,
     413,    9,    9,    9, 0x2a,
     429,   47,    9,    9, 0x0a,
     449,    9,    9,    9, 0x2a,
     465,   47,    9,    9, 0x0a,
     486,    9,    9,    9, 0x2a,
     503,   47,    9,    9, 0x0a,
     524,    9,    9,    9, 0x2a,
     541,   47,    9,    9, 0x0a,
     562,    9,    9,    9, 0x2a,
     579,   47,    9,    9, 0x0a,
     600,    9,    9,    9, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_mywidget[] = {
    "mywidget\0\0bclicked(int)\0witch\0"
    "pressbutton(int)\0check\0pressbutton0(bool)\0"
    "pressbutton0()\0pressbutton1(bool)\0"
    "pressbutton1()\0pressbutton2(bool)\0"
    "pressbutton2()\0pressbutton3(bool)\0"
    "pressbutton3()\0pressbutton4(bool)\0"
    "pressbutton4()\0pressbutton5(bool)\0"
    "pressbutton5()\0pressbutton6(bool)\0"
    "pressbutton6()\0pressbutton7(bool)\0"
    "pressbutton7()\0pressbutton8(bool)\0"
    "pressbutton8()\0pressbutton9(bool)\0"
    "pressbutton9()\0pressbuttonac(bool)\0"
    "pressbuttonac()\0pressbuttoneq(bool)\0"
    "pressbuttoneq()\0pressbuttonadd(bool)\0"
    "pressbuttonadd()\0pressbuttonsub(bool)\0"
    "pressbuttonsub()\0pressbuttonmul(bool)\0"
    "pressbuttonmul()\0pressbuttondiv(bool)\0"
    "pressbuttondiv()\0"
};

const QMetaObject mywidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mywidget,
      qt_meta_data_mywidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mywidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mywidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mywidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mywidget))
        return static_cast<void*>(const_cast< mywidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int mywidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: bclicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: pressbutton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: pressbutton0((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: pressbutton0(); break;
        case 4: pressbutton1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: pressbutton1(); break;
        case 6: pressbutton2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: pressbutton2(); break;
        case 8: pressbutton3((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: pressbutton3(); break;
        case 10: pressbutton4((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: pressbutton4(); break;
        case 12: pressbutton5((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: pressbutton5(); break;
        case 14: pressbutton6((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: pressbutton6(); break;
        case 16: pressbutton7((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: pressbutton7(); break;
        case 18: pressbutton8((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: pressbutton8(); break;
        case 20: pressbutton9((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: pressbutton9(); break;
        case 22: pressbuttonac((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: pressbuttonac(); break;
        case 24: pressbuttoneq((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: pressbuttoneq(); break;
        case 26: pressbuttonadd((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: pressbuttonadd(); break;
        case 28: pressbuttonsub((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: pressbuttonsub(); break;
        case 30: pressbuttonmul((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: pressbuttonmul(); break;
        case 32: pressbuttondiv((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: pressbuttondiv(); break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void mywidget::bclicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
