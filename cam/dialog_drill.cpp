#include "dialog_drill.h"
#include "ui_dialog_drill.h"

// #include "includes.h"



Dialog_drill::Dialog_drill(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_drill)
{
    ui->setupUi(this);
}

Dialog_drill::~Dialog_drill()
{
    delete ui;
}

void Dialog_drill::setData(Data_dialog_drill &d)
{
    data = &d;

   ui->lineEdit_1->setText(d.lblnum);
   ui->lineEdit_2->setText(d.secure1);
   ui->lineEdit_3->setText(d.depth1);
   ui->lineEdit_4->setText(d.secure2);

   ui->radioButton->setChecked(d.q216q217);


}

void Dialog_drill::updateData()
{
    data->lblnum = ui->lineEdit_1->text();

   if(ui->radioButton->isChecked())
     data->q216q217 = 1;
   else
     data->q216q217 = 0;

   data->secure1 = ui->lineEdit_2->text();
   data->depth1 = ui->lineEdit_3->text();
   data->secure2 = ui->lineEdit_4->text();

}



