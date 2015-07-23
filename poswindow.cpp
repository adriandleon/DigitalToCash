#include "poswindow.h"
#include "ui_poswindow.h"

POSWindow::POSWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::POSWindow)
{
    ui->setupUi(this);

    //Constructor de la ventada
    modal = new QSqlQueryModel();

    //Cargar la lista con Todas las tarjetas
    loadListView();

    //Colocar el label del ID oculto
    ui->lineHidden_Id->setHidden(true);
}

POSWindow::~POSWindow()
{
    delete ui;
}

void POSWindow::on_treeView_clicked(const QModelIndex &index)
{
    mapper->setCurrentModelIndex(index);
}

void POSWindow::loadListView()
{
    dbhandler.Open();
    QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);
    mapper = new QDataWidgetMapper;

    qry->prepare("SELECT idpos, nombre as Nombre, codigo as Código FROM pos ORDER BY nombre");

    qry->exec();
    modal->setQuery(*qry);

    ui->treeView->setModel(modal);
    dbhandler.Close();

    //Ocultar Columnas del idpos
    ui->treeView->setColumnHidden(0, true);

    mapper->setModel(modal);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->addMapping(ui->lineHidden_Id, 0);
    mapper->addMapping(ui->lineEdit, 1);
    mapper->addMapping(ui->lineEdit_2, 2);
    mapper->toFirst();
}

void POSWindow::on_pushButton_2_clicked()
{
    this->close();
}

void POSWindow::on_pushButton_clicked()
{
    //Boton para agregar un nuevo P.O.S.
    nuevoPOS();
}

void POSWindow::nuevoPOS()
{
    //Limpiar todos los campos para agregar un nuevo registro
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    //Cambiar los botones al modo
    cambiarModo("nuevo");
}

void POSWindow::cambiarModo(QString modo)
{
    if(modo == "nuevo")
    {
        //Configurar los botones de opciones
        ui->pushButton_3->setText("&Guardar");
        ui->pushButton_4->setText("&Borrar");
        ui->pushButton->setDisabled(true);
    }
    else if (modo == "editar")
    {
        ui->pushButton_3->setText("&Editar");
        ui->pushButton_4->setText("El&iminar");
        ui->pushButton->setDisabled(false);
    }
}

void POSWindow::on_pushButton_3_clicked()
{
    if (ui->pushButton_3->text().toStdString() == "&Editar")
    {
        actualizarPOS();
    }
    else if (ui->pushButton_3->text().toStdString() == "&Guardar")
    {
        //Se guarda una tarjeta nueva
        guardarNuevoPOS();
        cambiarModo("editar");
    }
}

void POSWindow::on_pushButton_4_clicked()
{
    if (ui->pushButton_4->text().toStdString() == "El&iminar")
    {
        eliminarPOS();
    }
    else if (ui->pushButton_4->text().toStdString() == "&Borrar")
    {
        on_pushButton_clicked();
    }
}

bool POSWindow::guardarNuevoPOS()
{
    if(dbhandler.Open())
    {
        QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

        QString vNombre = ui->lineEdit->text();
        QString vCodigo = ui->lineEdit_2->text();

        QString sql = "INSERT INTO pos (nombre, codigo) VALUES ('"
                + vNombre + "', '" + vCodigo + "')";

        qry->prepare(sql);

        if(qry->exec())
        {
            qDebug() << "Se agregó un nuevo Punto de Venta (POS)";
            dbhandler.Close();
            loadListView();
            return true;
        }
        else
        {
            qDebug() << "Falló la consulta al agregar un nuevo Punto de Venta";
            qDebug() << qry->lastError();
            qDebug() << sql;
            dbhandler.Close();
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool POSWindow::eliminarPOS()
{
    if(dbhandler.Open())
    {
        QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

        QString vId = ui->lineHidden_Id->text();

        QString sql = "DELETE FROM pos WHERE idpos = " + vId;

        qry->prepare(sql);

        if(qry->exec())
        {
            qDebug() << "Se eliminó el Punto de Venta con el id: " + vId;
            dbhandler.Close();
            loadListView();
            return true;
        }
        else
        {
            qDebug() << "Falló al eliminar el Punto de Venta con id: " + vId;
            qDebug() << qry->lastError();
            qDebug() << sql;
            dbhandler.Close();
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool POSWindow::actualizarPOS()
{
    if(dbhandler.Open())
    {
        QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

        QString vId = ui->lineHidden_Id->text();
        QString vNombre = ui->lineEdit->text();
        QString vCodigo = ui->lineEdit_2->text();

        QString sql = "UPDATE pos SET "
                      "nombre = '" + vNombre + "', "
                      "codigo = '" + vCodigo + "' WHERE idpos = " + vId;

        qry->prepare(sql);

        if(qry->exec())
        {
            qDebug() << "Se actualizó el Punto de Venta con el id: " + vId;
            dbhandler.Close();
            loadListView();
            return true;
        }
        else
        {
            qDebug() << "Falló al actualizar el Punto de Venta con id: " + vId;
            qDebug() << qry->lastError();
            qDebug() << sql;
            dbhandler.Close();
            return false;
        }
    }
    else
    {
        return false;
    }
}
