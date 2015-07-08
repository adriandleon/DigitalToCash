#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cardswindow.h"
#include <math.h>

void createTables(QSqlDatabase mydb);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!dbhandler.Open()){
        //No se pudo abrir la Base de Datos
        QMessageBox mensaje;
        mensaje.setWindowTitle("Advertencia");
        mensaje.setText("Falló la Conexión a la Base de Datos");
        mensaje.setStandardButtons(QMessageBox::Cancel);
        mensaje.setStandardButtons(QMessageBox::Ok);
        mensaje.setDefaultButton(QMessageBox::Cancel);
        mensaje.exec();
    }
    else
    {
        //Conexión exitosa a la base de datos
        dbhandler.createTableCashBox();
        dbhandler.createTableCards();
        dbhandler.createTablePos();
        dbhandler.createTableOperaciones();
    }

    dbhandler.Close();

    //MOSTRAR CAJA DE EFECTIVO
    CashBox cb;
    cb.get();

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

    //Mostrar la Lista de Tarjetas
    modal = new QSqlQueryModel();

    dbhandler.Open();
    QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

    qry->prepare("SELECT (idcard || '-' || emisor || ' ' || tipo) AS Tipo FROM cards ORDER BY emisor");

    qry->exec();
    modal->setQuery(*qry);

    ui->comboBox->setModel(modal);
    ui->comboBox_2->addItem("df", 3);

    dbhandler.Close();
    qDebug() << (modal->rowCount());

    mapper = new QDataWidgetMapper;

    mapper->setModel(modal);
    mapper->toFirst();

    //La hora actual
    QDate fecha = QDate::currentDate();
    ui->label_19->setText(fecha.toString("dd/MM/yyyy"));

    //Mostrar mensaje de terminado
    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Salir_triggered()
{
    //close();
    qApp->exit(0);
}

void MainWindow::on_actionLista_de_Tarjetas_triggered()
{
    CardsWindow cw;
    cw.setModal(true);
    cw.exec();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int n = ui->comboBox->currentText().indexOf('-', 0);
    QString id = ui->comboBox->currentText().left(n);

    leerTarjeta(id);
}

