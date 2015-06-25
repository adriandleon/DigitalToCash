#include "mainwindow.h"
#include "ui_mainwindow.h"

void createTables(QSqlDatabase mydb);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DBHandler dbhandler;

    if (!dbhandler.mydb.isOpen()){
        //No se pudo abrir la Base de Datos
        qDebug() << "No se pudo abrir la Base de Datos";
    }
    else
    {
        //Conexión exitosa a la base de datos
        qDebug() << "Conexión exitosa a la base de datos";
        dbhandler.createTableCashBox();
        dbhandler.createTableCards();
        dbhandler.createTablePos();
        dbhandler.createTableOperaciones();
    }

    //MOSTRAR CAJA DE EFECTIVO
    CashBox cb;

    QString s0 = QString::number(cb.billetes[0].cantidad);
    QString s1 = QString::number(cb.billetes[0].valor);
    ui->label->setText(s0 + " billetes de " + s1);

    s0 = QString::number(cb.billetes[1].cantidad);
    s1 = QString::number(cb.billetes[1].valor);
    ui->label_2->setText(s0 + " billetes de " + s1);

    s0 = QString::number(cb.billetes[2].cantidad);
    s1 = QString::number(cb.billetes[2].valor);
    ui->label_3->setText(s0 + " billetes de " + s1);

    s0 = QString::number(cb.billetes[3].cantidad);
    s1 = QString::number(cb.billetes[3].valor);
    ui->label_4->setText(s0 + " billetes de " + s1);

    s0 = QString::number(cb.billetes[4].cantidad);
    s1 = QString::number(cb.billetes[4].valor);
    ui->label_5->setText(s0 + " billetes de " + s1);

    s0 = QString::number(cb.billetes[5].cantidad);
    s1 = QString::number(cb.billetes[5].valor);
    ui->label_6->setText(s0 + " billetes de " + s1);

    //Mostrar el Total de efectivo en la caja
    ui->groupCaja->setTitle("Caja de Efectivo: " + QString::number(cb.totalEfectivo()) + "Bs.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Salir_triggered()
{
    close();
}
