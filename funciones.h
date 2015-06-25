#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <QtSql>

class Funciones
{
public:
    Funciones();
    ~Funciones();
    void createTables(QSqlDatabase mydb);
};

#endif // FUNCIONES_H
