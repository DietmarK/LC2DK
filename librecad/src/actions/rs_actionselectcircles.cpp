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


// +++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "rs_actionselectcircles.h"

#include <QAction>
#include "rs_dialogfactory.h"
#include "rs_selection.h"
#include "rs_overlaybox.h"



RS_ActionSelectCircles::RS_ActionSelectCircles(RS_EntityContainer& container,
        RS_GraphicView& graphicView, int select_type)
        :RS_PreviewActionInterface("Select Circles", container, graphicView) 
{
	   circle1 = NULL;
	   circle2 = NULL;
   
	   this->select_type = select_type;
}


QAction* RS_ActionSelectCircles::createGUIAction(RS2::ActionType type, QObject* /*parent*/) 
{
   QAction* action;
   
   if (type==RS2::ActionSelectCircles)       /* 1 */
     {
	action = new QAction(tr("(de-)select circles"), NULL);
	//action->setIcon(QIcon(":/extui/selectlayer.png"));	
     }
   else if (type==RS2::ActionSelectCirclesOnCircle)    /* 2 */
     {
	action = new QAction(tr("(de-)select circles on pitch circle"), NULL);
	//action->setIcon(QIcon(":/extui/selectlayer.png"));	
     }
   else		   /* RS2::ActionSelectCirclesInWindow : 3 */
     {
	action = new QAction(tr("(de-)select circles in window"), NULL);
	//action->setIcon(QIcon(":/extui/selectlayer.png"));
     }
   
   return action;
}


void RS_ActionSelectCircles::init(int status) 
{
    RS_PreviewActionInterface::init(status);
    v1 = v2 = RS_Vector(false);
   //snapMode = RS2::SnapFree;
    //snapRes = RS2::RestrictNothing;
}


void RS_ActionSelectCircles::trigger() 
{
   //std::cerr << "trigger: select_type=" << select_type << "\n";
   
   //std::cerr << " trigger:   status=" << getStatus() << "\n";
   
   if (circle1 != NULL ) 
     {
	RS_Selection s(*container, graphicView);
	
	if(select_type == 1)
	  {
	     s.selectCircles(circle1);             /* all equal circles */
	     init();
	  }
	else if(select_type == 2)
	  {
	     s.selectCircles(circle1, circle2);    /* on pitch circle */
             init();
	  }
	else if(select_type == 3)
	  {	     
	     if (v1.valid && v2.valid && (graphicView->toGuiDX(v1.distanceTo(v2)) > 10))
	       {	       
		  s.selectCircles(circle1, v1, v2);    /* in window */
		  init();
	       }
	  }	
	
	if (RS_DIALOGFACTORY!=NULL) 
	  RS_DIALOGFACTORY->updateSelectionWidget(container->countSelected(),container->totalSelectedLength());
	//RS_DIALOGFACTORY->updateSelectionWidget(container->countSelected());
	
	//std::cerr << " trigger vor init:   status=" << getStatus() << "\n";
	
	//init();
	
	//std::cerr << " trigger nach init:   status=" << getStatus() << "\n";
	
     }
   else
     {
	RS_DEBUG->print("RS_ActionSelectCircles::trigger: Entity is NULL\n");
     }
}

void RS_ActionSelectCircles::mouseMoveEvent(QMouseEvent* e)
{
     //std::cerr << " mouseMoveEvent:   status=" << getStatus() << "\n";
   
   snapFree(e);   
   
   if (getStatus()==SetCorner2 && v1.valid) 
     {
	v2 = snapFree(e);	       /* ++++++ ???????? siehe rs_actionselectwindow.cpp : snapFree(e); */
	deletePreview();
	RS_Pen pen_f(RS_Color(50,50,255,40), RS2::Width00, RS2::SolidLine);
	RS_OverlayBox* ob=new RS_OverlayBox(preview, RS_OverlayBoxData(v1, v2));
	ob->setPen(pen_f);	
	preview->addEntity(ob);
	
	drawPreview();
     }
}


void RS_ActionSelectCircles::mousePressEvent(QMouseEvent* e) 
{
    //std::cerr << " mousePressEvent:  status=" << getStatus() << "\n";

   //std::cout << " mousePressEvent " <<  getStatus() << "\n";
   
   if (e->button()==Qt::LeftButton) 
     {
	switch (getStatus()) 
	  {
	   case SetCorner1:
	     v1 = snapFree(e);	
	     
	     setStatus(SetCorner2);
	     
	     // setStatus(SetCorner2);   /* ---> mouseReleaseEvent */
	     break;
	     
	   default:
	     break;
	  }
     }
}


