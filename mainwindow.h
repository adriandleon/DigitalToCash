#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QFileInfo>
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
