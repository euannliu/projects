/****************************************************************************
** Meta object code from reading C++ file 'Notflix.h'
**
** Created: Mon Dec 8 22:30:13 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Notflix.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Notflix.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Notflix[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      20,    8,    8,    8, 0x08,
      31,    8,    8,    8, 0x08,
      46,    8,    8,    8, 0x08,
      58,    8,    8,    8, 0x08,
      73,    8,    8,    8, 0x08,
      90,    8,    8,    8, 0x08,
     105,    8,    8,    8, 0x08,
     126,    8,    8,    8, 0x08,
     139,    8,    8,    8, 0x08,
     152,    8,    8,    8, 0x08,
     167,    8,    8,    8, 0x08,
     176,    8,    8,    8, 0x08,
     189,    8,    8,    8, 0x08,
     204,    8,    8,    8, 0x08,
     220,    8,    8,    8, 0x08,
     239,    8,    8,    8, 0x08,
     253,    8,    8,    8, 0x08,
     263,    8,    8,    8, 0x08,
     272,    8,    8,    8, 0x08,
     281,    8,    8,    8, 0x08,
     291,    8,    8,    8, 0x08,
     300,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Notflix[] = {
    "Notflix\0\0Register()\0Reg_Back()\0"
    "Reg_Complete()\0Main_Menu()\0Search_Title()\0"
    "Search_Keyword()\0Return_Movie()\0"
    "Return_Movie_Final()\0Queue_Rent()\0"
    "Queue_Next()\0Queue_Remove()\0Logout()\0"
    "Rate_Movie()\0ReRate_Movie()\0Rating_Update()\0"
    "Rate_Delete_Menu()\0Rate_Delete()\0"
    "M_Queue()\0M_Exit()\0K_Next()\0K_Queue()\0"
    "K_Exit()\0K_Destructor()\0"
};

void Notflix::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Notflix *_t = static_cast<Notflix *>(_o);
        switch (_id) {
        case 0: _t->Register(); break;
        case 1: _t->Reg_Back(); break;
        case 2: _t->Reg_Complete(); break;
        case 3: _t->Main_Menu(); break;
        case 4: _t->Search_Title(); break;
        case 5: _t->Search_Keyword(); break;
        case 6: _t->Return_Movie(); break;
        case 7: _t->Return_Movie_Final(); break;
        case 8: _t->Queue_Rent(); break;
        case 9: _t->Queue_Next(); break;
        case 10: _t->Queue_Remove(); break;
        case 11: _t->Logout(); break;
        case 12: _t->Rate_Movie(); break;
        case 13: _t->ReRate_Movie(); break;
        case 14: _t->Rating_Update(); break;
        case 15: _t->Rate_Delete_Menu(); break;
        case 16: _t->Rate_Delete(); break;
        case 17: _t->M_Queue(); break;
        case 18: _t->M_Exit(); break;
        case 19: _t->K_Next(); break;
        case 20: _t->K_Queue(); break;
        case 21: _t->K_Exit(); break;
        case 22: _t->K_Destructor(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Notflix::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Notflix::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Notflix,
      qt_meta_data_Notflix, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Notflix::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Notflix::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Notflix::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Notflix))
        return static_cast<void*>(const_cast< Notflix*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Notflix::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
