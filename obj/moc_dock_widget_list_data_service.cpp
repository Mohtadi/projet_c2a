/****************************************************************************
** Meta object code from reading C++ file 'dock_widget_list_data_service.h'
**
** Created: Fri Jan 6 09:26:43 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/dock_widget_list_data_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dock_widget_list_data_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CDockWidgetListDataService[] = {

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
      28,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CDockWidgetListDataService[] = {
    "CDockWidgetListDataService\0\0"
    "slotUpdateTreeWidgetListDataService()\0"
};

const QMetaObject CDockWidgetListDataService::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_CDockWidgetListDataService,
      qt_meta_data_CDockWidgetListDataService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CDockWidgetListDataService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CDockWidgetListDataService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CDockWidgetListDataService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDockWidgetListDataService))
        return static_cast<void*>(const_cast< CDockWidgetListDataService*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int CDockWidgetListDataService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotUpdateTreeWidgetListDataService(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
