/****************************************************************************
** Meta object code from reading C++ file 'plugin_abstract_serial_port.h'
**
** Created: Thu Jan 5 09:42:15 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../interface/pluginAbstractSerialPort/plugin_abstract_serial_port.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin_abstract_serial_port.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPluginAbstractSerialPort[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CPluginAbstractSerialPort[] = {
    "CPluginAbstractSerialPort\0"
};

const QMetaObject CPluginAbstractSerialPort::staticMetaObject = {
    { &CPluginAbstractObject::staticMetaObject, qt_meta_stringdata_CPluginAbstractSerialPort,
      qt_meta_data_CPluginAbstractSerialPort, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPluginAbstractSerialPort::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPluginAbstractSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPluginAbstractSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPluginAbstractSerialPort))
        return static_cast<void*>(const_cast< CPluginAbstractSerialPort*>(this));
    if (!strcmp(_clname, "CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginAbstractSerialPort*>(this));
    return CPluginAbstractObject::qt_metacast(_clname);
}

int CPluginAbstractSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CPluginAbstractObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
