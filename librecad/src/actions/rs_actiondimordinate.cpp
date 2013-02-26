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

#include "rs_settings.h"
#include "rs_actiondimordinate.h"
#include "rs_overlayline.h"
		  
#include <QAction>
#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_commandevent.h"
#include "rs_constructionline.h"

/**
 * Constructor.
 *
 * @param angle Initial angle in rad.
 * @param fixedAngle true: The user can't change the angle.
 *                   false: The user can change the angle in a option widget.
 */
RS_ActionDimOrdinate::RS_ActionDimOrdinate(RS_EntityContainer& container,
					   RS_GraphicView& graphicView,
					   RS2::ActionType type)
  :RS_ActionDimension("Draw ordinate dimensions",
		      container, graphicView)
    ,actionType(type)
{
   reset();      
}



RS_ActionDimOrdinate::~RS_ActionDimOrdinate() {}


QAction* RS_ActionDimOrdinate::createGUIAction(RS2::ActionType type, QObject* /*parent*/) 
{
   QAction* action;
   
   action = new QAction(tr("&Ordinate"),  NULL);
   action->setIcon(QIcon(":/extui/dimlinear.png"));
   //action->zetStatusTip(tr("Ordinate Dimension"));
   
   return action;
}

RS2::ActionType RS_ActionDimOrdinate::rtti() 
{
   return actionType;
}


void RS_ActionDimOrdinate::reset() 
{
   RS_ActionDimension::reset();
   
   RS_Vector op;
   
   
   RS_SETTINGS->beginGroup("/DimOrdinate");
   op.x = RS_SETTINGS->readEntry("/OriginX", "0.0").toDouble();
   op.y = RS_SETTINGS->readEntry("/OriginY", "0.0").toDouble();
   QString Xtyp = RS_SETTINGS->readEntry("/Xtype", "0");  
   
   				       /* auskommentieren ?? */
   X_type = (Xtyp == "1");
   
  RS_SETTINGS->endGroup();
  
   edata = RS_DimOrdinateData(op, RS_Vector(false), RS_Vector(false), bool(false));   
   
   setStatus(SetFirstLine);
   
   if (RS_DIALOGFACTORY!=NULL) 
    {
      RS_DIALOGFACTORY->requestOptions(this, true, true);
   }
}


void RS_ActionDimOrdinate::showOrigin()
{
  double ox = 15; 
  
  RS_LineData ld1, ld2;

  RS_CircleData cdo;

  RS_OverlayLine* lo;

  RS_Circle* co;
  
  RS_Pen p(RS_Color(255,88,0), RS2::Width00, RS2::SolidLine);
  
  ld1 = RS_LineData(graphicView->toGui(edata.OriginPoint) + RS_Vector( ox, ox),  graphicView->toGui(edata.OriginPoint) + RS_Vector( -ox, -ox));
  ld2 = RS_LineData(graphicView->toGui(edata.OriginPoint) + RS_Vector( ox, -ox),  graphicView->toGui(edata.OriginPoint) + RS_Vector( -ox, ox));
  
  lo = new RS_OverlayLine(NULL, ld1);
  
  lo->setPen(p);
  
  preview->addEntity(lo);
  
  lo = new RS_OverlayLine(NULL, ld2);
  
  lo->setPen(p);
  
  preview->addEntity(lo);
    
  cdo = RS_CircleData(edata.OriginPoint, 11 / graphicView->getFactor().x);
  
  co = new RS_Circle(NULL, cdo);
  
  co->setPen(p);
  
  preview->addEntity(co);
}



void RS_ActionDimOrdinate::trigger() 
{
   RS_ActionDimension::trigger();
   
  // preparePreview();
   
   data.definitionPoint = edata.OriginPoint;   
   
   RS_DimOrdinate* dim = new RS_DimOrdinate(container, data, edata);
   
   //dim->setXType(X_type);
   
   dim->setLayerToActive();

  dim->setPenToActive();
  
  dim->update();
  
  container->addEntity(dim);
   
   deletePreview();
   
   // upd. undo list:
   if (document!=NULL) 
     {
        document->startUndoCycle();
        document->addUndoable(dim);
        document->endUndoCycle();
     }
   
   RS_Vector rz = graphicView->getRelativeZero();
   
   graphicView->redraw(RS2::RedrawDrawing);
   
   graphicView->moveRelativeZero(rz);
   
   RS_DEBUG->print("RS_ActionDimOrdinate::trigger():"
		   " dim added: %d", dim->getId());
}


void RS_ActionDimOrdinate::preparePreview() 
{
   /* compute data.middleOfText : */
   
   double angle;
   
   /* dummy object, only for reading variables */
   RS_DimOrdinate* dimo = new RS_DimOrdinate(preview, data, edata);   
   
   // double as = dimo->getArrowSize();
   
   // double lo = dimo->getExtensionLineOffset();
   
   // double lg = dimo->getDimensionLineGap();
   
   double w = dimo->getTextWidth();    /* added in rs_actiondimension  */
   
   RS_Vector mot;
   
   /* distance from SecondLine to middleOfText */
   /*   = w/2 + ?????? : lg, 2*lg, as/2 or a fix number ???  */
   textDist = w / 2 + 3; 	 
   
   if(edata.is_x_type)                  /* direction X */
     {
	angle = M_PI / 2;
	
	if(edata.FirstLine.y > edata.SecondLine.y)
	  angle += M_PI;
     }
   else
     {
	angle = 0.0;
	
	if(edata.FirstLine.x > edata.SecondLine.x)
	  angle += M_PI;
     }
   
   mot.setPolar(textDist, angle);
   
   data.middleOfText = edata.SecondLine + mot; 
}



