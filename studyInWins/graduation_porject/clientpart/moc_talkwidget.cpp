/****************************************************************************
** Meta object code from reading C++ file 'talkwidget.h'
**
** Created: Sun May 31 21:32:32 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "talkwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'talkwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_talkwidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      24,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_talkwidget[] = {
    "talkwidget\0\0presssend()\0presscancel()\0"
};

const QMetaObject talkwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_talkwidget,
      qt_meta_data_talkwidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &talkwidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *talkwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *talkwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_talkwidget))
        return static_cast<void*>(const_cast< talkwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int talkwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: presssend(); break;
        case 1: presscancel(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
