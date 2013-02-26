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


// ++++++++++++++++++++++++++++++++++++++ neu


#include "rs_overlaycircle.h"

#include "rs_debug.h"
#include "rs_graphicview.h"
#include "rs_painter.h"
#include "rs_graphic.h"
#include <QBrush>

/**
 * Constructor.
 */
RS_OverlayCircle::RS_OverlayCircle(RS_EntityContainer* parent,
                 const RS_OverlayCircleData& d)
        :RS_AtomicEntity(parent), data(d) {
}



/**
 * Destructor.
 */
RS_OverlayCircle::~RS_OverlayCircle() {}




RS_Entity* RS_OverlayCircle::clone() {

    RS_OverlayCircle* l = new RS_OverlayCircle(*this);
    l->initId();
    return l;
} 

void RS_OverlayCircle::draw(RS_Painter* painter, RS_GraphicView* view, double& /*patternOffset*/) {
    if (painter==NULL || view==NULL) {
        return;
    }
	
	RS_Vector v1=view->toGui(getCorner1());
	RS_Vector v2=view->toGui(getCorner2());
	
   RS_Vector cc = (v1 + v2) / 2.0;
           
   double radius = v2.distanceTo(cc);
   
       if (v1.x > v2.x) 	       /* see "cross" in rs_actionselectcircle.cpp  */
     {
	
	RS_Pen p(RS_Color(50,255,50),RS2::Width00,RS2::DashLine);   /* green */
	        painter->setPen(p);
	//        painter->setPen(QColor(50, 255, 50));
	        painter->fillCircle(cc, radius, RS_Color(9, 255, 9, 90));
	     }
	     else {
	         painter->setPen(QColor(50, 50, 255));
	         painter->fillCircle(cc, radius, RS_Color(9, 9, 255, 90));
	     }
	 
	 
   
// old in LC1:	QBrush brush(QColor(9,9,255,90));
   
	// painter->fillRect(v1.x, v1.y, v2.x-v1.x, v2.y-v1.y, QColor(9,9,255,90) );
	
   // painter->fillCircle(cc, radius, brush );
   
   painter->drawCircle(cc, radius);   
   
}

/**
 * Dumps the point's data to stdout.
 */
std::ostream& operator << (std::ostream& os, const RS_OverlayCircle& l) {
    os << " Line: " << l.getData() << "\n";
    return os;
}


