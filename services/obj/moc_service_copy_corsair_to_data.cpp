/****************************************************************************
** Meta object code from reading C++ file 'service_copy_corsair_to_data.h'
**
** Created: Thu Jan 5 13:09:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serviceCopyCorsairToData/service_copy_corsair_to_data.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service_copy_corsair_to_data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CServiceCopyCorsairToDataThread[] = {

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
      39,   33,   32,   32, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CServiceCopyCorsairToDataThread[] = {
    "CServiceCopyCorsairToDataThread\0\0_file\0"
    "slotFileChanged(QString)\0"
};

const QMetaObject CServiceCopyCorsairToDataThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CServiceCopyCorsairToDataThread,
      qt_meta_data_CServiceCopyCorsairToDataThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CServiceCopyCorsairToDataThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CServiceCopyCorsairToDataThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CServiceCopyCorsairToDataThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CServiceCopyCorsairToDataThread))
        return static_cast<void*>(const_cast< CServiceCopyCorsairToDataThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CServiceCopyCorsairToDataThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_CServiceCopyCorsairToData[] = {

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
      27,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CServiceCopyCorsairToData[] = {
    "CServiceCopyCorsairToData\0\0signalSendData()\0"
    "slotUpdate()\0"
};

const QMetaObject CServiceCopyCorsairToData::staticMetaObject = {
    { &CServiceAbstractObject::staticMetaObject, qt_meta_stringdata_CServiceCopyCorsairToData,
      qt_meta_data_CServiceCopyCorsairToData, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CServiceCopyCorsairToData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CServiceCopyCorsairToData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CServiceCopyCorsairToData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CServiceCopyCorsairToData))
        return static_cast<void*>(const_cast< CServiceCopyCorsairToData*>(this));
    if (!strcmp(_clname, "CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceCopyCorsairToData*>(this));
    if (!strcmp(_clname, "projet_c2a.CServiceAbstract"))
        return static_cast< CServiceAbstract*>(const_cast< CServiceCopyCorsairToData*>(this));
    return CServiceAbstractObject::qt_metacast(_clname);
}

int CServiceCopyCorsairToData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CServiceCopyCorsairToData::signalSendData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
