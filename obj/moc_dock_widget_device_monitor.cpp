/****************************************************************************
** Meta object code from reading C++ file 'dock_widget_device_monitor.h'
**
** Created: Fri Jan 6 09:26:41 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/dock_widget_device_monitor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dock_widget_device_monitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CDockWidgetDeviceMonitor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   57,   25,   25, 0x0a,
     109,   57,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CDockWidgetDeviceMonitor[] = {
    "CDockWidgetDeviceMonitor\0\0"
    "signalUpdateInformationsData()\0_device\0"
    "slotUpdateTreeWidgetDeviceMonitor(CDevice*)\0"
    "slotDisplaySearchPlugin(CDevice*)\0"
};

const QMetaObject CDockWidgetDeviceMonitor::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_CDockWidgetDeviceMonitor,
      qt_meta_data_CDockWidgetDeviceMonitor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CDockWidgetDeviceMonitor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CDockWidgetDeviceMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CDockWidgetDeviceMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDockWidgetDeviceMonitor))
        return static_cast<void*>(const_cast< CDockWidgetDeviceMonitor*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int CDockWidgetDeviceMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalUpdateInformationsData(); break;
        case 1: slotUpdateTreeWidgetDeviceMonitor((*reinterpret_cast< CDevice*(*)>(_a[1]))); break;
        case 2: slotDisplaySearchPlugin((*reinterpret_cast< CDevice*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CDockWidgetDeviceMonitor::signalUpdateInformationsData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
