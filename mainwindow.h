#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QFileInfo>
#include <QDataWidgetMapper>
#include "cashbox.h"
#include "dbhandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Salir_triggered();

    void on_actionLista_de_Tarjetas_triggered();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_doubleSpinBox_editingFinished();

private:
    Ui::MainWindow *ui;
    QDataWidgetMapper *mapper;
    QSqlQueryModel *modal;
    DBHandler dbhandler;
    void leerTarjeta(QString id);
    void sacarEfectivo(float total);
};

#endif // MAINWINDOW_H
