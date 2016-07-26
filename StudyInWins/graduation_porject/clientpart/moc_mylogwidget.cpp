/****************************************************************************
** Meta object code from reading C++ file 'mylogwidget.h'
**
** Created: Sat Jun 13 03:49:11 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mylogwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mylogwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mylogwidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      21,   12,   12,   12, 0x0a,
      34,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mylogwidget[] = {
    "mylogwidget\0\0login()\0presslogin()\0"
    "pressregister()\0"
};

const QMetaObject mylogwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mylogwidget,
      qt_meta_data_mylogwidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mylogwidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mylogwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mylogwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mylogwidget))
        return static_cast<void*>(const_cast< mylogwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int mylogwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: login(); break;
        case 1: presslogin(); break;
        case 2: pressregister(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void mylogwidget::login()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
