#include "addstu.h"
#include "ui_addstu.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

addStu::addStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStu)
{
    ui->setupUi(this);
}

addStu::~addStu()
{
    delete ui;
}

void addStu::on_pushButton_ok_clicked()
{
    //获取控件的内容
    QString name = this->ui->lineEdit_name->text();
    QString id = this->ui->lineEdit_ID->text();
    QString sex = this->ui->buttonGroup_sex->checkedButton()->text();
    QList<QAbstractButton *> ins_list = this->ui->buttonGroup_ins->buttons();
    QString ins;

    for(int i=0;i<ins_list.length();i++){
        QAbstractButton * che=ins_list.at(i);
        if(che->isChecked()){
            ins+=che->text()+" ";
        }
    }

    //获取控件的内容
    QString age=this->ui->comboBox_age->currentText();
    QString yx=this->ui->comboBox_yx->currentText();
    //显示在消息框中的内容
    QString content=name+'\n'+id+'\n'+sex+'\n'+age+'\n'+yx+'\n'+ins;
    //写到文件中时的内容，与上面的就只有格式不一样
    QString cnt=name+" "+id+" "+sex+" "+age+" "+yx+" "+ins+'\n';

    //判断姓名长度和学号长度是否符合符合要求，兴趣是否有勾选
    if(name.length()<1 || id.length()!=6 || ins.length()<1){
        QMessageBox::critical(this,"错误","你填写的信息不完整，请重新填写！","确定");
    }else{
        int ret=QMessageBox::information(this,"请确认信息！",content,"确认","取消");
        //ret=0时，即用户点击的是“确认”按钮
        if(ret==0){
            //点击“确认”按钮后，会调用clearUserInterface方法,将界面恢复到最原始的时候
            clearUserInterface();
            //调用writeToFile方法，将数据写入到文件中
            writeToFile(cnt);
        }
    }
}

//将界面选项恢复到初始值
void addStu::clearUserInterface(){
    this->ui->lineEdit_name->clear();
    this->ui->lineEdit_ID->clear();
    this->ui->radioButton_male->setChecked(true);
    this->ui->comboBox_age->setCurrentIndex(6);
    this->ui->comboBox_yx->setCurrentIndex(0);
    QList<QAbstractButton *>ins_list=this->ui->buttonGroup_ins->buttons();
    for(int i=0;i<ins_list.length();i++){
        QAbstractButton * box=ins_list.at(i);
        box->setChecked(false);
    }
    //光标恢复到name上
    this->ui->lineEdit_name->setFocus();
}

//将数据写入到文件中
void addStu::writeToFile(QString cnt){
    QFile file("studentInfo.txt");
    //以追加和text方式打开文件
    if(! file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
        return;
    }
    QTextStream out(&file);
    out << cnt;
    file.close();
}

//关闭窗口
void addStu::on_pushButton_cancel_clicked()
{
    this->close();
}
