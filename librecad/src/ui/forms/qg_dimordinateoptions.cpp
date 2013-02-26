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
#include "qg_dimordinateoptions.h"

#include "rs_settings.h"

/*
 *  Constructs a QG_DimOrdinateOptions as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
QG_DimOrdinateOptions::QG_DimOrdinateOptions(QWidget* parent, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_DimOrdinateOptions::~QG_DimOrdinateOptions()
{
  writeSettings();
  destroy();
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_DimOrdinateOptions::languageChange()
{
    retranslateUi(this);
}

void QG_DimOrdinateOptions::destroy() {
    RS_SETTINGS->beginGroup("/Dimension");
   // RS_SETTINGS->writeEntry("/Angle", leAngle->text());
    RS_SETTINGS->endGroup();
}

void QG_DimOrdinateOptions::setAction(RS_ActionInterface* a, bool update) 
{
    if (a!=NULL && a->rtti()==RS2::ActionDimOrdinate)
    {
        action = (RS_ActionDimOrdinate*)a;

      double x, y;
      
      if (!update) 
	{
            x = action->getOriginX();
            y = action->getOriginY();
        } else {
            RS_SETTINGS->beginGroup("/DimOrdinate");
            x = RS_SETTINGS->readEntry("/OriginX", "0.0").toDouble();
            y = RS_SETTINGS->readEntry("/OriginY", "0.0").toDouble();
	     QString Xtyp = RS_SETTINGS->readEntry("/Xtype", "0");
	     if (Xtyp == "1")
	    on_rbXtype_clicked();
	    else
	    on_rbYtype_clicked();
	  
	   QString Orig = RS_SETTINGS->readEntry("/SetOrigin", "0");
	     if (Orig == "1")
	    on_rbOrigin_clicked();
	  
            RS_SETTINGS->endGroup();
        }
      
      leOriginX->setText(QString::number(x,'g',6));
      leOriginY->setText(QString::number(y,'g',6));
    }
  else 
    {
        RS_DEBUG->print(RS_Debug::D_ERROR,
                        "QG_DimOrdinateOptions::setAction: wrong action type");
        action = NULL;
    }
}


void QG_DimOrdinateOptions::writeSettings()
{
  RS_SETTINGS->beginGroup("/DimOrdinate");
  RS_SETTINGS->writeEntry("/Xtype", (int)rbXtype->isChecked());
  RS_SETTINGS->writeEntry("/SetOrigin", (int)rbOrigin->isChecked());
  RS_SETTINGS->endGroup();
}


void QG_DimOrdinateOptions::on_rbOrigin_clicked()
{
  rbOrigin->setChecked(true);

  leOriginX->setEnabled(true);
  leOriginY->setEnabled(true);
    
    if (action!=NULL) 
    {
      action->setOrig(true);
    }
  
  writeSettings();
}

void QG_DimOrdinateOptions::on_rbXtype_clicked()
{
  rbXtype->setChecked(true);
  rbYtype->setChecked(false);
  
  leOriginX->setEnabled(false);
  leOriginY->setEnabled(false);
  
  if (action!=NULL) 
    {
      action->setOrig(false);
      action->setXtype(true);
    }
  
  writeSettings();
}

void QG_DimOrdinateOptions::on_rbYtype_clicked()
{
  rbYtype->setChecked(true);
  rbXtype->setChecked(false);
  
  leOriginX->setEnabled(false);
  leOriginY->setEnabled(false);
  
  if (action!=NULL) 
    {
      action->setOrig(false);
      action->setXtype(false);
    }
  
  writeSettings();
}

void QG_DimOrdinateOptions::xy_values_changed()
{
  if (action!=NULL && rbOrigin->isChecked()) 
    {
      action->setOriginXY(leOriginX->text().toDouble(), leOriginY->text().toDouble());
    }
}

void QG_DimOrdinateOptions::set_rbXtype(bool b)
{
  if(b == true)
    on_rbXtype_clicked();
  else
    on_rbYtype_clicked();
  
    writeSettings();
}

void QG_DimOrdinateOptions::set_rbOrigin(bool b)
{  
  if(b == true)
    {
      on_rbOrigin_clicked();
//      rbOrigin->setChecked(true);
    }
  else
    rbOrigin->setChecked(false);
  
    writeSettings();
}  


void QG_DimOrdinateOptions::updateOptions(double x, double y, bool set_Origin, bool X_type)
{
  leOriginX->setText(QString::number(x,'g',6));
  leOriginY->setText(QString::number(y,'g',6));
  set_rbOrigin(set_Origin);
  set_rbXtype(X_type);

  writeSettings();  
}
