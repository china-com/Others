#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//显示addStu窗口
void MainWindow::on_actionAddStu_triggered()
{
    //    addStu add;
    //    //add.show();
    //    add.exec();
    this->add.show();
}

//显示queryStu窗口
void MainWindow::on_actionQueryStu_triggered()
{
    this->query.show();
}

void MainWindow::on_actionHelp_triggered()
{

}
