#include "querystu.h"
#include "ui_querystu.h"
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>

queryStu::queryStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryStu)
{
    ui->setupUi(this);
    //初始化时会试着打开文件，如果不能打开，则报错
    if(readFromFile()== -1){
        QMessageBox::critical(this,"严重错误","文件打开失败，请重试！");
        this->close();
    }

    this->model = new QStandardItemModel;
    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("性别"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("年龄"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("院系"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("兴趣"));
    //使model与tableView建立联系
    this->ui->tableView->setModel(model);

    //设置表格的长度
    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,150);
    this->ui->tableView->setColumnWidth(2,50);
    this->ui->tableView->setColumnWidth(3,50);
    this->ui->tableView->setColumnWidth(4,100);
    this->ui->tableView->setColumnWidth(5,160);
}

queryStu::~queryStu()
{
    delete ui;
}

//读取文件
int queryStu::readFromFile(){

    QFile file("studentInfo.txt");
    //不能读取，则返回-1
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;
    }
    //以流的方式读取进来
    QTextStream in(&file);

    //当文件没有读完时，一次读取以行
    while(!in.atEnd()){
        QString line=in.readLine();
        //追加到容器中
        stu_lines.append(line);
    }
    file.close();
    return 0;
}

void queryStu::on_pushButton_search_clicked()
{
    ////第二次查询之前，需要清除tableView中的内容，所以，也需要重新设置表头和单元格长度
    this->model->clear();
    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("性别"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("年龄"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("院系"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("兴趣"));

    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,150);
    this->ui->tableView->setColumnWidth(2,50);
    this->ui->tableView->setColumnWidth(3,50);
    this->ui->tableView->setColumnWidth(4,100);
    this->ui->tableView->setColumnWidth(5,160);

    //获取该页面中的comboBox中选中的索引，0索引是被提示语句所占用，所以，能用到的索引，从1开始
    int index = this->ui->comboBox_method->currentIndex();
    QString cnt = this->ui->lineEdit_cnt->text();
    //将获取到的数据传入到doQuert方法中去
    doQuert(index,cnt);
}

void queryStu::doQuert(int index,QString cnt){
    int row=0;
    //将stu_lines容器中的数据取出，按照空格进行份分割
    for(int i=0 ; i < stu_lines.length(); i++){
        QString line=stu_lines.at(i);
        line=line.trimmed();
        QStringList subs = line.split(" ");
        switch(index){
            //当case是1时，即选中“按姓名查询”，其他索引类似
            case 1:
                if(cnt == subs.at(0)){
                    disPlay(row++,subs);
                }
                break;
            case 2:
                if(cnt == subs.at(1)){
                    disPlay(row++,subs);
                }
                break;
            case 3:
                if(cnt == subs.at(4)){
                    disPlay(row++,subs);
                }
                break;
            default:
                break;
        }
    }
}

//在tableView中显示内容
void queryStu::disPlay(int row, QStringList subs){
    int i;
    //，单独考虑前五个列，内容的树木固定，最后一列的兴趣每个人的数据不同
    for(i=0 ; i < 5;i++){
        this->model->setItem(row,i,new QStandardItem(subs.at(i)));
    }
    QString ins;
    //每个人的兴趣去之不一样，长度也不一样
    for(i = 5; i < subs.length();i++){
        ins +=subs.at(i)+" ";
    }
    this->model->setItem(row,5,new QStandardItem(ins));
}
