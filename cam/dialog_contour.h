#ifndef DIALOG_CONTOUR_H
#define DIALOG_CONTOUR_H

#include <QDialog>

#include <ui_dialog_contour.h>

#include "data_dialog_contour.h"


namespace Ui {
    class Dialog_contour;
}

class Dialog_contour : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_contour(QWidget *parent = 0);
    ~Dialog_contour();

public slots:
    virtual void setData( Data_dialog_contour &d );
    virtual void updateData();

private:
    Ui::Dialog_contour *ui;
    Data_dialog_contour * data;
};

#endif // DIALOG_CONTOUR_H
