/****************************************************************************
** Meta object code from reading C++ file 'device.h'
**
** Created: Fri Jan 6 09:26:39 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/device.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'device.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CDevice[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,    8,    8,    8, 0x0a,
      91,   74,    8,    8, 0x0a,
     124,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CDevice[] = {
    "CDevice\0\0signalUpdateTreeWidgetDeviceMonitor(CDevice*)\0"
    "slotSearchPlugin()\0_abstract_plugin\0"
    "slotDisconnect(CPluginAbstract*)\0"
    "slotUpdateServices()\0"
};

const QMetaObject CDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CDevice,
      qt_meta_data_CDevice, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CDevice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDevice))
        return static_cast<void*>(const_cast< CDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int CDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalUpdateTreeWidgetDeviceMonitor((*reinterpret_cast< CDevice*(*)>(_a[1]))); break;
        case 1: slotSearchPlugin(); break;
        case 2: slotDisconnect((*reinterpret_cast< CPluginAbstract*(*)>(_a[1]))); break;
        case 3: slotUpdateServices(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CDevice::signalUpdateTreeWidgetDeviceMonitor(CDevice * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
