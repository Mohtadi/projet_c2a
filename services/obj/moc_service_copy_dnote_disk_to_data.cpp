/****************************************************************************
** Meta object code from reading C++ file 'service_copy_dnote_disk_to_data.h'
**
** Created: Thu Jan 5 13:08:48 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serviceCopyDNoteDiskToData/service_copy_dnote_disk_to_data.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service_copy_dnote_disk_to_data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CServiceCopyDNoteDiskToDataThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      41,   35,   34,   34, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CServiceCopyDNoteDiskToDataThread[] = {
    "CServiceCopyDNoteDiskToDataThread\0\0"
    "_file\0slotFileChanged(QString)\0"
};

const QMetaObject CServiceCopyDNoteDiskToDataThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CServiceCopyDNoteDiskToDataThread,
      qt_meta_data_CServiceCopyDNoteDiskToDataThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CServiceCopyDNoteDiskToDataThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CServiceCopyDNoteDiskToDataThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CServiceCopyDNoteDiskToDataThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CServiceCopyDNoteDiskToDataThread))
        return static_cast<void*>(const_cast< CServiceCopyDNoteDiskToDataThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CServiceCopyDNoteDiskToDataThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotFileChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_CServiceCopyDNoteDiskToData[] = {

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
      29,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CServiceCopyDNoteDiskToData[] = {
    "CServiceCopyDNoteDiskToData\0\0"
    "signalSendData()\0slotUpdate()\0"
};

const QMetaObject CServiceCopyDNoteDiskToData::staticMetaObject = {
    { &CServiceAbstractObject::staticMetaObject, qt_meta_stringdata_CServiceCopyDNoteDiskToData,
      qt_meta_data_CServiceCopyDNoteDiskToData, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CServiceCopyDNoteDiskToData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CServiceCopyDNoteDiskToData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CServiceCopyDNoteDiskToData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CServiceCopyDNoteDiskToData))
        return static_cast<void*>(const_cast< CServiceCopyDNoteDiskToData*>(this));
    if (!strcmp(_clname, "CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceCopyDNoteDiskToData*>(this));
    if (!strcmp(_clname, "projet_c2a.CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceCopyDNoteDiskToData*>(this));
    return CServiceAbstractObject::qt_metacast(_clname);
}

int CServiceCopyDNoteDiskToData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CServiceCopyDNoteDiskToData::signalSendData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
