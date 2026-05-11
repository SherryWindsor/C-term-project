/****************************************************************************
** Meta object code from reading C++ file 'chessboard.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../chessboard.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chessboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10ChessboardE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10ChessboardE = QtMocHelpers::stringData(
    "Chessboard",
    "regret",
    "",
    "draw",
    "fly_sand_go_stone",
    "strength_uproot_mountain",
    "still_like_stagnant_water",
    "this_is_baseball",
    "i_am_cleaning",
    "seize_hold",
    "find_gold_no_hide",
    "look_at_embarrassing_history"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10ChessboardE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x0a,    1 /* Public */,
       3,    0,   75,    2, 0x0a,    2 /* Public */,
       4,    0,   76,    2, 0x0a,    3 /* Public */,
       5,    0,   77,    2, 0x0a,    4 /* Public */,
       6,    0,   78,    2, 0x0a,    5 /* Public */,
       7,    0,   79,    2, 0x0a,    6 /* Public */,
       8,    0,   80,    2, 0x0a,    7 /* Public */,
       9,    0,   81,    2, 0x0a,    8 /* Public */,
      10,    0,   82,    2, 0x0a,    9 /* Public */,
      11,    0,   83,    2, 0x0a,   10 /* Public */,

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
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Chessboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN10ChessboardE.offsetsAndSizes,
    qt_meta_data_ZN10ChessboardE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10ChessboardE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Chessboard, std::true_type>,
        // method 'regret'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'draw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fly_sand_go_stone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'strength_uproot_mountain'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'still_like_stagnant_water'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'this_is_baseball'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'i_am_cleaning'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'seize_hold'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'find_gold_no_hide'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'look_at_embarrassing_history'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Chessboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Chessboard *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->regret(); break;
        case 1: _t->draw(); break;
        case 2: _t->fly_sand_go_stone(); break;
        case 3: _t->strength_uproot_mountain(); break;
        case 4: _t->still_like_stagnant_water(); break;
        case 5: _t->this_is_baseball(); break;
        case 6: _t->i_am_cleaning(); break;
        case 7: _t->seize_hold(); break;
        case 8: _t->find_gold_no_hide(); break;
        case 9: _t->look_at_embarrassing_history(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Chessboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Chessboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10ChessboardE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Chessboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
