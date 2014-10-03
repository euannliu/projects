/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created: Thu May 1 10:10:42 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "game.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Game[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      31,    5,    5,    5, 0x08,
      47,    5,    5,    5, 0x08,
      65,    5,    5,    5, 0x08,
      82,    5,    5,    5, 0x08,
      95,    5,    5,    5, 0x08,
     106,    5,    5,    5, 0x08,
     119,    5,    5,    5, 0x08,
     132,    5,    5,    5, 0x08,
     144,    5,    5,    5, 0x08,
     160,    5,    5,    5, 0x08,
     174,    5,    5,    5, 0x08,
     194,    5,    5,    5, 0x08,
     200,    5,    5,    5, 0x08,
     207,  205,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Game[] = {
    "Game\0\0Display_Number_Players()\0"
    "Set_Names_Two()\0Set_Names_Three()\0"
    "Set_Names_Four()\0Name_Input()\0Set_Name()\0"
    "Pick_Class()\0Begin_Game()\0Dice_Roll()\0"
    "Victory_Check()\0Player_Quit()\0"
    "Check_Player_Turn()\0Yes()\0No()\0i\0"
    "Check_Class_Button(int)\0"
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Game *_t = static_cast<Game *>(_o);
        switch (_id) {
        case 0: _t->Display_Number_Players(); break;
        case 1: _t->Set_Names_Two(); break;
        case 2: _t->Set_Names_Three(); break;
        case 3: _t->Set_Names_Four(); break;
        case 4: _t->Name_Input(); break;
        case 5: _t->Set_Name(); break;
        case 6: _t->Pick_Class(); break;
        case 7: _t->Begin_Game(); break;
        case 8: _t->Dice_Roll(); break;
        case 9: _t->Victory_Check(); break;
        case 10: _t->Player_Quit(); break;
        case 11: _t->Check_Player_Turn(); break;
        case 12: _t->Yes(); break;
        case 13: _t->No(); break;
        case 14: _t->Check_Class_Button((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Game::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Game::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Game,
      qt_meta_data_Game, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Game::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Game))
        return static_cast<void*>(const_cast< Game*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
