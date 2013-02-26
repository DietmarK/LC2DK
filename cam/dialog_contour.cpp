#include "dialog_contour.h"
#include "ui_dialog_contour.h"

Dialog_contour::Dialog_contour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_contour)
{
    ui->setupUi(this);
}

Dialog_contour::~Dialog_contour()
{
    delete ui;
}

void Dialog_contour::setData(Data_dialog_contour &d)
{
    data = &d;

   ui->lineEdit_1->setText(d.secure1);
   ui->lineEdit_2->setText(d.z_begin);
   ui->lineEdit_3->setText(d.z_end);
   ui->lineEdit_4->setText(d.num_steps);
   ui->lineEdit_5->setText(d.feed);
   ui->lineEdit_6->setText(d.lblnum);
   ui->lineEdit_7->setText(d.lblkom);

   // ui->checkBox_1->setChecked(d.b_e_exch);

   ui->checkBox_1->setChecked(false);       /*   ??   */

   if (d.rl_rr == 0)
     ui->radioButton_1->setChecked(1);
   else if (d.rl_rr == 1)
     ui->radioButton_2->setChecked(1);
   else if (d.rl_rr == 2)
     ui->radioButton_3->setChecked(1);

}

void Dialog_contour::updateData()
{
    data->secure1 = ui->lineEdit_1->text();
    data->z_begin = ui->lineEdit_2->text();
    data->z_end   = ui->lineEdit_3->text();
    data->num_steps = ui->lineEdit_4->text();
    data->feed    =  ui->lineEdit_5->text();
    data->lblnum    =  ui->lineEdit_6->text();
    data->lblkom    =  ui->lineEdit_7->text();

    if(ui->checkBox_1->isChecked())
      data->b_e_exch = 1;
    else
      data->b_e_exch = 0;

    if(ui->radioButton_1->isChecked())
      data->rl_rr = 0;
    else if(ui->radioButton_2->isChecked())
      data->rl_rr = 1;
    else if(ui->radioButton_3->isChecked())
      data->rl_rr = 2;

}
