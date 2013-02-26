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
#include "qg_dlgarc.h"

#include "rs_arc.h"
#include "rs_graphic.h"

#include  <stdio.h>		       /* +++++++++++++++ */
 
char *my_sprintf (double, int=0) ;     /* +++++++++++++++ in qg_dlgline.cpp ++++++++++++ */


/*
 *  Constructs a QG_DlgArc as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
QG_DlgArc::QG_DlgArc(QWidget* parent, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setModal(modal);
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_DlgArc::~QG_DlgArc()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_DlgArc::languageChange()
{
    retranslateUi(this);
}

void QG_DlgArc::setArc(RS_Arc& a) {
   arc = &a;
   //pen = arc->getPen();
   wPen->setPen(arc->getPen(false), true, false, "Pen");
   RS_Graphic* graphic = arc->getGraphic();
   if (graphic!=NULL) {
      cbLayer->init(*(graphic->getLayerList()), false, false);
   }
   RS_Layer* lay = arc->getLayer(false);
   if (lay!=NULL) {
      cbLayer->setLayer(*lay);
   }
   
   /* ++++++++++++++++++++++++++++++++++++++   arc1  bis arc5  versorgen:  */
   
   char b[222];
   
   strcpy (b, "l  x");         
   strcat (b, my_sprintf ( arc->startpoint.x ) );
   strcat (b, "   y");
   strcat (b, my_sprintf (arc->startpoint.y ) );
   
   arc6_2->setText(b);
   
   // -------
    
      
   strcpy (b, "l  x");         
   strcat (b, my_sprintf ( arc->endpoint.x ) );
   strcat (b, "   y");
   strcat (b, my_sprintf (arc->endpoint.y ) );
   
   arc6->setText(b);
   
   // -------

   strcpy (b, "cc  x");         
   strcat (b, my_sprintf ( arc->getCenter().x ) );
   strcat (b, "   y");
   strcat (b, my_sprintf (arc->getCenter().y ) );
   
   arc1_2->setText(b);
   
   // ----------------
    
   if(arc->isReversed())
     {
	
	strcpy (b, "lp  pr");
	strcat (b, my_sprintf ( arc->getRadius() ) );
	strcat (b, "  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle2() ) ) );
	
	arc2_2->setText(b);
	
	// -------
	strcpy (b, "cp  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle1() ) ) );
	strcat (b, "  dr+");
	
	arc3_2->setText(b);
	
	strcpy (b, "lp  pr");
	strcat (b, my_sprintf ( arc->getRadius() ) );
	strcat (b, "  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle1() ) ) );
	
	arc4_2->setText(b);         
	
	// -------   
   
	strcpy (b, "cp  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle2() ) ) );
	strcat (b, "  dr-");
	
	arc5_2->setText(b);
     }
   else
     {
	strcpy (b, "lp  pr");
	strcat (b, my_sprintf ( arc->getRadius() ) );
	strcat (b, "  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle1() ) ) );
	
	arc2_2->setText(b);
	
	// -------
	strcpy (b, "cp  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle2() ) ) );
	strcat (b, "  dr+");
	
	arc3_2->setText(b);
	
	strcpy (b, "lp  pr");
	strcat (b, my_sprintf ( arc->getRadius() ) );
	strcat (b, "  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle2() ) ) );
	
	arc4_2->setText(b);         
	
	// -------   
   
	strcpy (b, "cp  pa");
	strcat (b, my_sprintf ( RS_Math::rad2deg(arc->getAngle1() ) ) );
	strcat (b, "  dr-");
	
	arc5_2->setText(b);
     }
   
   /* ++++++++++++++++++++++++++++ */
   
   QString s;
   s.setNum(arc->getCenter().x);
   leCenterX->setText(s);
   s.setNum(arc->getCenter().y);
   leCenterY->setText(s);
   s.setNum(arc->getRadius());
   leRadius->setText(s);
   s.setNum(RS_Math::rad2deg(arc->getAngle1()));
   leAngle1->setText(s);
   s.setNum(RS_Math::rad2deg(arc->getAngle2()));
   leAngle2->setText(s);
   cbReversed->setChecked(arc->isReversed());
}

void QG_DlgArc::updateArc() {
   arc->setCenter(RS_Vector(RS_Math::eval(leCenterX->text()),
			    RS_Math::eval(leCenterY->text())));
   arc->setRadius(RS_Math::eval(leRadius->text()));
   arc->setAngle1(RS_Math::deg2rad(RS_Math::eval(leAngle1->text())));
   arc->setAngle2(RS_Math::deg2rad(RS_Math::eval(leAngle2->text())));
   arc->setReversed(cbReversed->isChecked());
   arc->setPen(wPen->getPen());
   arc->setLayer(cbLayer->currentText());
   arc->calculateEndpoints();
   arc->calculateBorders();
}
