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
#include "qg_dlgcircle.h"


#include "rs_circle.h"
#include "rs_graphic.h"

#include  <stdio.h>		       /* ++++++++++++++++++++ */

char *my_sprintf (double, int=0) ;     /* ++++++++++++++++++++++ */


/*
 *  Constructs a QG_DlgCircle as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
QG_DlgCircle::QG_DlgCircle(QWidget* parent, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setModal(modal);
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_DlgCircle::~QG_DlgCircle()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_DlgCircle::languageChange()
{
    retranslateUi(this);
}

void QG_DlgCircle::setCircle(RS_Circle& c) {
    circle = &c;
    //pen = circle->getPen();
    wPen->setPen(circle->getPen(false), true, false, "Pen");
    RS_Graphic* graphic = circle->getGraphic();
    if (graphic!=NULL) {
        cbLayer->init(*(graphic->getLayerList()), false, false);
    }
    RS_Layer* lay = circle->getLayer(false);
    if (lay!=NULL) {
        cbLayer->setLayer(*lay);
    }
   
   /* +++++++++++++++++++++++++ */
   
      char b[222];
   
   strcpy (b, "cc  x");
   strcat (b, my_sprintf (circle->getCenter().x) );
   strcat (b, "   y");
   strcat (b, my_sprintf (circle->getCenter().y) );
   
   strcat (b, " ; R");
   strcat (b, my_sprintf (circle->getRadius() ) );
   
   xy_2->setText(b);
         
   // ---------
      
   strcpy (b, "l  x");
   strcat (b, my_sprintf (circle->getCenter().x) );
   strcat (b, "   y");
   strcat (b, my_sprintf (circle->getCenter().y) );
   
   xy->setText(b);
   
   strcat (b, "  f max m99");
   
   xymax->setText(b);
   
   // ---------
   
   strcpy (b, "q216 = ");
   strcat (b, my_sprintf (circle->getCenter().x, 1) );   /* kein '+' -vorzeichen ! */
   strcat (b, " ; x \nq217 = ");
   strcat (b, my_sprintf (circle->getCenter().y, 1) );
   strcat (b, " ; y ");
   
   strcat (b, "\nl  x+q216  y+q217 ");
   
   tb_circle->setText(b);

   /* +++++++++++++++++++++++++ */
   
    QString s;
    s.setNum(circle->getCenter().x);
    leCenterX->setText(s);
    s.setNum(circle->getCenter().y);
    leCenterY->setText(s);
    s.setNum(circle->getRadius());
    leRadius->setText(s);
}

void QG_DlgCircle::updateCircle() {
    circle->setCenter(RS_Vector(RS_Math::eval(leCenterX->text()),
                                  RS_Math::eval(leCenterY->text())));
    circle->setRadius(RS_Math::eval(leRadius->text()));
    circle->setPen(wPen->getPen());
    circle->setLayer(cbLayer->currentText());
    circle->calculateBorders();
}

