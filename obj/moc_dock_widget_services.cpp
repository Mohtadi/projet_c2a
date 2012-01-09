/****************************************************************************
** Meta object code from reading C++ file 'dock_widget_services.h'
**
** Created: Fri Jan 6 09:26:45 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/dock_widget_services.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dock_widget_services.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CDockWidgetServices[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      36,   20,   20,   20, 0x05,
      53,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     101,   92,   20,   20, 0x0a,
     166,  160,   20,   20, 0x2a,
     221,   20,   20,   20, 0x2a,
     260,   20,   20,   20, 0x0a,
     289,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CDockWidgetServices[] = {
    "CDockWidgetServices\0\0signalUpdate()\0"
    "signalSendData()\0"
    "signalUpdateStackedWidgetServices(int)\0"
    "_item,_i\0"
    "slotUpdateTreeWidgetDataInformations(QTreeWidgetItem*,int)\0"
    "_item\0slotUpdateTreeWidgetDataInformations(QTreeWidgetItem*)\0"
    "slotUpdateTreeWidgetDataInformations()\0"
    "slotUpdateInformationsData()\0"
    "slotSendData()\0"
};

const QMetaObject CDockWidgetServices::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_CDockWidgetServices,
      qt_meta_data_CDockWidgetServices, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CDockWidgetServices::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CDockWidgetServices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CDockWidgetServices::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDockWidgetServices))
        return static_cast<void*>(const_cast< CDockWidgetServices*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int CDockWidgetServices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalUpdate(); break;
        case 1: signalSendData(); break;
        case 2: signalUpdateStackedWidgetServices((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: slotUpdateTreeWidgetDataInformations((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: slotUpdateTreeWidgetDataInformations((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 5: slotUpdateTreeWidgetDataInformations(); break;
        case 6: slotUpdateInformationsData(); break;
        case 7: slotSendData(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CDockWidgetServices::signalUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CDockWidgetServices::signalSendData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CDockWidgetServices::signalUpdateStackedWidgetServices(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
