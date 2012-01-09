/****************************************************************************
** Meta object code from reading C++ file 'plugin_corsair.h'
**
** Created: Thu Jan 5 09:42:44 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pluginCorsair/plugin_corsair.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin_corsair.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPluginCorsair[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      51,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   74,   15,   15, 0x0a,
     106,   15,   15,   15, 0x0a,
     121,   15,   15,   15, 0x0a,
     138,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CPluginCorsair[] = {
    "CPluginCorsair\0\0signalDisconnect(CPluginAbstract*)\0"
    "signalUpdateServices()\0_data\0"
    "slotReceiveData(QString&)\0slotSendData()\0"
    "slotDisconnect()\0parseDirectory()\0"
};

const QMetaObject CPluginCorsair::staticMetaObject = {
    { &CPluginAbstractObject::staticMetaObject, qt_meta_stringdata_CPluginCorsair,
      qt_meta_data_CPluginCorsair, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPluginCorsair::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPluginCorsair::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPluginCorsair::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPluginCorsair))
        return static_cast<void*>(const_cast< CPluginCorsair*>(this));
    if (!strcmp(_clname, "CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginCorsair*>(this));
    if (!strcmp(_clname, "projet_c2a.CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginCorsair*>(this));
    return CPluginAbstractObject::qt_metacast(_clname);
}

int CPluginCorsair::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CPluginAbstractObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalDisconnect((*reinterpret_cast< CPluginAbstract*(*)>(_a[1]))); break;
        case 1: signalUpdateServices(); break;
        case 2: slotReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: slotSendData(); break;
        case 4: slotDisconnect(); break;
        case 5: parseDirectory(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CPluginCorsair::signalDisconnect(CPluginAbstract * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPluginCorsair::signalUpdateServices()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
