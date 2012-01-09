/****************************************************************************
** Meta object code from reading C++ file 'cutecom.h'
**
** Created: Thu Jan 5 09:42:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../interface/pluginAbstractSerialPort/cutecom.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cutecom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCuteCom[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x05,
      44,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,    9,    9,    9, 0x0a,
      76,   73,    9,    9, 0x0a,
      90,    9,    9,    9, 0x0a,
     101,    9,    9,    9, 0x0a,
     121,  116,    9,    9, 0x0a,
     153,    9,    9,    9, 0x0a,
     168,    9,    9,    9, 0x0a,
     185,    9,    9,    9, 0x0a,
     202,    9,    9,    9, 0x0a,
     213,    9,    9,    9, 0x0a,
     226,    9,    9,    9, 0x0a,
     242,    9,    9,    9, 0x0a,
     258,  251,    9,    9, 0x0a,
     285,    9,    9,    9, 0x0a,
     296,    9,    9,    9, 0x0a,
     309,  306,    9,    9, 0x0a,
     332,  306,    9,    9, 0x0a,
     352,    9,    9,    9, 0x0a,
     368,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CCuteCom[] = {
    "CCuteCom\0\0_data\0signalReceiveData(QString&)\0"
    "signalDisconnect()\0execCmd()\0fd\0"
    "readData(int)\0sendFile()\0showAboutMsg()\0"
    "item\0oldCmdClicked(QListWidgetItem*)\0"
    "saveSettings()\0readFromStdout()\0"
    "readFromStderr()\0sendDone()\0connectTTY()\0"
    "disconnectTTY()\0killSz()\0enable\0"
    "enableSettingWidgets(bool)\0doOutput()\0"
    "sendKey()\0on\0hexOutputClicked(bool)\0"
    "enableLogging(bool)\0chooseLogFile()\0"
    "clearOutput()\0"
};

const QMetaObject CCuteCom::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CCuteCom,
      qt_meta_data_CCuteCom, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCuteCom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCuteCom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCuteCom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCuteCom))
        return static_cast<void*>(const_cast< CCuteCom*>(this));
    if (!strcmp(_clname, "Ui::CuteCommDlg"))
        return static_cast< Ui::CuteCommDlg*>(const_cast< CCuteCom*>(this));
    return QWidget::qt_metacast(_clname);
}

int CCuteCom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: signalDisconnect(); break;
        case 2: execCmd(); break;
        case 3: readData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: sendFile(); break;
        case 5: showAboutMsg(); break;
        case 6: oldCmdClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: saveSettings(); break;
        case 8: readFromStdout(); break;
        case 9: readFromStderr(); break;
        case 10: sendDone(); break;
        case 11: connectTTY(); break;
        case 12: disconnectTTY(); break;
        case 13: killSz(); break;
        case 14: enableSettingWidgets((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: doOutput(); break;
        case 16: sendKey(); break;
        case 17: hexOutputClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: enableLogging((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: chooseLogFile(); break;
        case 20: clearOutput(); break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void CCuteCom::signalReceiveData(QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CCuteCom::signalDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
