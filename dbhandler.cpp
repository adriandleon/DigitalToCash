#include "dbhandler.h"

DBHandler::DBHandler()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("db.sqlite3");

    //Abrir o Crear la Base de Datos
    if (!mydb.open()){
        //No se pudo abrir la Base de Datos
        qDebug() << "No se pudo abrir la Base de Datos";

        QMessageBox mensaje;
        mensaje.setWindowTitle("Advertencia");
        mensaje.setText("Falló la Conexión a la Base de Datos");
        mensaje.setStandardButtons(QMessageBox::Cancel);
        mensaje.setStandardButtons(QMessageBox::Ok);
        mensaje.setDefaultButton(QMessageBox::Cancel);
        mensaje.exec();
    }
}

DBHandler::~DBHandler()
{
    //Cerrar la conexion a la BD
    mydb.close();
}

bool DBHandler::createTableCashBox()
{
    QString tableName = "cashbox";

    QString sql = "CREATE TABLE IF NOT EXISTS " + tableName + " ("
                  "id INTEGER PRIMARY KEY, "
                  "valor REAL NOT NULL DEFAULT (0), "
                  "cantidad INTEGER NOT NULL DEFAULT (0), "
                  "imagen VARCHAR(80))";

    if (!mydb.isOpen())
    {
        qDebug() << "Falló la conexión a la base de datos. Creando la tabla " + tableName;
        return false;
    }
    else
    {
        QSqlQuery qry;
        if (qry.exec(sql))
        {
            qDebug() << "Se creó la tabla " + tableName + " exitosamente.";

            sql = "INSERT INTO cashbox VALUES "
                  "(0, 100, 0, '100bolivares.png'),"
                  "(1, 50, 0, '50bolivares.png'),"
                  "(2, 20, 0, '20bolivares.png'),"
                  "(3, 10, 0, '10bolivares.png'),"
                  "(4, 5, 0, '5bolivares.png'),"
                  "(5, 2, 0, '2bolivares.png')";
            if (qry.exec(sql))
            {
                qDebug() << "Se insertaron los registros iniciales en la tabla " + tableName;
            }
            else
            {
                qDebug() << "Ocurrió un error al insertar los registros iniciales en la tabla " + tableName;

            }

            return true;
        }
        else
        {
            qDebug() << "Ocurrió un error al crear la Tabla " + tableName;
            return false;
        }
    }
}

bool DBHandler::createTableCards()
{
    QString tableName = "cards";

    QString sql = "CREATE TABLE IF NOT EXISTS " + tableName + " ("
                  "idcard INTEGER PRIMARY KEY, "
                  "emisor VARCHAR(100) NOT NULL, "
                  "tipo VARCHAR(100) NOT NULL, "
                  "comBanco REAL DEFAULT (0), "
                  "comPropia REAL DEFAULT (0) )";

    if (!this->mydb.isOpen())
    {
        qDebug() << "Falló la conexión a la base de datos. Creando la tabla " + tableName;
        return false;
    }
    else
    {
        QSqlQuery qry;
        if (qry.exec(sql))
        {
            qDebug() << "Se creó la tabla " + tableName + " exitosamente.";
            return true;
        }
        else
        {
            qDebug() << "Ocurrió un error al crear la Tabla " + tableName;
            return false;
        }
    }
}

bool DBHandler::createTablePos()
{
    QString tableName = "pos";

    QString sql = "CREATE TABLE IF NOT EXISTS " + tableName + " ("
                  "idpos INTEGER PRIMARY KEY NOT NULL, "
                  "codigo VARCHAR UNIQUE, "
                  "nombre VARCHAR)";

    if (!this->mydb.isOpen())
    {
        qDebug() << "Falló la conexión a la base de datos. Creando la tabla " + tableName;
        return false;
    }
    else
    {
        QSqlQuery qry;
        if (qry.exec(sql))
        {
            qDebug() << "Se creó la tabla " + tableName + " exitosamente.";
            return true;
        }
        else
        {
            qDebug() << "Ocurrió un error al crear la Tabla " + tableName;
            return false;
        }
    }
}

bool DBHandler::createTableOperaciones()
{
    QString tableName = "operaciones";

    QString sql = "CREATE TABLE IF NOT EXISTS " + tableName + " ("
                  "idop INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                  "idcard INTEGER, "
                  "idpos INTEGER, "
                  "fecha DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP, "
                  "monto REAL NOT NULL DEFAULT 0, "
                  "totalcliente BOOL DEFAULT 1,"
                  "FOREIGN KEY(idcard) REFERENCES cards(idcard) ON UPDATE CASCADE ON DELETE CASCADE,"
                  "FOREIGN KEY(idpos) REFERENCES pos(idpos) ON UPDATE CASCADE ON DELETE CASCADE)";

    if (!this->mydb.isOpen())
    {
        qDebug() << "Falló la conexión a la base de datos. Creando la tabla " + tableName;
        return false;
    }
    else
    {
        QSqlQuery qry;
        if (qry.exec(sql))
        {
            qDebug() << "Se creó la tabla " + tableName + " exitosamente.";
            return true;
        }
        else
        {
            qDebug() << "Ocurrió un error al crear la Tabla " + tableName;
            return false;
        }
    }
}
