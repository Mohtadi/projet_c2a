/****************************************************************************
** Meta object code from reading C++ file 'plugin_bluetooth.h'
**
** Created: Thu Jan 5 09:42:36 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pluginBluetooth/plugin_bluetooth.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin_bluetooth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPluginBluetoothThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CPluginBluetoothThread[] = {
    "CPluginBluetoothThread\0\0signalThread()\0"
};

const QMetaObject CPluginBluetoothThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CPluginBluetoothThread,
      qt_meta_data_CPluginBluetoothThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPluginBluetoothThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPluginBluetoothThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPluginBluetoothThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPluginBluetoothThread))
        return static_cast<void*>(const_cast< CPluginBluetoothThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CPluginBluetoothThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalThread(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CPluginBluetoothThread::signalThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_CPluginBluetoothThreadSendFile[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CPluginBluetoothThreadSendFile[] = {
    "CPluginBluetoothThreadSendFile\0\0"
    "signalThread()\0"
};

const QMetaObject CPluginBluetoothThreadSendFile::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CPluginBluetoothThreadSendFile,
      qt_meta_data_CPluginBluetoothThreadSendFile, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPluginBluetoothThreadSendFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPluginBluetoothThreadSendFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPluginBluetoothThreadSendFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPluginBluetoothThreadSendFile))
        return static_cast<void*>(const_cast< CPluginBluetoothThreadSendFile*>(this));
    return QThread::qt_metacast(_clname);
}

int CPluginBluetoothThreadSendFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalThread(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CPluginBluetoothThreadSendFile::signalThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_CPluginBluetooth[] = {

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
      18,   17,   17,   17, 0x05,
      53,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   76,   17,   17, 0x0a,
     108,   17,   17,   17, 0x0a,
     123,   17,   17,   17, 0x0a,
     140,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CPluginBluetooth[] = {
    "CPluginBluetooth\0\0signalDisconnect(CPluginAbstract*)\0"
    "signalUpdateServices()\0_data\0"
    "slotReceiveData(QString&)\0slotSendData()\0"
    "slotDisconnect()\0slotThread()\0"
};

const QMetaObject CPluginBluetooth::staticMetaObject = {
    { &CPluginAbstractObject::staticMetaObject, qt_meta_stringdata_CPluginBluetooth,
      qt_meta_data_CPluginBluetooth, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPluginBluetooth::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPluginBluetooth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPluginBluetooth::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPluginBluetooth))
        return static_cast<void*>(const_cast< CPluginBluetooth*>(this));
    if (!strcmp(_clname, "CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginBluetooth*>(this));
    if (!strcmp(_clname, "projet_c2a.CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginBluetooth*>(this));
    return CPluginAbstractObject::qt_metacast(_clname);
}

int CPluginBluetooth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 5: slotThread(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CPluginBluetooth::signalDisconnect(CPluginAbstract * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPluginBluetooth::signalUpdateServices()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
