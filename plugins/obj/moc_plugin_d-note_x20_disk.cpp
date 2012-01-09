/****************************************************************************
** Meta object code from reading C++ file 'plugin_d-note_x20_disk.h'
**
** Created: Thu Jan 5 09:42:28 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pluginD-Notex20Disk/plugin_d-note_x20_disk.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin_d-note_x20_disk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPluginDNoteX20Disk[] = {

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
      21,   20,   20,   20, 0x05,
      56,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   79,   20,   20, 0x0a,
     111,   20,   20,   20, 0x0a,
     126,   20,   20,   20, 0x0a,
     143,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CPluginDNoteX20Disk[] = {
    "CPluginDNoteX20Disk\0\0"
    "signalDisconnect(CPluginAbstract*)\0"
    "signalUpdateServices()\0_data\0"
    "slotReceiveData(QString&)\0slotSendData()\0"
    "slotDisconnect()\0parseDirectory()\0"
};

const QMetaObject CPluginDNoteX20Disk::staticMetaObject = {
    { &CPluginAbstractObject::staticMetaObject, qt_meta_stringdata_CPluginDNoteX20Disk,
      qt_meta_data_CPluginDNoteX20Disk, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPluginDNoteX20Disk::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPluginDNoteX20Disk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPluginDNoteX20Disk::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPluginDNoteX20Disk))
        return static_cast<void*>(const_cast< CPluginDNoteX20Disk*>(this));
    if (!strcmp(_clname, "CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginDNoteX20Disk*>(this));
    if (!strcmp(_clname, "projet_c2a.CPluginAbstract"))
        return static_cast< CPluginAbstract*>(const_cast< CPluginDNoteX20Disk*>(this));
    return CPluginAbstractObject::qt_metacast(_clname);
}

int CPluginDNoteX20Disk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CPluginDNoteX20Disk::signalDisconnect(CPluginAbstract * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPluginDNoteX20Disk::signalUpdateServices()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
