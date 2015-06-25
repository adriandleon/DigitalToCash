#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <QtSql>
#include <QMessageBox>

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();
    bool createTableCashBox();
    bool createTableCards();
    bool createTablePos();
    bool createTableOperaciones();
    QSqlDatabase mydb;
};

#endif // DBHANDLER_H
