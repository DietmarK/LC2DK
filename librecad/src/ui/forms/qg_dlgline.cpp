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
#include "qg_dlgline.h"

//#include <qvariant.h>
#include "rs_line.h"
#include "rs_graphic.h"

/* +++++++++++++++++++++++++++++ */
#include  <stdio.h>

/* siehe auch qg_dlgarc.cpp qg_dlgcircle.cpp und ..../cam/functions.cpp */
char *my_sprintf (double d, int plus = 0)	       
{
   /* tausender-separator entfernen, Komma als decimal-point character, Nachnullen entfernen */
   /* wenn plus == 1 dann ohne '+'-vorzeichen */
   
   static char num[222];
   int i,k, len;
   
   strcpy (num, "");
   
   if (plus)
     sprintf (num, "%.3f", d);
   else
     sprintf (num, "%+.3f", d);
   
   len = strlen (num);
   
   for (k=0; k<len; k++)
     {
	if (num[k] == ',')
	  { 
	     for (i=k; i<len; i++)
	       {
		  num[i] = num[i+1];
	       }
	     num[len] = '\0';
	  }
	else if (num[k] == '.')
	  num[k] = ',';
     }
   
   if (strchr(num, ','))
     {
	len = strlen (num);
	
	for (k=len-1; k>0; k--)
	  {
	     if ( num[k] == ',')
	       {
		  num[k] = '\0';
		  break;
	       }
	     else if (num[k] == '0')
	       num[k] = '\0';
	     else
	       break;	     
	  }
     }
   
   return num;
}

/* ++++++++++++++++++++++++++++++++++++++++++ */

/*
 *  Constructs a QG_DlgLine as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
QG_DlgLine::QG_DlgLine(QWidget* parent, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setModal(modal);
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_DlgLine::~QG_DlgLine()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_DlgLine::languageChange()
{
    retranslateUi(this);
}

void QG_DlgLine::setLine(RS_Line& l) {
    line = &l;
    //pen = line->getPen();
    wPen->setPen(line->getPen(false), true, false, "Pen");
    RS_Graphic* graphic = line->getGraphic();
    if (graphic!=NULL) {
        cbLayer->init(*(graphic->getLayerList()), false, false);
    }
    RS_Layer* lay = line->getLayer(false);
    if (lay!=NULL) {
        cbLayer->setLayer(*lay);
    }
   

   /* +++++++++++++++++++++++++++++++ */
   /* ausgabezeilen erstellen */
   
   char b1[222];
   char b2[222];
   
   
   
   strcpy (b1, "l  x");         
   strcat (b1, my_sprintf (line->getStartpoint().x) );
   strcat (b1, "   y");
   strcat (b1, my_sprintf (line->getStartpoint().y) );
   
   
   // -------    
      
      
   strcpy (b2, "l  x");         
   strcat (b2, my_sprintf (line->getEndpoint().x) );
   strcat (b2, "   y");
   strcat (b2, my_sprintf (line->getEndpoint().y) );
   
   // std::cout << " winkel " << line->getAngle1() << "   " << RS_Math::rad2deg(line->getAngle1() )   << "\n";
   
   double w = RS_Math::rad2deg(line->getAngle1() );
   
   if( w == 90 || w == 270 )
     {	
	if(line->getStartpoint().y < line->getEndpoint().y)   
	  {
	     punkt1->setText(b1);
	     punkt2->setText(b2);
	  }
	else
	  {
	     punkt1->setText(b2);
	     punkt2->setText(b1);
	  }
     }
   else
     {		   
	if(line->getStartpoint().x < line->getEndpoint().x)
	  {	     
	     punkt1->setText(b1);
	     punkt2->setText(b2);
	  }	
	else
	  {	     
	     punkt1->setText(b2);
	     punkt2->setText(b1);
	  }	
     }   
   
   /* +++++++++++++++++++++++++++++++ */
   
   QString s;
    s.setNum(line->getStartpoint().x);
    leStartX->setText(s);
    s.setNum(line->getStartpoint().y);
    leStartY->setText(s);
    s.setNum(line->getEndpoint().x);
    leEndX->setText(s);
    s.setNum(line->getEndpoint().y);
    leEndY->setText(s);
}

void QG_DlgLine::updateLine() {
    line->setStartpoint(RS_Vector(RS_Math::eval(leStartX->text()),
                                  RS_Math::eval(leStartY->text())));
    line->setEndpoint(RS_Vector(RS_Math::eval(leEndX->text()),
                                RS_Math::eval(leEndY->text())));
    line->setPen(wPen->getPen());
    line->setLayer(cbLayer->currentText());
}

