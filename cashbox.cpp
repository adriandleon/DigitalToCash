#include "cashbox.h"

CashBox::CashBox()
{
    // Constructor de Cash Box    
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

void CashBox::set(int cantMod[6])
{
    int i = 0;
    while(i < 6){
        this->billetes[i].cantidad = cantMod[i];
        i++;
    }
}

bool CashBox::get()
{
    if (dbhandler.Open()){
        QString sql = "SELECT * FROM cashbox";
        QSqlQuery qry;
        if (qry.exec(sql))
        {
            qDebug() << "Se leyeron los datos del CashBox";
            int count = 0;
            while(qry.next()){
                this->billetes[count].id = qry.value(0).toInt();
                this->billetes[count].valor = qry.value(1).toFloat();
                this->billetes[count].cantidad = qry.value(2).toInt();
                this->billetes[count].imagen = qry.value(3).toString();
                count++;
            }
            dbhandler.Close();
            return true;
        }
        else
        {
            qDebug() << "No se pudieron leer los datos del chasbox:";
            qDebug() << qry.lastError();
            dbhandler.Close();
            return false;
        }
    }
    else{
        return false;
    }
}

bool CashBox::update()
{
    if (dbhandler.Open()){

        QString sql;
        QSqlQuery qry;
        int i = 0;

        while (i < 6)
        {
            sql = "UPDATE cashbox SET cantidad = " + QString::number(this->billetes[i].cantidad)
                    + " WHERE id = " + QString::number(this->billetes[i].id);
            qry.exec(sql);
            i++;
        }

        dbhandler.Close();
        return true;
    }
    else{
        return false;
    }
}
