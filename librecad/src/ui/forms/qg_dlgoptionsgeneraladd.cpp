/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/

// +++++++++++++++++++++++

#include "qg_dlgoptionsgeneraladd.h"
#include "rs_settings.h"

#include <qvariant.h>
#include <qmessagebox.h>
// #include "qg_dlgoptionsgeneraladd.ui.h"   moved to here


/*
 *  Constructs a QG_DlgOptionsGeneralAdd as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
QG_DlgOptionsGeneralAdd::QG_DlgOptionsGeneralAdd(QWidget* parent, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_DlgOptionsGeneralAdd::~QG_DlgOptionsGeneralAdd()
{
    destroy();
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_DlgOptionsGeneralAdd::languageChange()
{
    retranslateUi(this);
}

void QG_DlgOptionsGeneralAdd::init() 
{
   RS_SETTINGS->beginGroup("/Privat");
   
   lineEdit_1->setText(RS_SETTINGS->readEntry("/NumberRecentFiles", "9"));
   
   QString OldestOnTop = RS_SETTINGS->readEntry("/OldestOnTop", "0");
   checkBox_15->setChecked(OldestOnTop=="1");
   
   QString NoNativeDialog = RS_SETTINGS->readEntry("/NoNativeDialog", "0");
   checkBox_1->setChecked(NoNativeDialog=="1");
   
   QString Grid_1_2_5 = RS_SETTINGS->readEntry("/Grid-1-2-5", "0");
   if (Grid_1_2_5 == "1")
     radioButton_2->setChecked(true);
   else
     radioButton_1->setChecked(true);
   
   QString SnapOnDimension =  RS_SETTINGS->readEntry("/SnapOnDimension", "0");
   checkBox_2->setChecked(SnapOnDimension=="1");
   
   QString SnapOnSpline =  RS_SETTINGS->readEntry("/SnapOnSpline", "0");
   checkBox_3->setChecked(SnapOnSpline=="1");
   
   QString SnapOnPolyline =  RS_SETTINGS->readEntry("/SnapOnPolyline", "0");
   checkBox_4->setChecked(SnapOnPolyline=="1");
   
   QString SnapOnInsert =  RS_SETTINGS->readEntry("/SnapOnInsert", "0");
   checkBox_5->setChecked(SnapOnInsert=="1");
   
   QString SnapOnText =  RS_SETTINGS->readEntry("/SnapOnText", "0");
   checkBox_6->setChecked(SnapOnText=="1");

   QString SnapOnHatch =  RS_SETTINGS->readEntry("/SnapOnHatch", "0");
   checkBox_7->setChecked(SnapOnHatch=="1");

   lineEdit->setText(RS_SETTINGS->readEntry("/SnapCursorDiameter", "6"));

   lineEdit_2->setText(RS_SETTINGS->readEntry("/SnapCursorColor", "#ffaa00"));

   
   lineEdit_5->setText(RS_SETTINGS->readEntry("/AutoSnapTolerance", "8.88"));

   lineEdit_3->setText(RS_SETTINGS->readEntry("/AutoSnapCursorSize", "6"));

   lineEdit_4->setText(RS_SETTINGS->readEntry("/AutoSnapCursorColor", "#33ff33"));

   QString AutoSnapOnEndpoint =  RS_SETTINGS->readEntry("/AutoSnapOnEndpoint", "1");
      checkBox_8->setChecked(AutoSnapOnEndpoint=="1");
   
   QString AutoSnapOnIntersection =  RS_SETTINGS->readEntry("/AutoSnapOnIntersection", "1");
      checkBox_9->setChecked(AutoSnapOnIntersection=="1");
   
   QString AutoSnapOnGrid =  RS_SETTINGS->readEntry("/AutoSnapOnGrid", "1");
      checkBox_10->setChecked(AutoSnapOnGrid=="1");
   
   QString AutoSnapOnMiddle =  RS_SETTINGS->readEntry("/AutoSnapOnMiddle", "1");
      checkBox_11->setChecked(AutoSnapOnMiddle=="1");
   
   QString AutoSnapOnCenter =  RS_SETTINGS->readEntry("/AutoSnapOnCenter", "1");
      checkBox_12->setChecked(AutoSnapOnCenter=="1");
   
   QString SnapDK =  RS_SETTINGS->readEntry("/SnapDK", "1");
         checkBox_14->setChecked(SnapDK=="1");
   
   QString SnapCenterOnlyContour =  RS_SETTINGS->readEntry("/SnapCenterOnlyContour", "1");
         checkBox_16->setChecked(SnapCenterOnlyContour=="1");
   
   
   // std::cerr << " SnapOnText " << SnapOnText.toStdString() << "\n";
   

   
      QString DraftModePreview =  RS_SETTINGS->readEntry("/DraftModePreview", "1");
      checkBox->setChecked(DraftModePreview=="1");
   

   
      QString PrintPreviewAutoScale =  RS_SETTINGS->readEntry("/PrintPreviewAutoScale", "1");
      checkBox_13->setChecked(PrintPreviewAutoScale=="1");
   

   RS_SETTINGS->endGroup();

   
   RS_SETTINGS->beginGroup("/Snap");
   lineEdit_6->setText(RS_SETTINGS->readEntry("/Range", "20"));
   RS_SETTINGS->endGroup();

    RS_SETTINGS->beginGroup("/DimOrdinate");
    lineEdit_7->setText(RS_SETTINGS->readEntry("/SecondLineLength", "9.0"));
    lineEdit_8->setText(RS_SETTINGS->readEntry("/ConnectingLineLength", "6.0"));
    RS_SETTINGS->endGroup();
  
  
       restartNeeded = false;
}

void QG_DlgOptionsGeneralAdd::destroy() {
}

void QG_DlgOptionsGeneralAdd::setRestartNeeded() {
    restartNeeded = true;
}

void QG_DlgOptionsGeneralAdd::ok() 
{
   RS_SETTINGS->beginGroup("/Privat");
   
   RS_SETTINGS->writeEntry("/NumberRecentFiles", lineEdit_1->text());
   RS_SETTINGS->writeEntry("/OldestOnTop",QString("%1").arg((int)checkBox_15->isChecked()));
   RS_SETTINGS->writeEntry("/NoNativeDialog",QString("%1").arg((int)checkBox_1->isChecked()));
   RS_SETTINGS->writeEntry("/Grid-1-2-5", QString("%1").arg((int)radioButton_2->isChecked()));
   RS_SETTINGS->writeEntry("/SnapOnDimension", QString("%1").arg((int)checkBox_2->isChecked()));
   RS_SETTINGS->writeEntry("/SnapOnSpline", QString("%1").arg((int)checkBox_3->isChecked()));
   RS_SETTINGS->writeEntry("/SnapOnPolyline", QString("%1").arg((int)checkBox_4->isChecked()));
   RS_SETTINGS->writeEntry("/SnapOnInsert", QString("%1").arg((int)checkBox_5->isChecked()));
   RS_SETTINGS->writeEntry("/SnapOnText", QString("%1").arg((int)checkBox_6->isChecked()));
   RS_SETTINGS->writeEntry("/SnapOnHatch", QString("%1").arg((int)checkBox_7->isChecked()));
   RS_SETTINGS->writeEntry("/SnapCursorDiameter", lineEdit->text());
   RS_SETTINGS->writeEntry("/SnapCursorColor", lineEdit_2->text());
   RS_SETTINGS->writeEntry("/AutoSnapTolerance", lineEdit_5->text());
   RS_SETTINGS->writeEntry("/AutoSnapCursorSize", lineEdit_3->text());
   RS_SETTINGS->writeEntry("/AutoSnapCursorColor", lineEdit_4->text());
   RS_SETTINGS->writeEntry("/AutoSnapOnEndpoint", QString("%1").arg((int)checkBox_8->isChecked()));
   RS_SETTINGS->writeEntry("/AutoSnapOnIntersection", QString("%1").arg((int)checkBox_9->isChecked()));
   RS_SETTINGS->writeEntry("/AutoSnapOnGrid", QString("%1").arg((int)checkBox_10->isChecked()));
   RS_SETTINGS->writeEntry("/AutoSnapOnMiddle", QString("%1").arg((int)checkBox_11->isChecked()));
   RS_SETTINGS->writeEntry("/AutoSnapOnCenter", QString("%1").arg((int)checkBox_12->isChecked()));

   RS_SETTINGS->writeEntry("/SnapDK", QString("%1").arg((int)checkBox_14->isChecked()));

   RS_SETTINGS->writeEntry("/SnapCenterOnlyContour", QString("%1").arg((int)checkBox_16->isChecked()));

   RS_SETTINGS->writeEntry("/DraftModePreview", QString("%1").arg((int)checkBox->isChecked()));
   
   RS_SETTINGS->writeEntry("/PrintPreviewAutoScale", QString("%1").arg((int)checkBox_13->isChecked()));
   
   //RS_SETTINGS->writeEntry("/AutoSnapOn...", QString("%1").arg((int)checkBox_99->isChecked()));
   //RS_SETTINGS->writeEntry("/", lineEdit_99->text());
   
   RS_SETTINGS->beginGroup("/Snap");
   RS_SETTINGS->writeEntry("/Range", lineEdit_6->text());
   RS_SETTINGS->endGroup();
      
   
  RS_SETTINGS->beginGroup("/DimOrdinate");
  RS_SETTINGS->writeEntry("/SecondLineLength", lineEdit_7->text());
  RS_SETTINGS->writeEntry("/ConnectingLineLength", lineEdit_8->text());
  RS_SETTINGS->endGroup();

    if (restartNeeded==true) {
        QMessageBox::warning( this, tr("Preferences"),
                        tr("Please restart the application to apply all changes."),
                              QMessageBox::Ok,
                              Qt::NoButton);
    }
    accept();
}

