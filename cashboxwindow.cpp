#include "cashboxwindow.h"
#include "ui_cashboxwindow.h"

CashBoxWindow::CashBoxWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CashBoxWindow)
{
    ui->setupUi(this);

    //Actualizar Caja de Efectivo Actual
    refreshBox();
    desactivarEdicion();
}

CashBoxWindow::~CashBoxWindow()
{
    delete ui;
}

void CashBoxWindow::refreshBox()
{
    //Mostrar Caja de Efectivo Actual
    cb.get();

    QString s0 = QString::number(cb.billetes[0].cantidad);
    ui->billetes_100->setText(s0);
    ui->billetes_100->setAlignment(Qt::AlignHCenter);

    s0 = QString::number(cb.billetes[1].cantidad);
    ui->billetes_50->setText(s0);
    ui->billetes_50->setAlignment(Qt::AlignHCenter);

    s0 = QString::number(cb.billetes[2].cantidad);
    ui->billetes_20->setText(s0);
    ui->billetes_20->setAlignment(Qt::AlignHCenter);

    s0 = QString::number(cb.billetes[3].cantidad);
    ui->billetes_10->setText(s0);
    ui->billetes_10->setAlignment(Qt::AlignHCenter);

    s0 = QString::number(cb.billetes[4].cantidad);
    ui->billetes_5->setText(s0);
    ui->billetes_5->setAlignment(Qt::AlignHCenter);

    s0 = QString::number(cb.billetes[5].cantidad);
    ui->billetes_2->setText(s0);
    ui->billetes_2->setAlignment(Qt::AlignHCenter);

    //Mostrar el Total de efectivo en la caja
    ui->total_efectivo->setText("Total Efectivo: " + QString::number(cb.totalEfectivo()) + "Bs.");
    ui->total_efectivo->setAlignment(Qt::AlignHCenter);
}

void CashBoxWindow::on_boton_agregar_clicked()
{
    //Se presiona 'Agregar Efectivo'
    //Se coloca la variable tipoMod en 1
    if (tipoMod == 1)
    {
        tipoMod = 0;
        desactivarEdicion();
        limpiar();
    }
    else
    {
        tipoMod = 1;
        activarEdicion();
        limpiar();

        ui->mod_billetes_2->setMaximum(99999);
        ui->mod_billetes_5->setMaximum(99999);
        ui->mod_billetes_10->setMaximum(99999);
        ui->mod_billetes_20->setMaximum(99999);
        ui->mod_billetes_50->setMaximum(99999);
        ui->mod_billetes_100->setMaximum(99999);
    }
}

void CashBoxWindow::on_boton_eliminar_clicked()
{
    //Se presiona 'Sacar Efectivo'
    //Se coloca la variable tipoMod en 2
    if (tipoMod == 2)
    {
        tipoMod = 0;
        desactivarEdicion();
        limpiar();
    }
    else
    {
        tipoMod = 2;
        activarEdicion();
        limpiar();

        ui->mod_billetes_2->setMaximum(ui->billetes_2->toPlainText().toInt());
        ui->mod_billetes_5->setMaximum(ui->billetes_5->toPlainText().toInt());
        ui->mod_billetes_10->setMaximum(ui->billetes_10->toPlainText().toInt());
        ui->mod_billetes_20->setMaximum(ui->billetes_20->toPlainText().toInt());
        ui->mod_billetes_50->setMaximum(ui->billetes_50->toPlainText().toInt());
        ui->mod_billetes_100->setMaximum(ui->billetes_100->toPlainText().toInt());
    }
}

void CashBoxWindow::activarEdicion()
{
    ui->mod_billetes_2->setDisabled(false);
    ui->mod_billetes_5->setDisabled(false);
    ui->mod_billetes_10->setDisabled(false);
    ui->mod_billetes_20->setDisabled(false);
    ui->mod_billetes_50->setDisabled(false);
    ui->mod_billetes_100->setDisabled(false);
}

void CashBoxWindow::desactivarEdicion()
{
    ui->mod_billetes_2->setDisabled(true);
    ui->mod_billetes_5->setDisabled(true);
    ui->mod_billetes_10->setDisabled(true);
    ui->mod_billetes_20->setDisabled(true);
    ui->mod_billetes_50->setDisabled(true);
    ui->mod_billetes_100->setDisabled(true);
}

