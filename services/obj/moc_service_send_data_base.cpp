/****************************************************************************
** Meta object code from reading C++ file 'service_send_data_base.h'
**
** Created: Mon Jan 9 10:03:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serviceSendDataBase/service_send_data_base.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service_send_data_base.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CServiceSendDataBase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   21,   21,   21, 0x0a,
      52,   21,   21,   21, 0x0a,
      73,   21,   21,   21, 0x0a,
     117,  102,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CServiceSendDataBase[] = {
    "CServiceSendDataBase\0\0signalSendData()\0"
    "slotUpdate()\0slotUpdateDataBase()\0"
    "slotFinished(QNetworkReply*)\0"
    "_network_error\0slotError(QNetworkReply::NetworkError)\0"
};

const QMetaObject CServiceSendDataBase::staticMetaObject = {
    { &CServiceAbstractObject::staticMetaObject, qt_meta_stringdata_CServiceSendDataBase,
      qt_meta_data_CServiceSendDataBase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CServiceSendDataBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CServiceSendDataBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CServiceSendDataBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CServiceSendDataBase))
        return static_cast<void*>(const_cast< CServiceSendDataBase*>(this));
    if (!strcmp(_clname, "CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceSendDataBase*>(this));
    if (!strcmp(_clname, "projet_c2a.CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceSendDataBase*>(this));
    return CServiceAbstractObject::qt_metacast(_clname);
}

int CServiceSendDataBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CServiceAbstractObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalSendData(); break;
        case 1: slotUpdate(); break;
        case 2: slotUpdateDataBase(); break;
        case 3: slotFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: slotError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CServiceSendDataBase::signalSendData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
