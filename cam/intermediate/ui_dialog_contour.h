/********************************************************************************
** Form generated from reading UI file 'dialog_contour.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CONTOUR_H
#define UI_DIALOG_CONTOUR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
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

class Ui_Dialog_contour
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QFormLayout *formLayout;
    QLabel *label_1;
    QLineEdit *lineEdit_1;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QSpacerItem *verticalSpacer;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_1;
    QSpacerItem *verticalSpacer_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QWidget *widget_2;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QLineEdit *lineEdit_6;
    QLabel *label_7;
    QLineEdit *lineEdit_7;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_contour)
    {
        if (Dialog_contour->objectName().isEmpty())
            Dialog_contour->setObjectName(QString::fromUtf8("Dialog_contour"));
        Dialog_contour->resize(521, 282);
        verticalLayout_3 = new QVBoxLayout(Dialog_contour);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_6 = new QWidget(Dialog_contour);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        frame = new QFrame(widget_6);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(frame);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        formLayout = new QFormLayout(widget_3);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_1 = new QLabel(widget_3);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_1);

        lineEdit_1 = new QLineEdit(widget_3);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_1);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(widget_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);

        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEdit_3 = new QLineEdit(widget_3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_3);

        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        lineEdit_4 = new QLineEdit(widget_3);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_4);


        verticalLayout->addWidget(widget_3);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget_4 = new QWidget(frame);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(202, 34));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 26));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_5 = new QLineEdit(widget_4);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(0, 26));

        horizontalLayout_4->addWidget(lineEdit_5);


        verticalLayout->addWidget(widget_4);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        widget_5 = new QWidget(frame);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(241, 31));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(84, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        checkBox_1 = new QCheckBox(widget_5);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(checkBox_1);


        verticalLayout->addWidget(widget_5);

        verticalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout_5->addWidget(frame);

        frame_2 = new QFrame(widget_6);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_7 = new QWidget(frame_2);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_3 = new QHBoxLayout(widget_7);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(widget_7);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        widget_2 = new QWidget(widget_7);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(111, 91));
        radioButton_1 = new QRadioButton(widget_2);
        radioButton_1->setObjectName(QString::fromUtf8("radioButton_1"));
        radioButton_1->setGeometry(QRect(0, 0, 105, 21));
        radioButton_2 = new QRadioButton(widget_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(0, 30, 105, 21));
        radioButton_3 = new QRadioButton(widget_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(0, 60, 105, 21));

        horizontalLayout_3->addWidget(widget_2);


        verticalLayout_2->addWidget(widget_7);

        widget_8 = new QWidget(frame_2);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        horizontalLayout_6 = new QHBoxLayout(widget_8);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new QLabel(widget_8);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);

        lineEdit_6 = new QLineEdit(widget_8);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setMinimumSize(QSize(41, 26));
        lineEdit_6->setMaximumSize(QSize(41, 16777215));

        horizontalLayout_6->addWidget(lineEdit_6);

        label_7 = new QLabel(widget_8);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        lineEdit_7 = new QLineEdit(widget_8);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setMinimumSize(QSize(141, 0));

        horizontalLayout_6->addWidget(lineEdit_7);


        verticalLayout_2->addWidget(widget_8);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);


        horizontalLayout_5->addWidget(frame_2);


        verticalLayout_3->addWidget(widget_6);

        verticalSpacer_4 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        widget = new QWidget(Dialog_contour);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(245, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout_3->addWidget(widget);


        retranslateUi(Dialog_contour);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_contour, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_contour, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_contour);
    } // setupUi

    void retranslateUi(QDialog *Dialog_contour)
    {
        Dialog_contour->setWindowTitle(QApplication::translate("Dialog_contour", "Fr\303\244sen Kontur", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("Dialog_contour", "Sichere H\303\266he", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog_contour", "Beginn bei", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog_contour", "Endtiefe", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dialog_contour", "Anzahl Schritte", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog_contour", "Vorschub", 0, QApplication::UnicodeUTF8));
        checkBox_1->setText(QApplication::translate("Dialog_contour", "Startp. <--> Endp.", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog_contour", "Radiuskorrektur", 0, QApplication::UnicodeUTF8));
        radioButton_1->setText(QApplication::translate("Dialog_contour", "R0", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("Dialog_contour", "RL", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("Dialog_contour", "RR", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog_contour", "lbl ", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Dialog_contour", " ; ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog_contour: public Ui_Dialog_contour {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CONTOUR_H