void RS_ActionSelectCircles::mouseReleaseEvent(QMouseEvent* e)
{
   //std::cerr << " mouseReleaseEvent: type " << select_type << "   status=" << getStatus() << "\n";

   if(select_type == 1)
     {
	if (e->button()==Qt::RightButton) 
	  {
	     init(getStatus()-1);
	  }
	else
	  {
	    // std::cerr << " mouseReleaseEvent: vor catchEntity \n";
			 
	    circle1 = catchEntity(e);
            
	    // std::cerr << " mouseReleaseEvent: nach catchEntity circle R: " << circle1->getRadius() << "\n";
	    
	     if(circle1->rtti() == RS2::EntityCircle  ||  circle1->rtti()==RS2::EntityArc)
	       trigger();
	     else
	       circle1 = NULL;
	  }
     }
   else if(select_type == 2)	       /* on pitch circle */
     {
	if (e->button()==Qt::RightButton) 
	  {
	     init(getStatus()-1);
	  }
	else if (getStatus()==SelectCircle1)
	  {
	     circle1 = catchEntity(e);
	     
	     if(NULL == circle1)
	       init(getStatus()-1);
	     else
	       {
		  if(circle1->rtti() == RS2::EntityCircle  ||  circle1->rtti()==RS2::EntityArc)
		    {
		       circle1->toggleSelected();
		       
		       if (graphicView!=NULL)
			 graphicView->drawEntity(circle1);
		       
		       setStatus(SelectCircle2);
		    }
		  else
		    {
		       //std::cerr << " ..else... circle1->rtti() != RS2::EntityCircle \n";
		       RS_DIALOGFACTORY->commandMessage(tr("selected entity isn't a circle, start from the beginning!"));
		       circle1 = NULL;
		       init(getStatus()-1);
		    }
	       }
	     
	  }
	else	
	  {
	     circle2 = catchEntity(e);
	     
	     if(NULL == circle2)
	       init(getStatus()-1);
	     else
	       {
		  if(circle2->rtti() == RS2::EntityCircle)
		    trigger();
		  else
		    circle2 = NULL;
	       }
	  }
     }
   else if(select_type == 3)	       /* in window */
     {
	// std::cout << " mouseReleaseEvent " <<  getStatus() << "\n";
	
	if (e->button()==Qt::RightButton) 
	  {
	     if (getStatus()==SetCorner2) 
	       deletePreview();
	     
	     init(getStatus()-1);
	  }
	else if (getStatus()==SelectCircle1) 
	  {
	     circle1 = catchEntity(e);
	     
	     if(NULL == circle1)
	       init(getStatus()-1);
	     else
	       {
		  if(circle1->rtti() == RS2::EntityCircle  ||  circle1->rtti()==RS2::EntityArc)
		    {
		       setStatus(SetCorner1);
		       
		       circle1->toggleSelected();
		       
		       if (graphicView!=NULL)
			 graphicView->drawEntity(circle1);
		    }
		  else
		    {
		       //std::cerr << " ..else... circle1->rtti() != RS2::EntityCircle \n";
		       RS_DIALOGFACTORY->commandMessage(tr("selected entity isn't a circle, start from the beginning!"));
		       circle1 = NULL;
		       
		       init(getStatus()-1);
		    }
	       }
	  }
	else if (getStatus()==SetCorner1)
	  {
	     if(v1.valid)
	       setStatus(SetCorner2);
	  }
	else if (getStatus()==SetCorner2)
	  {
   //std::cout << " mouseReleaseEvent vor trigger: " <<  getStatus() << "\n";
	     v2 = snapFree(e);
	     trigger();
	  }
     }				       /* if(select_type == */
   
   //std::cout << " mouseReleaseEvent am ende: " <<  getStatus() << "\n";
   
}



void RS_ActionSelectCircles::updateMouseButtonHints() 
{
    switch (getStatus()) 
     {
      case SelectCircle1:
        RS_DIALOGFACTORY->updateMouseWidget(tr("Choose one circle or arc (min. 3/4 circle)"), tr("Cancel"));
        break;
      case SelectCircle2:
        RS_DIALOGFACTORY->updateMouseWidget(tr("Choose the pitch circle"), tr("Back"));
        break;
      case SetCorner1:
        RS_DIALOGFACTORY->updateMouseWidget(tr("Choose first edge from window"), tr("Back"));
        break;
      case SetCorner2:
        RS_DIALOGFACTORY->updateMouseWidget(tr("Choose second edge from window"), tr("Back"));
        break;
    default:
        RS_DIALOGFACTORY->updateMouseWidget("", "");
        break;
    }
}



void RS_ActionSelectCircles::updateMouseCursor() 
{
    graphicView->setMouseCursor(RS2::SelectCursor);
}

void RS_ActionSelectCircles::updateToolBar()
{
    if (!isFinished()) 
     {   
	//RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSnap);
	RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSelect);
     }
   
   
}


// EOF
