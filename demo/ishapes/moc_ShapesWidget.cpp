/****************************************************************************
** Meta object code from reading C++ file 'ShapesWidget.hpp'
**
** Created: Fri Feb 12 01:34:23 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ShapesWidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShapesWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShapesWidget[] = {

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
      41,   35,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ShapesWidget[] = {
    "ShapesWidget\0\0nextAnimationFrame()\0"
    "shape\0addShape(boost::shared_ptr<Shape>)\0"
};

const QMetaObject ShapesWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ShapesWidget,
      qt_meta_data_ShapesWidget, 0 }
};

const QMetaObject *ShapesWidget::metaObject() const
{
    return &staticMetaObject;
}

void *ShapesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShapesWidget))
        return static_cast<void*>(const_cast< ShapesWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ShapesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: nextAnimationFrame(); break;
        case 1: addShape((*reinterpret_cast< boost::shared_ptr<Shape>(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
