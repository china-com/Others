#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addstu.h"
#include "querystu.h"

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
    void on_actionAddStu_triggered();

    void on_actionQueryStu_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;

    //创建私有成员
    addStu add;
    queryStu query;
};

#endif // MAINWINDOW_H
