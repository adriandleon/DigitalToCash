#include "cashbox.h"

CashBox::CashBox()
{
    // Constructor de Cash Box

    if (!dbhandler.mydb.isOpen()){
        //No se pudo abrir la Base de Datos
        qDebug() << "No se pudo abrir la Base de Datos";
    }
    else
    {
        //Conexión exitosa a la base de datos
        qDebug() << "Conexión exitosa a la base de datos";
        QString sql = "SELECT * FROM cashbox";
        QSqlQuery qry;
        if (qry.exec(sql))
        {
            int count = 0;
            while(qry.next()){
                this->billetes[count].id = qry.value(0).toInt();
                this->billetes[count].valor = qry.value(1).toFloat();
                this->billetes[count].cantidad = qry.value(2).toInt();
                this->billetes[count].imagen = qry.value(3).toString();
                count++;
            }
        }
        else
        {
            qDebug() << qry.lastError();
        }
    }

    //Cerrar la conexión destruyendo el objeto DBHandler
    dbhandler.~DBHandler();
}

float CashBox::totalEfectivo()
{
    float contador = 0;
    int i = 0;

    while(i < 6){
        contador += this->billetes[i].valor * this->billetes[i].cantidad;
        i++;
    }

    return contador;
}

CashBox::~CashBox()
{
    // Destructor de Cash Box
}
