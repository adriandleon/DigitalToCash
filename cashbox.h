#ifndef CASHBOX_H
#define CASHBOX_H
#include "dbhandler.h"

class CashBox
{
public:
    CashBox();
    ~CashBox();
    float totalEfectivo();
    bool get();
    void set(int cantMod[6]);
    bool update();

    struct Billete
    {
        int id;
        int cantidad;
        float valor;
        QString imagen;
    };

    Billete billetes[6];

private:
    DBHandler dbhandler;
};

#endif // CASHBOX_H
