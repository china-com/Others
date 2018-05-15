#ifndef QUERYSTU_H
#define QUERYSTU_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QString>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class queryStu;
}

class queryStu : public QDialog
{
    Q_OBJECT

public:
    explicit queryStu(QWidget *parent = 0);
    ~queryStu();
    int readFromFile();
    void doQuert(int index , QString cnt);
    void disPlay(int row,QStringList subs);

private slots:
    void on_pushButton_search_clicked();

private:
    Ui::queryStu *ui;
    QList<QString> stu_lines;
    QStandardItemModel * model;
};

#endif // QUERYSTU_H
