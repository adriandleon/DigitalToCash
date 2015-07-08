#ifndef CARDSWINDOW_H
#define CARDSWINDOW_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QKeyEvent>
#include "dbhandler.h"

namespace Ui {
class CardsWindow;
}

class CardsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardsWindow(QWidget *parent = 0);
    ~CardsWindow();

private slots:
    void on_pushButton_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::CardsWindow *ui;
    DBHandler dbhandler;
    QDataWidgetMapper *mapper;
    QSqlQueryModel *modal;
    void loadListView();
    bool guardarNuevaTarjeta();
    void cambiarModo(QString modo);
    void nuevaTarjeta();
    bool eliminarTarjeta();
    bool actualizarTarjeta();
};

#endif // CARDSWINDOW_H
