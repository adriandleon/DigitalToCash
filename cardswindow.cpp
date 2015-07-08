#include "cardswindow.h"
#include "ui_cardswindow.h"

CardsWindow::CardsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardsWindow)
{
    ui->setupUi(this);

    //Constructor de la ventana
    modal = new QSqlQueryModel();

    //Cargar la lista con Todas las tarjetas
    loadListView();

    //Colocar el label del ID oculto
    ui->lineHidden_Id->setHidden(true);
}

CardsWindow::~CardsWindow()
{
    delete ui;
}

void CardsWindow::on_pushButton_clicked()
{
    this->close();
}

void CardsWindow::on_treeView_clicked(const QModelIndex &index)
{
    mapper->setCurrentModelIndex(index);
    //mapper->submit();
}

void CardsWindow::loadListView()
{
    dbhandler.Open();
    QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);
    mapper = new QDataWidgetMapper;

    qry->prepare("SELECT idcard, emisor as Emisor, tipo as Tipo, comBanco, comPropia, imagen FROM cards ORDER BY emisor");

    qry->exec();
    modal->setQuery(*qry);

    ui->treeView->setModel(modal);
    dbhandler.Close();

    //Ocultar Columnas del idcard, comBanco, comPropia, imagen
    ui->treeView->setColumnHidden(0, true);
    ui->treeView->setColumnHidden(3, true);
    ui->treeView->setColumnHidden(4, true);
    ui->treeView->setColumnHidden(5, true);

    mapper->setModel(modal);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->addMapping(ui->lineHidden_Id, 0);
    mapper->addMapping(ui->lineEdit, 1);
    mapper->addMapping(ui->lineEdit_2, 2);
    mapper->addMapping(ui->lineEdit_3, 5);
    mapper->addMapping(ui->doubleSpinBox, 3);
    mapper->addMapping(ui->doubleSpinBox_2, 4);
    mapper->toFirst();
}

void CardsWindow::on_pushButton_2_clicked()
{
    //Boton para agregar una nueva tarjeta
    nuevaTarjeta();
}

void CardsWindow::on_pushButton_3_clicked()
{
    if (ui->pushButton_3->text().toStdString() == "&Editar")
    {
        actualizarTarjeta();
    }
    else if (ui->pushButton_3->text().toStdString() == "&Guardar")
    {
        //Se guarda una tarjeta nueva
        guardarNuevaTarjeta();
        cambiarModo("editar");
    }
}

void CardsWindow::on_pushButton_4_clicked()
{

    if (ui->pushButton_4->text().toStdString() == "El&iminar")
    {
        eliminarTarjeta();
    }
    else if (ui->pushButton_4->text().toStdString() == "&Borrar")
    {
        on_pushButton_2_clicked();
    }
}

bool CardsWindow::guardarNuevaTarjeta()
{
    if(dbhandler.Open())
    {
        QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

        QString vEmisor = ui->lineEdit->text();
        QString vTipo = ui->lineEdit_2->text();
        QString vComBanco = QString::number(ui->doubleSpinBox->value(), 'g', 2);
        QString vComPropia = QString::number(ui->doubleSpinBox_2->value(), 'g', 2);
        QString vImagen = ui->lineEdit_3->text();

        QString sql = "INSERT INTO cards (emisor, tipo, comBanco, comPropia, imagen) VALUES ('"
                + vEmisor + "', '" + vTipo + "', "
                + vComBanco + ", " + vComPropia + ", '"
                + vImagen + "')";

        qry->prepare(sql);

        if(qry->exec())
        {
            qDebug() << "Se agregó una nueva tarjeta";
            dbhandler.Close();
            loadListView();
            return true;
        }
        else
        {
            qDebug() << "Falló la consulta al agregar una nueva tarjeta";
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

void CardsWindow::cambiarModo(QString modo)
{
    if(modo == "nuevo")
    {
        //Configurar los botones de opciones
        ui->pushButton_3->setText("&Guardar");
        ui->pushButton_4->setText("&Borrar");
        ui->pushButton_2->setDisabled(true);
    }
    else if (modo == "editar")
    {
        ui->pushButton_3->setText("&Editar");
        ui->pushButton_4->setText("El&iminar");
        ui->pushButton_2->setDisabled(false);
    }
}

void CardsWindow::nuevaTarjeta()
{
    //Limpiar todos los campos para agregar un nuevo registro
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->doubleSpinBox->setValue(0.0);
    ui->doubleSpinBox_2->setValue(0.0);

    //Cambiar los botones al modo
    cambiarModo("nuevo");
}

bool CardsWindow::eliminarTarjeta()
{
    if(dbhandler.Open())
    {
        QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

        QString vId = ui->lineHidden_Id->text();

        QString sql = "DELETE FROM cards WHERE idcard = " + vId;

        qry->prepare(sql);

        if(qry->exec())
        {
            qDebug() << "Se eliminó la tarjeta con el id: " + vId;
            dbhandler.Close();
            loadListView();
            return true;
        }
        else
        {
            qDebug() << "Falló al eliminar la tarjeta con id: " + vId;
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

bool CardsWindow::actualizarTarjeta()
{
    if(dbhandler.Open())
    {
        QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

        QString vId = ui->lineHidden_Id->text();
        QString vEmisor = ui->lineEdit->text();
        QString vTipo = ui->lineEdit_2->text();
        QString vComBanco = QString::number(ui->doubleSpinBox->value(), 'g', 2);
        QString vComPropia = QString::number(ui->doubleSpinBox_2->value(), 'g', 2);
        QString vImagen = ui->lineEdit_3->text();

        QString sql = "UPDATE cards SET "
                      "emisor = '" + vEmisor + "', "
                      "tipo = '" + vTipo + "', "
                      "comBanco = " + vComBanco + ", "
                      "comPropia = " + vComPropia + ", "
                      "imagen = '" + vImagen + "' WHERE idcard = " + vId;

        qry->prepare(sql);

        if(qry->exec())
        {
            qDebug() << "Se actualizó la tarjeta con el id: " + vId;
            dbhandler.Close();
            loadListView();
            return true;
        }
        else
        {
            qDebug() << "Falló al actualizar la tarjeta con id: " + vId;
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
