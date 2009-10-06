/****************************************************************************
** Meta object code from reading C++ file 'ShapesDialog.hpp'
**
** Created: Thu Jul 16 10:20:30 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ShapesDialog.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShapesDialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShapesDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      39,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ShapesDialog[] = {
    "ShapesDialog\0\0onPublishButtonClicked()\0"
    "onSubscribeButtonClicked()\0"
};

const QMetaObject ShapesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ShapesDialog,
      qt_meta_data_ShapesDialog, 0 }
};

const QMetaObject *ShapesDialog::metaObject() const
{
    return &staticMetaObject;
}

void *ShapesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShapesDialog))
        return static_cast<void*>(const_cast< ShapesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ShapesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onPublishButtonClicked(); break;
        case 1: onSubscribeButtonClicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
