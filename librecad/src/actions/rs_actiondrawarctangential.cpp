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

#include "rs_actiondrawarctangential.h"

#include <QAction>
#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_commandevent.h"
#include "ui_qg_arctangentialoptions.h"

/* +++++++++++ here are many changes ++++++++++++++++ */

RS_ActionDrawArcTangential::RS_ActionDrawArcTangential(RS_EntityContainer& container,
                                                       RS_GraphicView& graphicView,
						        bool endpoint)   /* , bool endpoint */
  :RS_PreviewActionInterface("Draw arcs tangential",
                               container, graphicView) 
{
   reset();
   this->endpoint = endpoint;	       /* +++++++++++++ */
}



RS_ActionDrawArcTangential::~RS_ActionDrawArcTangential() {}

				       /* ++++++ type war auskommentiert */
QAction* RS_ActionDrawArcTangential::createGUIAction(RS2::ActionType type, QObject* /*parent*/) {
    /*RVT_PORT    QAction* action = new QAction(tr("Arc: Tangential"),
                                  tr("&Tangential"),
                                  QKeySequence(), NULL); */
      QAction* action;

   // std::cout << "RS_ActionDrawArcTangential::createGUIAction RS2::ActionType = " << type << "\n";
   

   /* not needed in LC2   in LC1 we had an extra button, but here it doesn't work.... */
   if (type==RS2::ActionDrawArcTangentialEndpoint)   /* +++++++++++++++++++++++++++++ */
     {	
	action = new QAction(tr("Arc: Tangential to endpoint"), NULL);
	//action->zetStatusTip(tr("Draw arcs tangential to base entity"));
     }      
   else
     {	
	action = new QAction(tr("Arc: Tangential with radius"), NULL);
	//action->zetStatusTip(tr("Draw arcs tangential to base entity"));
     }
    return action;
}


void RS_ActionDrawArcTangential::reset() {
    baseEntity = NULL;
    isStartPoint = false;
    point = RS_Vector(false);
}

void RS_ActionDrawArcTangential::setArcType(int t)
{
   arcType = t;
}

int RS_ActionDrawArcTangential::getArcType()
{
   return arcType;
}
 

// void RS_ActionDrawArcTangential::setByRadius(bool status) {
//     byRadius=status;
// }

void RS_ActionDrawArcTangential::init(int status) {
    RS_PreviewActionInterface::init(status);

    //reset();
}



void RS_ActionDrawArcTangential::trigger() 
{
   RS_PreviewActionInterface::trigger();
   
   if (point.valid==false || baseEntity==NULL) {
      RS_DEBUG->print("RS_ActionDrawArcTangential::trigger: "
		      "conditions not met");
      return;
   }
   
   preparePreview();
   RS_Arc* arc = new RS_Arc(container, data);
   arc->setLayerToActive();
   arc->setPenToActive();
   container->addEntity(arc);
   
   // upd. undo list:
   if (document!=NULL) {
      document->startUndoCycle();
      document->addUndoable(arc);
      document->endUndoCycle();
   }
   
   graphicView->redraw(RS2::RedrawDrawing);
   
   if(endpoint)
     graphicView->moveRelativeZero(point);
   else
     graphicView->moveRelativeZero(arc->getCenter());
   
   setStatus(SetBaseEntity);
   reset();
}



void RS_ActionDrawArcTangential::preparePreview() 
{
   if (baseEntity!=NULL && point.valid)
     {
	RS_Vector startPoint;
	double direction;
	if (isStartPoint)
	  {
	     startPoint = baseEntity->getStartpoint();
	     direction = RS_Math::correctAngle(baseEntity->getDirection1()+M_PI);
	  }
	else 
	  {
	     startPoint = baseEntity->getEndpoint();
	     direction = RS_Math::correctAngle(baseEntity->getDirection2()+M_PI);
	  }
	
	RS_Arc arc(NULL, RS_ArcData());
	
	/* ++++++++++++++++++++++++++++++++++++ */
	
	bool suc = false;
	double hs, angle, r;
	
	switch (arcType)     // (getArcType()) 
	  {
	   case ArcByEndpoint:
	     
	     hs = startPoint.distanceTo(point)/2.0;
	     angle = startPoint.angleTo(point) - direction;
	     
	     // std::cerr << "   angle = " << angle << "\n";
	     
	     // avoid division by zero:
	     if((fabs(angle) > (M_PI * 2.0 - 0.00001))
		|| (fabs(angle) > (M_PI - 0.00001) && fabs(angle) < (M_PI + 0.00001))
		|| (fabs(angle) < 0.00001))
	       {
		  data.center.valid = false;
		  return;
	       }
	     
	     r = fabs(hs / sin(angle));
	     
	     //               std::cerr << "\n hs " << hs << "  startPoint.angleTo(point)" << startPoint) << "   angle " << angle << "    r " << r << "\n";
	     //               std::cerr << "   startPoint x=" << startPoint.x << "       point x=" <<  "      direction" << direction << "     r=" << r << "\n";
			               
	     // std::cerr << " vor arc.create: r= " << r << "     hs= " << hs
	     //   << "      angle= " << angle << "    sin(angle)= " << sin(angle) << "\n";
	     // 
	     suc = arc.createFrom2PDirectionRadius(startPoint, point, direction, r);
	     
	     break;
	     
	   case ArcByRadius:
	     suc = arc.createFrom2PDirectionRadius(startPoint, point, direction, data.radius);
	     break;
	     
	   case ArcByAngle:
	     suc = arc.createFrom2PDirectionAngle(startPoint, point, direction, angleLength);
	     break;
	   default:
	     break;
	  }			       /* switch */
	     
	if (suc)
	  {
	     data = arc.getData();
	     
	     if(RS_DIALOGFACTORY != NULL) 
	       {
		  if (arcType == ArcByRadius)	  
		    {
		       RS_DIALOGFACTORY->updateArcTangentialOptions(arc.getAngleLength()*180./M_PI,true);
		    }
		  else if(arcType == ArcByAngle)
		    {
		       RS_DIALOGFACTORY->updateArcTangentialOptions(arc.getRadius(),false);
		    }
		 else
		    {
		       RS_DIALOGFACTORY->updateArcTangentialOptions(arc.getAngleLength()*180./M_PI,true);
                       RS_DIALOGFACTORY->updateArcTangentialOptions(arc.getRadius(),false);
		    }		   
	       }
	  }
     }
   

   // std::cerr << " ende von preparePreview  \n";
}

   
void RS_ActionDrawArcTangential::mouseMoveEvent(QMouseEvent* e) {
    if(getStatus() == SetEndAngle) {
        point = snapPoint(e);
        preparePreview();
        if (data.isValid()) {
            RS_Arc* arc = new RS_Arc(preview, data);
            deletePreview();
            preview->addEntity(arc);
            drawPreview();
        }
    }
}



