#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "dbhandler.h"

class Operations
{
public:
    Operations();
    ~Operations();
    bool get();
    bool save();

    struct Operation
    {
        int idcard;
        int idpos;
        QString fecha;
        float monto;
        int tipo;
        float residuo;
    };

private:
    DBHandler dbhandler;
};

#endif // OPERATIONS_H
