#ifndef DRILL_H
#define DRILL_H

#include <QDialog>

#include <ui_dialog_drill.h>


#include "data_dialog_drill.h"

namespace Ui {
   class dialog_drill;
};


class Dialog_drill : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_drill(QWidget *parent = 0);
    ~Dialog_drill();

public slots:
    virtual void setData( Data_dialog_drill &d );
    virtual void updateData();

private:
   Ui::dialog_drill *ui;
   Data_dialog_drill * data;
};

#endif // DRILL_H