void RS_ActionDimOrdinate::mouseMoveEvent(QMouseEvent* e)
{
   RS_DEBUG->print("RS_ActionDimOrdinate::mouseMoveEvent begin");
   
   deletePreview();
   
   preparePreview();
   
   showOrigin();
   
   RS_Vector mouse = snapPoint(e);
   
   if (SetSecondLine == getStatus() &&  edata.FirstLine.valid) 
     {
	edata.SecondLine = mouse; 
	
	RS_DimOrdinate* dim = new RS_DimOrdinate(preview, data, edata);
	
	preview->addEntity(dim);
	
	dim->update();
     }

  drawPreview();
   
  //graphicView->redraw(RS2::RedrawOverlay);
   
}



void RS_ActionDimOrdinate::mouseReleaseEvent(QMouseEvent* e) 
{
   if (e->button()==Qt::LeftButton) 
     {
        RS_CoordinateEvent ce(snapPoint(e));
        coordinateEvent(&ce);
     }
   else if (e->button()==Qt::RightButton) 
     {
        deletePreview();
        init(getStatus()-1);
     }
}



void RS_ActionDimOrdinate::coordinateEvent(RS_CoordinateEvent* e) 
{
   if (e==NULL)
     {
        return;
     }
   
   RS_Vector pos = e->getCoordinate();
   
   switch (getStatus())
     {
      case SetOriginPoint:

       edata.OriginPoint = pos;

       data.definitionPoint = pos;

       writeSettingsOriginPoint();
       
       graphicView->moveRelativeZero(pos);
       
       preparePreview();
       
       showOrigin();
       
       drawPreview();
	
	// std::cout << "rs_actiondimordinate.cpp pos : " << edata.OriginPoint << "\n";
	
	
	if (RS_DIALOGFACTORY!=NULL)
	  RS_DIALOGFACTORY->updateDimOrdinateOptions(edata.OriginPoint.x, edata.OriginPoint.y, false, X_type);	
	
	setStatus(SetFirstLine);
	break;
	
      case SetFirstLine:
	edata.FirstLine = pos;
	graphicView->moveRelativeZero(pos);
	
       // std::cout << "rs_actiondimordinate.cpp vor setStatus  \n";
	
	setStatus(SetSecondLine);
	break;
	
      case SetSecondLine:
	edata.SecondLine = pos;
	trigger();
	reset();
	setStatus(SetFirstLine);
	break;
	
      default:
	break;
     }
}



void RS_ActionDimOrdinate::commandEvent(RS_CommandEvent* e) 
{
   QString c = e->getCommand().toLower();
   
   if (checkCommand("help", c)) 
     {
        if (RS_DIALOGFACTORY!=NULL) 
	  {
	     RS_DIALOGFACTORY->commandMessage(msgAvailableCommands()
					      + getAvailableCommands().join(", "));
	  }
        return;
     }
   
}



QStringList RS_ActionDimOrdinate::getAvailableCommands() {
   QStringList cmd;
   
   switch (getStatus()) {
    case SetOriginPoint:
    case SetFirstLine:
    case SetSecondLine:
      cmd += command("text");
      break;
      
    default:
      break;
   }
   
   return cmd;
}


void RS_ActionDimOrdinate::updateMouseButtonHints() {
   if (RS_DIALOGFACTORY!=NULL) {
      switch (getStatus()) {
       case SetOriginPoint:
	 RS_DIALOGFACTORY->updateMouseWidget(
					     tr("Specify origin point"),
					     tr("Cancel"));
	 break;
       case SetFirstLine:
	 RS_DIALOGFACTORY->updateMouseWidget(
					     tr("Specify first line"),
					     tr("Back"));
	 break;
       case SetSecondLine:
	 RS_DIALOGFACTORY->updateMouseWidget(
					     tr("Specify second line"),
					     tr("Back"));
	 break;
       default:
	 RS_DIALOGFACTORY->updateMouseWidget("", "");
	 break;
      }
   }
}



void RS_ActionDimOrdinate::showOptions() {
   RS_ActionInterface::showOptions();
   
   if (RS_DIALOGFACTORY!=NULL) {
      
      
      RS_DIALOGFACTORY->requestOptions(this, true, true);
   }
}



void RS_ActionDimOrdinate::hideOptions() {
   RS_ActionInterface::hideOptions();
   
   if (RS_DIALOGFACTORY!=NULL) {
      
      RS_DIALOGFACTORY->requestOptions(this, false);
   }
}


void RS_ActionDimOrdinate::setOrig(bool a)
{
   set_Origin = a;
   
   if(a == true)
     {
	setStatus(SetOriginPoint);
	
	
     }
}

void RS_ActionDimOrdinate::setXtype(bool a)
{
   // std::cout << "rs_actiondimordinate.cpp setXtype a= " << a << " \n";
      
   X_type = a;
   edata.is_x_type = a;
   
}

void RS_ActionDimOrdinate::setOriginXY(double x, double y)
{
  edata.OriginPoint.x = x; 
  edata.OriginPoint.y = y; 
  
  data.definitionPoint = edata.OriginPoint;
  
  //graphicView->moveRelativeZero(edata.OriginPoint);
  
  //preparePreview();
  
  //showOrigin();
  
  //drawPreview();
  
  writeSettingsOriginPoint();
}

void RS_ActionDimOrdinate::writeSettingsOriginPoint()
{
  RS_SETTINGS->beginGroup("/DimOrdinate");
  RS_SETTINGS->writeEntry("/OriginX", edata.OriginPoint.x);
  RS_SETTINGS->writeEntry("/OriginY", edata.OriginPoint.y);
  RS_SETTINGS->endGroup();
  
}

// EOF
