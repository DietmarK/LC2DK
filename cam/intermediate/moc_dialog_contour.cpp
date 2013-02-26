/****************************************************************************
** Meta object code from reading C++ file 'dialog_contour.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog_contour.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_contour.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Dialog_contour[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x0a,
      48,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Dialog_contour[] = {
    "Dialog_contour\0\0d\0setData(Data_dialog_contour&)\0"
    "updateData()\0"
};

void Dialog_contour::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Dialog_contour *_t = static_cast<Dialog_contour *>(_o);
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< Data_dialog_contour(*)>(_a[1]))); break;
        case 1: _t->updateData(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Dialog_contour::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Dialog_contour::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_contour,
      qt_meta_data_Dialog_contour, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Dialog_contour::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Dialog_contour::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Dialog_contour::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_contour))
        return static_cast<void*>(const_cast< Dialog_contour*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog_contour::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
