/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Sat Jun 13 10:16:47 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainwidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      21,   11,   11,   11, 0x0a,
      33,   11,   11,   11, 0x0a,
      47,   11,   11,   11, 0x0a,
      72,   67,   11,   11, 0x0a,
     107,   11,   11,   11, 0x0a,
     127,  119,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainwidget[] = {
    "mainwidget\0\0logout()\0presssend()\0"
    "presscancel()\0preparegetmessage()\0"
    "item\0createchatwidget(QListWidgetItem*)\0"
    "writeface()\0facenum\0sendface(int)\0"
};

const QMetaObject mainwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mainwidget,
      qt_meta_data_mainwidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainwidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainwidget))
        return static_cast<void*>(const_cast< mainwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int mainwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: logout(); break;
        case 1: presssend(); break;
        case 2: presscancel(); break;
        case 3: preparegetmessage(); break;
        case 4: createchatwidget((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: writeface(); break;
        case 6: sendface((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void mainwidget::logout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
