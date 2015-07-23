#ifndef POSWINDOW_H
#define POSWINDOW_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "dbhandler.h"

namespace Ui {
class POSWindow;
}

class POSWindow : public QDialog
{
    Q_OBJECT

public:
    explicit POSWindow(QWidget *parent = 0);
    ~POSWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::POSWindow *ui;
    DBHandler dbhandler;
    QDataWidgetMapper *mapper;
    QSqlQueryModel *modal;
    void loadListView();
    bool guardarNuevoPOS();
    void cambiarModo(QString modo);
    void nuevoPOS();
    bool eliminarPOS();
    bool actualizarPOS();
};

#endif // POSWINDOW_H
