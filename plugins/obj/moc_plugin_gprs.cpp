/****************************************************************************
** Meta object code from reading C++ file 'plugin_gprs.h'
**
** Created: Thu Jan 5 09:42:32 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pluginGPRS/plugin_gprs.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin_gprs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPluginGPRS[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      48,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      77,   71,   12,   12, 0x0a,
     103,   12,   12,   12, 0x0a,
     118,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CPluginGPRS[] = {
    "CPluginGPRS\0\0signalDisconnect(CPluginAbstract*)\0"
    "signalUpdateServices()\0_data\0"
    "slotReceiveData(QString&)\0slotSendData()\0"
    "slotDisconnect()\0"
};

const QMetaObject CPluginGPRS::staticMetaObject = {
    { &CPluginAbstractSerialPort::staticMetaObject, qt_meta_stringdata_CPluginGPRS,
      qt_meta_data_CPluginGPRS, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPluginGPRS::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPluginGPRS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPluginGPRS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPluginGPRS))
        return static_cast<void*>(const_cast< CPluginGPRS*>(this));
    if (!strcmp(_clname, "projet_c2a.CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginGPRS*>(this));
    return CPluginAbstractSerialPort::qt_metacast(_clname);
}

int CPluginGPRS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CPluginAbstractSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalDisconnect((*reinterpret_cast< CPluginAbstract*(*)>(_a[1]))); break;
        case 1: signalUpdateServices(); break;
        case 2: slotReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: slotSendData(); break;
        case 4: slotDisconnect(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CPluginGPRS::signalDisconnect(CPluginAbstract * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPluginGPRS::signalUpdateServices()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
