/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[374];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 36), // "on_actionConnect_to_NUCLEO_tr..."
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 29), // "on_actionDisconnect_triggered"
QT_MOC_LITERAL(4, 79, 8), // "readData"
QT_MOC_LITERAL(5, 88, 19), // "on_upButton_clicked"
QT_MOC_LITERAL(6, 108, 22), // "on_rightButton_clicked"
QT_MOC_LITERAL(7, 131, 21), // "on_downButton_clicked"
QT_MOC_LITERAL(8, 153, 21), // "on_leftButton_clicked"
QT_MOC_LITERAL(9, 175, 24), // "on_forwardButton_clicked"
QT_MOC_LITERAL(10, 200, 25), // "on_backwardButton_clicked"
QT_MOC_LITERAL(11, 226, 40), // "on_horizontalSliderSpeed_acti..."
QT_MOC_LITERAL(12, 267, 6), // "action"
QT_MOC_LITERAL(13, 274, 23), // "on_pushButtonGo_clicked"
QT_MOC_LITERAL(14, 298, 25), // "on_pushButtonEcho_clicked"
QT_MOC_LITERAL(15, 324, 27), // "on_pushButtonRecord_clicked"
QT_MOC_LITERAL(16, 352, 21) // "on_testButton_clicked"

    },
    "MainWindow\0on_actionConnect_to_NUCLEO_triggered\0"
    "\0on_actionDisconnect_triggered\0readData\0"
    "on_upButton_clicked\0on_rightButton_clicked\0"
    "on_downButton_clicked\0on_leftButton_clicked\0"
    "on_forwardButton_clicked\0"
    "on_backwardButton_clicked\0"
    "on_horizontalSliderSpeed_actionTriggered\0"
    "action\0on_pushButtonGo_clicked\0"
    "on_pushButtonEcho_clicked\0"
    "on_pushButtonRecord_clicked\0"
    "on_testButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    1,   93,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionConnect_to_NUCLEO_triggered(); break;
        case 1: _t->on_actionDisconnect_triggered(); break;
        case 2: _t->readData(); break;
        case 3: _t->on_upButton_clicked(); break;
        case 4: _t->on_rightButton_clicked(); break;
        case 5: _t->on_downButton_clicked(); break;
        case 6: _t->on_leftButton_clicked(); break;
        case 7: _t->on_forwardButton_clicked(); break;
        case 8: _t->on_backwardButton_clicked(); break;
        case 9: _t->on_horizontalSliderSpeed_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_pushButtonGo_clicked(); break;
        case 11: _t->on_pushButtonEcho_clicked(); break;
        case 12: _t->on_pushButtonRecord_clicked(); break;
        case 13: _t->on_testButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
