#ifndef CASHBOXWINDOW_H
#define CASHBOXWINDOW_H

#include <QDialog>
#include "cashbox.h"

namespace Ui {
class CashBoxWindow;
}

class CashBoxWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CashBoxWindow(QWidget *parent = 0);
    ~CashBoxWindow();

private slots:

    void on_boton_agregar_clicked();

    void on_boton_eliminar_clicked();

    void on_mod_billetes_2_valueChanged();

    void on_mod_billetes_5_valueChanged();

    void on_mod_billetes_10_valueChanged();

    void on_mod_billetes_20_valueChanged();

    void on_mod_billetes_50_valueChanged();

    void on_mod_billetes_100_valueChanged();

    void on_buttonBox_accepted();

private:
    Ui::CashBoxWindow *ui;
    CashBox cb;
    int tipoMod; // 0=Ninguna, 1=Agregar Efectivo, 2=Sacar Efectivo
    void refreshBox();
    void activarEdicion();
    void desactivarEdicion();
    void limpiar();
    double calcularMontoModificado();
    double calcularNuevoTotal(double modificado);
    void updateInfoMod();
};

#endif // CASHBOXWINDOW_H