void CashBoxWindow::limpiar()
{
    ui->mod_billetes_2->setValue(0);
    ui->mod_billetes_5->setValue(0);
    ui->mod_billetes_10->setValue(0);
    ui->mod_billetes_20->setValue(0);
    ui->mod_billetes_50->setValue(0);
    ui->mod_billetes_100->setValue(0);
}

void CashBoxWindow::on_mod_billetes_2_valueChanged()
{
    updateInfoMod();
}

void CashBoxWindow::on_mod_billetes_5_valueChanged()
{
    updateInfoMod();
}

void CashBoxWindow::on_mod_billetes_10_valueChanged()
{
    updateInfoMod();
}

void CashBoxWindow::on_mod_billetes_20_valueChanged()
{
    updateInfoMod();
}

void CashBoxWindow::on_mod_billetes_50_valueChanged()
{
    updateInfoMod();
}

void CashBoxWindow::on_mod_billetes_100_valueChanged()
{
    updateInfoMod();
}

double CashBoxWindow::calcularMontoModificado()
{
    double monto = 0;
    monto += ui->mod_billetes_2->value() * cb.billetes[5].valor;
    monto += ui->mod_billetes_5->value() * cb.billetes[4].valor;
    monto += ui->mod_billetes_10->value() * cb.billetes[3].valor;
    monto += ui->mod_billetes_20->value() * cb.billetes[2].valor;
    monto += ui->mod_billetes_50->value() * cb.billetes[1].valor;
    monto += ui->mod_billetes_100->value() * cb.billetes[0].valor;

    return monto;
}

double CashBoxWindow::calcularNuevoTotal(double modificado)
{
    double total = 0;

    switch (tipoMod) {
    case 1:
        total = (cb.totalEfectivo() + modificado);
        break;
    case 2:
        total = (cb.totalEfectivo() - modificado);
        break;
    default:
        total = cb.totalEfectivo();
        break;
    }
    return total;
}

void CashBoxWindow::updateInfoMod()
{
    //Actualizar Información sobre modificacion
    double mod = calcularMontoModificado();

    QString info = "Monto Modificado";
    switch (tipoMod) {
    case 1:
        info = "Monto Agregado: ";
        break;
    case 2:
        info = "Monto Retirado: ";
        break;
    default:
        info = "Monto Modificado: ";
        break;
    }

    ui->label_5->setText(info + QString::number(mod) + " Bs.");
    ui->label_6->setText("Nuevo Total: " + QString::number(calcularNuevoTotal(mod)) + " Bs.");
}

void CashBoxWindow::on_buttonBox_accepted()
{
    int modificado[6];

    switch (tipoMod) {
    case 1:
        //Recogemos los nuevos valores y los almacenamos en un arreglo

        modificado[0] = cb.billetes[0].cantidad + ui->mod_billetes_100->value();
        modificado[1] = cb.billetes[1].cantidad + ui->mod_billetes_50->value();
        modificado[2] = cb.billetes[2].cantidad + ui->mod_billetes_20->value();
        modificado[3] = cb.billetes[3].cantidad + ui->mod_billetes_10->value();
        modificado[4] = cb.billetes[4].cantidad + ui->mod_billetes_5->value();
        modificado[5] = cb.billetes[5].cantidad + ui->mod_billetes_2->value();

        cb.set(modificado);
        cb.update();
        break;
    case 2:
        //Recogemos los nuevos valores y los almacenamos en un arreglo
        modificado[0] = cb.billetes[0].cantidad - ui->mod_billetes_100->value();
        modificado[1] = cb.billetes[1].cantidad - ui->mod_billetes_50->value();
        modificado[2] = cb.billetes[2].cantidad - ui->mod_billetes_20->value();
        modificado[3] = cb.billetes[3].cantidad - ui->mod_billetes_10->value();
        modificado[4] = cb.billetes[4].cantidad - ui->mod_billetes_5->value();
        modificado[5] = cb.billetes[5].cantidad - ui->mod_billetes_2->value();

        cb.set(modificado);
        cb.update();
        break;
    default:
        break;
    }
}
