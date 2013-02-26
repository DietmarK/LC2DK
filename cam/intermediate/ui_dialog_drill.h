/********************************************************************************
** Form generated from reading UI file 'dialog_drill.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DRILL_H
#define UI_DIALOG_DRILL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog_drill
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *label_1;
    QLineEdit *lineEdit_1;
    QLabel *label_2;
    QRadioButton *radioButton;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *dialog_drill)
    {
        if (dialog_drill->objectName().isEmpty())
            dialog_drill->setObjectName(QString::fromUtf8("dialog_drill"));
        dialog_drill->resize(424, 240);
        dialog_drill->setMinimumSize(QSize(424, 240));
        verticalLayout = new QVBoxLayout(dialog_drill);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(dialog_drill);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_1 = new QLabel(frame);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_1);

        lineEdit_1 = new QLineEdit(frame);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        radioButton = new QRadioButton(frame);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        formLayout->setWidget(1, QFormLayout::FieldRole, radioButton);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEdit_2 = new QLineEdit(frame);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_2);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEdit_3 = new QLineEdit(frame);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_3);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        lineEdit_4 = new QLineEdit(frame);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_4);


        verticalLayout->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget = new QWidget(dialog_drill);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(199, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addWidget(widget);


        retranslateUi(dialog_drill);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialog_drill, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialog_drill, SLOT(reject()));

        QMetaObject::connectSlotsByName(dialog_drill);
    } // setupUi

    void retranslateUi(QDialog *dialog_drill)
    {
        dialog_drill->setWindowTitle(QApplication::translate("dialog_drill", "dialog4", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("dialog_drill", "LBL Nr. ; Kommentar", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dialog_drill", "Q216, Q217", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QString());
        label_3->setText(QApplication::translate("dialog_drill", "sichere H\303\266he bei vorpos.", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("dialog_drill", "Freitiefe incremental", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("dialog_drill", "sichere H\303\266he zwischen Bo.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dialog_drill: public Ui_dialog_drill {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DRILL_H