void RS_ActionDrawArcTangential::mouseReleaseEvent(QMouseEvent* e) {
    if (e->button()==Qt::LeftButton) {
        switch (getStatus()) {

        // set base entity:
        case SetBaseEntity: {
            RS_Vector coord = graphicView->toGraph(e->x(), e->y());
            RS_Entity* entity = catchEntity(coord, RS2::ResolveAll);
            if (entity!=NULL) {
                if (entity->isAtomic()) {
                    baseEntity = (RS_AtomicEntity*)entity;
                    if (baseEntity->getStartpoint().distanceTo(coord) <
                            baseEntity->getEndpoint().distanceTo(coord)) {
                        isStartPoint = true;
                    } else {
                        isStartPoint = false;
                    }
                    setStatus(SetEndAngle);
                    updateMouseButtonHints();
                } else {
                    // TODO: warning
                }
            }
            else {
            }
        }
            break;

            // set angle (point that defines the angle)
        case SetEndAngle: {
            RS_CoordinateEvent ce(snapPoint(e));
            coordinateEvent(&ce);
        }
            break;
        }
    } else if (e->button()==Qt::RightButton) {
        deletePreview();
        init(getStatus()-1);
    }
}



void RS_ActionDrawArcTangential::coordinateEvent(RS_CoordinateEvent* e) {
    if (e==NULL) {
        return;
    }
    RS_Vector mouse = e->getCoordinate();

    switch (getStatus()) {
    case SetBaseEntity:
        break;

    case SetEndAngle:
        point = mouse;
        trigger();
        break;

    default:
        break;
    }
}



void RS_ActionDrawArcTangential::commandEvent(RS_CommandEvent* e) {
    QString c = e->getCommand().toLower();

    if (checkCommand("help", c)) {
        RS_DIALOGFACTORY->commandMessage(msgAvailableCommands()
                                         + getAvailableCommands().join(", "));
        return;
    }
}



QStringList RS_ActionDrawArcTangential::getAvailableCommands() {
    QStringList cmd;
    return cmd;
}


void RS_ActionDrawArcTangential::showOptions() {
    RS_ActionInterface::showOptions();

    if (RS_DIALOGFACTORY!=NULL) {
        RS_DIALOGFACTORY->requestOptions(this, true);
    }
    updateMouseButtonHints();
}



void RS_ActionDrawArcTangential::hideOptions() {
    RS_ActionInterface::hideOptions();

    if (RS_DIALOGFACTORY!=NULL) {
        RS_DIALOGFACTORY->requestOptions(this, false);
    }
}



void RS_ActionDrawArcTangential::updateMouseButtonHints() {
   switch (getStatus()) {
    case SetBaseEntity:
      switch (arcType)
	{	    
	 case ArcByEndpoint:
	   RS_DIALOGFACTORY->updateMouseWidget(
					       tr("(ep) Specify base entity"),
					       tr("Cancel"));
	   break;
	   
	 case ArcByRadius:
	   RS_DIALOGFACTORY->updateMouseWidget(
					       tr("(r) Specify base entity"),
					       tr("Cancel"));
	   break;
	   
	 case ArcByAngle:
	   RS_DIALOGFACTORY->updateMouseWidget(
					       tr("(w) Specify base entity"),
					       tr("Cancel"));
	   break;
	 default:
	   break;
	}
      break;
      
    case SetEndAngle:
      switch (arcType)
	{
	 case ArcByEndpoint:   	 
	   RS_DIALOGFACTORY->updateMouseWidget(tr("(ep) Specify end point"), tr("Back"));
	   break;
	   
	 case ArcByRadius:	 
	   RS_DIALOGFACTORY->updateMouseWidget(
					       tr("(r) Specify end angle"), tr("Back"));
	   break;
	 case ArcByAngle:
	   RS_DIALOGFACTORY->updateMouseWidget(
					       tr("(w) Specify end point"), tr("Back"));
	   break;
	 default:
	   break;
	}
      
      break;
    default:
      RS_DIALOGFACTORY->updateMouseWidget("", "");
      break;
   }
}



void RS_ActionDrawArcTangential::updateMouseCursor() {
    graphicView->setMouseCursor(RS2::CadCursor);
}



//void RS_ActionDrawArcTangential::updateToolBar() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        if (isFinished()) {
//            RS_DIALOGFACTORY->resetToolBar();
//        }
//    }
//}


// EOF
