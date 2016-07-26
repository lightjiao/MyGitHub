/****************************************************************************
** Meta object code from reading C++ file 'myselectfacewidget.h'
**
** Created: Sat Jun 13 10:16:50 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myselectfacewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myselectfacewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myselectfacewidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      34,   19,   19,   19, 0x0a,
      48,   19,   19,   19, 0x0a,
      62,   19,   19,   19, 0x0a,
      76,   19,   19,   19, 0x0a,
      90,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myselectfacewidget[] = {
    "myselectfacewidget\0\0selectface1()\0"
    "selectface2()\0selectface3()\0selectface4()\0"
    "selectface5()\0selectface6()\0"
};

const QMetaObject myselectfacewidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myselectfacewidget,
      qt_meta_data_myselectfacewidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myselectfacewidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myselectfacewidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myselectfacewidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myselectfacewidget))
        return static_cast<void*>(const_cast< myselectfacewidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int myselectfacewidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selectface1(); break;
        case 1: selectface2(); break;
        case 2: selectface3(); break;
        case 3: selectface4(); break;
        case 4: selectface5(); break;
        case 5: selectface6(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
