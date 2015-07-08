#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <QtSql>
#include <QMessageBox>
#include <QDebug>

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();
    bool Open();
    bool Close();
    bool createTableCashBox();
    bool createTableCards();
    bool createTablePos();
    bool createTableOperaciones();
    QSqlDatabase mydb;
};

#endif // DBHANDLER_H
