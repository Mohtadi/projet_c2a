/****************************************************************************
** Meta object code from reading C++ file 'central_widget.h'
**
** Created: Fri Jan 6 09:26:38 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/central_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'central_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCentralWidget[] = {

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
      16,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CCentralWidget[] = {
    "CCentralWidget\0\0slotUpdateTabWidget()\0"
};

const QMetaObject CCentralWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CCentralWidget,
      qt_meta_data_CCentralWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCentralWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCentralWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCentralWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCentralWidget))
        return static_cast<void*>(const_cast< CCentralWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CCentralWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotUpdateTabWidget(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
