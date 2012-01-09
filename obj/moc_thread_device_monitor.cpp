/****************************************************************************
** Meta object code from reading C++ file 'thread_device_monitor.h'
**
** Created: Fri Jan 6 09:26:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/thread_device_monitor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thread_device_monitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CThreadDeviceMonitor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      51,   43,   21,   21, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CThreadDeviceMonitor[] = {
    "CThreadDeviceMonitor\0\0signalSearchPlugin()\0"
    "_device\0signalDisplaySearchPlugin(CDevice*)\0"
};

const QMetaObject CThreadDeviceMonitor::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CThreadDeviceMonitor,
      qt_meta_data_CThreadDeviceMonitor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CThreadDeviceMonitor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CThreadDeviceMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CThreadDeviceMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CThreadDeviceMonitor))
        return static_cast<void*>(const_cast< CThreadDeviceMonitor*>(this));
    return QThread::qt_metacast(_clname);
}

int CThreadDeviceMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalSearchPlugin(); break;
        case 1: signalDisplaySearchPlugin((*reinterpret_cast< CDevice*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CThreadDeviceMonitor::signalSearchPlugin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CThreadDeviceMonitor::signalDisplaySearchPlugin(CDevice * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
