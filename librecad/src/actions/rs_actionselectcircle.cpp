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


// +++++++++++++++++++++++++++++++++++


#include "rs_actionselectcircle.h"

#include <QAction>
#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_selection.h"
#include "rs_overlaycircle.h"

#include "rs_overlaybox.h"	       /* ?????? */


/**
 * Constructor.
 *
 * @param select true: select window. false: deselect window
 */
RS_ActionSelectCircle::RS_ActionSelectCircle(RS_EntityContainer& container,
        RS_GraphicView& graphicView,
        bool select, bool outside)
        : RS_PreviewActionInterface("Select Circle",
                            container, graphicView) {

	   this->select = select;
	   this->outside = outside;
}


QAction* RS_ActionSelectCircle::createGUIAction(RS2::ActionType type, QObject* /*parent*/) 
{
    QAction* action;

    if (type==RS2::ActionSelectInsideCircle) 
     {
        action = new QAction(tr("Select Inside Circle"),  NULL);
		action->setIcon(QIcon(":/extui/selectinsidecircle.png"));
        //action->zetStatusTip(tr("Selects all Entities in a given Circle"));
    } 
   else if (type==RS2::ActionDeselectInsideCircle)
     {
        action = new QAction(tr("Deselect Inside Circle"), NULL);
		action->setIcon(QIcon(":/extui/deselectinsidecircle.png"));
        //action->zetStatusTip(tr("Deselects all Entities in a given Circle"));		
	}
else if (type==RS2::ActionSelectOutsideCircle)
     {
	action = new QAction(tr("Select Outside Circle"),  NULL);
	action->setIcon(QIcon(":/extui/selectoutsidecircle.png"));
	//action->zetStatusTip(tr("Selects all Entities in a given Circle"));
     }
   else
       {
	  action = new QAction(tr("Deselect Outside Circle"), NULL);
	  action->setIcon(QIcon(":/extui/deselectoutsidecircle.png"));
	  //action->zetStatusTip(tr("Deselects all Entities in a given Circle"));		
	}
 return action;
}


void RS_ActionSelectCircle::init(int status) 
{
    RS_PreviewActionInterface::init(status);
    v1 = RS_Vector(false);
    v2 = RS_Vector(false);
    cc = RS_Vector(false);
   radius = 0;
   
   //snapMode = RS2::SnapFree;
    //snapRes = RS2::RestrictNothing;
}



void RS_ActionSelectCircle::trigger() 
{
        RS_PreviewActionInterface::trigger();

        if (cc.valid && radius > 0) 
     {
	bool cross = (v1.x > v2.x);    /* see RS_Pen in rs_overlaycircle.cpp  green/blue */
	
	RS_Selection s(*container, graphicView);
	
	s.selectCircle(cc, radius, select, cross, outside);
	
	if (RS_DIALOGFACTORY!=NULL)
	  RS_DIALOGFACTORY->updateSelectionWidget(container->countSelected(),container->totalSelectedLength());
	
	//RS_DIALOGFACTORY->updateSelectionWidget(container->countSelected());
//	deleteSnapper();
	
	init();
     }
}



void RS_ActionSelectCircle::mouseMoveEvent(QMouseEvent* e) 
{
   snapFree(e);
   drawSnapper();

   // std::cout << "  v1.x " << v1.x << "     v2.x " << v2.x << "\n";
   
   
   if (getStatus()==SetCorner2 && v1.valid) 
     {
        v2 = snapFree(e);
	
        deletePreview();
	
	RS_Pen pen_f(RS_Color(50,50,255,40), RS2::Width00, RS2::SolidLine);
	
	RS_OverlayCircle* ob = new RS_OverlayCircle(preview, RS_OverlayCircleData(v1, v2)); 
	
	ob->setPen(pen_f);	
	
	preview->addEntity(ob);

        drawPreview();
    }
}



void RS_ActionSelectCircle::mousePressEvent(QMouseEvent* e) {
    if (e->button()==Qt::LeftButton) {
        switch (getStatus()) 
	 {
        case SetCorner1:
            v1 = snapFree(e);
            setStatus(SetCorner2);
            break;

        default:
            break;
        }
    }

    RS_DEBUG->print("RS_ActionSelectCircle::mousePressEvent(): %f %f",
                    v1.x, v1.y);
}



void RS_ActionSelectCircle::mouseReleaseEvent(QMouseEvent* e) {
    RS_DEBUG->print("RS_ActionSelectCircle::mouseReleaseEvent()");

   if (e->button()==Qt::LeftButton) 
     {
        if (getStatus()==SetCorner2) 
	  {
	     v2 = snapFree(e);
	     
	     cc = (v1 + v2) / 2.0;
	     
	     radius = v2.distanceTo(cc);
	     
	     trigger();
	  }
     } 
   else if (e->button()==Qt::RightButton) 
     {
        if (getStatus()==SetCorner2)
	  {
	     deletePreview();
	  }
        init(getStatus()-1);
     }
}



void RS_ActionSelectCircle::updateMouseButtonHints() {
    switch (getStatus()) {
    case SetCorner1:
        RS_DIALOGFACTORY->updateMouseWidget(tr("Choose P1"), tr("Cancel"));
        break;
    case SetCorner2:
        RS_DIALOGFACTORY->updateMouseWidget(tr("Choose P2"), tr("Back"));
        break;
    default:
        RS_DIALOGFACTORY->updateMouseWidget("", "");
        break;
    }
}



void RS_ActionSelectCircle::updateMouseCursor() {
    graphicView->setMouseCursor(RS2::SelectCursor);
}



void RS_ActionSelectCircle::updateToolBar() {
    if (!isFinished()) {
        //RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSnap);
        RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSelect);
    }
    /* else {
        RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSelect);
    }*/
}

// EOF