void MainWindow::leerTarjeta(QString id)
{
    qDebug() << id;

    if(dbhandler.Open())
    {
        QSqlQuery* qry = new QSqlQuery(dbhandler.mydb);

        QString sql = "SELECT idcard, comBanco, comPropia, imagen FROM cards WHERE idcard = " + id;

        qry->prepare(sql);

        if(qry->exec())
        {
            while(qry->next())
            {
                //Restar comisiones
                if(ui->radioButton_2->isChecked())
                {
                    double comEmisor = ui->doubleSpinBox->value() * qry->value(1).toDouble();
                    ui->label_11->setText(QString::number(comEmisor, 'g', 8) + " (" + QString::number(qry->value(1).toDouble() * 100) + "%)");

                    double subtotal = ui->doubleSpinBox->value() - comEmisor;
                    ui->label_16->setText(QString::number(subtotal, 'g', 8));

                    double comPropia = subtotal * qry->value(2).toDouble();
                    ui->label_12->setText(QString::number(comPropia, 'g', 8) + " (" + QString::number(qry->value(2).toDouble() * 100) + "%)");

                    double total = subtotal - comPropia;
                    ui->label_18->setText(QString::number(total, 'g', 8));
                }
                //Total para el cliente
                else if(ui->radioButton->isChecked())
                {
                    double comPropia = ui->doubleSpinBox->value() * qry->value(2).toDouble();
                    ui->label_11->setText(QString::number(comPropia, 'g', 8) + " (" + QString::number(qry->value(2).toDouble() * 100) + "%)");

                    double subtotal = ui->doubleSpinBox->value() + comPropia;
                    ui->label_16->setText(QString::number(subtotal, 'g', 8));

                    double comEmisor = ui->doubleSpinBox->value() * qry->value(1).toDouble();
                    ui->label_12->setText(QString::number(comEmisor, 'g', 8) + " (" + QString::number(qry->value(1).toDouble() * 100) + "%)");

                    double total = subtotal + comEmisor;
                    ui->label_18->setText(QString::number(total, 'g', 8));
                }

            }
            dbhandler.Close();
        }
        else
        {
            qDebug() << "Falló al eliminar la tarjeta con id: " + id;
            qDebug() << qry->lastError();
            qDebug() << sql;
            dbhandler.Close();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    //ui->widget->show();
    //ui->widget->hide();

    //Mostrar los tipos de billetes
    sacarEfectivo(ui->label_18->text().toFloat());
}

void MainWindow::on_radioButton_2_clicked()
{
    int n = ui->comboBox->currentText().indexOf('-', 0);
    QString id = ui->comboBox->currentText().left(n);

    leerTarjeta(id);
}

void MainWindow::on_radioButton_clicked()
{
    int n = ui->comboBox->currentText().indexOf('-', 0);
    QString id = ui->comboBox->currentText().left(n);

    leerTarjeta(id);
}

void MainWindow::on_doubleSpinBox_editingFinished()
{
    int n = ui->comboBox->currentText().indexOf('-', 0);
    QString id = ui->comboBox->currentText().left(n);

    leerTarjeta(id);
}

void MainWindow::sacarEfectivo(float cantidad)
{
    CashBox cb;
    cb.get();
    int resultado[6];

    // Pocos Billetes: Le da prioridad a los billetes de alta denominacion
    if(cantidad <= cb.totalEfectivo())
    {

        float temp = 0;
        int billetes = 0;

        //for valor in caja:
        for(uint i = 0; i < 6; i++)
        {
            if (cantidad >= cb.billetes[i].valor)
            {
                temp = fmod(cantidad, cb.billetes[i].valor);
                billetes = int((cantidad - temp) / cb.billetes[i].valor);

                if (billetes <= cb.billetes[i].cantidad)
                {
                    cantidad -= billetes * cb.billetes[i].valor;
                    ui->billetes_100->setText(QString::number(billetes));
                    //resultado.append([valor[0], billetes]);
                    resultado[i] = billetes;
                }
                else
                {
                    cantidad -= cb.billetes[i].cantidad * cb.billetes[i].valor;
                    ui->billetes_100->setText(QString::number(cb.billetes[i].cantidad));
                    //resultado.append([valor[0], valor[1]]);
                    resultado[i] = cb.billetes[i].cantidad;
                }
            }
            else
            {
                ui->billetes_100->setText(QString::number(0));
                //resultado.append([valor[0], 0]);
                resultado[i] = 0;
            }
        }
        if (cantidad > 0)
        {
            ui->billetes_estado->setText("Sobran " + QString::number(cantidad) + "Bs.");
            ui->billetes_estado->setAlignment(Qt::AlignHCenter);
        }
        else
        {
            ui->billetes_estado->setText("Efectivo Completo");
            ui->billetes_estado->setAlignment(Qt::AlignHCenter);
        }

        //Mostrar los resultados
        ui->billetes_100->setText(QString::number(resultado[0]));
        ui->billetes_100->setAlignment(Qt::AlignHCenter);
        ui->billetes_50->setText(QString::number(resultado[1]));
        ui->billetes_50->setAlignment(Qt::AlignHCenter);
        ui->billetes_20->setText(QString::number(resultado[2]));
        ui->billetes_20->setAlignment(Qt::AlignHCenter);
        ui->billetes_10->setText(QString::number(resultado[3]));
        ui->billetes_10->setAlignment(Qt::AlignHCenter);
        ui->billetes_5->setText(QString::number(resultado[4]));
        ui->billetes_5->setAlignment(Qt::AlignHCenter);
        ui->billetes_2->setText(QString::number(resultado[5]));
        ui->billetes_2->setAlignment(Qt::AlignHCenter);

    }
    else
    {
        //return 'No hay suficiente dinero en la caja. ' + str(total) + ' Bs.';
        ui->billetes_estado->setText("No hay suficiente dinero en la caja. ");
        ui->billetes_estado->setAlignment(Qt::AlignHCenter);
    }
}
