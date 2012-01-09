/****************************************************************************
** Meta object code from reading C++ file 'service_flite.h'
**
** Created: Thu Jan 5 13:08:36 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serviceFlite/service_flite.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service_flite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CServiceFlite[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CServiceFlite[] = {
    "CServiceFlite\0\0signalSendData()\0"
    "slotUpdate()\0"
};

const QMetaObject CServiceFlite::staticMetaObject = {
    { &CServiceAbstractObject::staticMetaObject, qt_meta_stringdata_CServiceFlite,
      qt_meta_data_CServiceFlite, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CServiceFlite::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CServiceFlite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CServiceFlite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CServiceFlite))
        return static_cast<void*>(const_cast< CServiceFlite*>(this));
    if (!strcmp(_clname, "CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceFlite*>(this));
    if (!strcmp(_clname, "projet_c2a.CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceFlite*>(this));
    return CServiceAbstractObject::qt_metacast(_clname);
}

int CServiceFlite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CServiceAbstractObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalSendData(); break;
        case 1: slotUpdate(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CServiceFlite::signalSendData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
