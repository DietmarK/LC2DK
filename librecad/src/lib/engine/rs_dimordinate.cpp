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

/* kopiert von rs_dimlinear.cpp , angepasst  */

#include "rs_dimordinate.h"
#include "rs_constructionline.h"
#include "rs_mtext.h"
#include "rs_solid.h"
#include "rs_graphic.h"
#include "rs_settings.h"


/**
 * Constructor.
 *
 * @para parent Parent Entity Container.
 * @para d Common dimension geometrical data.
 * @para ed Extended geometrical data for linear dimension.
 */
RS_DimOrdinate::RS_DimOrdinate(RS_EntityContainer* parent,
                           const RS_DimensionData& d,
                           const RS_DimOrdinateData& ed)
        : RS_Dimension(parent, d), edata(ed)
{
  RS_SETTINGS->beginGroup("/DimOrdinate");
  SecondLineLength = RS_SETTINGS->readEntry("/SecondLineLength", "9.0").toDouble();
  ConnectingLineLength = RS_SETTINGS->readEntry("/ConnectingLineLength", "6.0").toDouble();
  RS_SETTINGS->endGroup();

  calculateBorders();
}



RS_VectorSolutions RS_DimOrdinate::getRefPoints() {
        RS_VectorSolutions ret(edata.OriginPoint, edata.FirstLine,
                                                edata.SecondLine);
        return ret;
}


/**
 * @return Automatically created label for the default
 * measurement of this dimension.
 */
QString RS_DimOrdinate::getMeasuredLabel() 
{
  // direction of dimension line
  double dist;
  
  if (edata.is_x_type)
    {
      dist = fabs (edata.OriginPoint.x - edata.FirstLine.x);
    }
  else
    {
      dist = fabs (edata.OriginPoint.y - edata.FirstLine.y);
    }
  
  RS_Graphic* graphic = getGraphic();
  
  QString ret;
  if (graphic!=NULL)
    {
      ret = RS_Units::formatLinear(dist, graphic->getUnit(), 
				   graphic->getLinearFormat(), graphic->getLinearPrecision());
    }
  else 
    {
      ret = QString("%1").arg(dist);
    }
  
  return ret;
}



bool RS_DimOrdinate::hasEndpointsWithinWindow(const RS_Vector& v1, const RS_Vector& v2) {
        return (edata.OriginPoint.isInWindow(v1, v2) ||
                edata.FirstLine.isInWindow(v1, v2) ||
		edata.SecondLine.isInWindow(v1, v2));
}



/**
 * Updates the sub entities of this dimension. Called when the
 * text or the position, alignment, .. changes.
 *
 * @param autoText Automatically reposition the text label
 */
void RS_DimOrdinate::update(bool autoText) {

    RS_DEBUG->print("RS_DimOrdinate::update");

  Q_UNUSED(autoText);
  
    clear();

  if(!edata.FirstLine.valid || !edata.SecondLine.valid || !edata.OriginPoint.valid)
    return;
  
  if (isUndone()) 
    {
      return;
    }

  RS_Vector p1, p2, p3;
  double as = getArrowSize();
  double lo = getExtensionLineOffset();
  RS_LineData ld;
  RS_Line* line;
  
  RS_Vector textPos = data.middleOfText;
  
  double angle, textAngle;
  
  double dimtxt = getTextHeight();
    
  if(edata.is_x_type)		       /* direction X */
    {  
      angle = M_PI / 2;

      if(edata.FirstLine.y > edata.SecondLine.y)
	angle += M_PI;
      
      // std::cout << "edata.is_x_type  angle = " << angle << "\n";
      p3.setPolar(lo, angle);
      p3 += edata.FirstLine;
      p1.setPolar(-(SecondLineLength + ConnectingLineLength) , angle);
      p1 += RS_Vector(edata.FirstLine.x,edata.SecondLine.y);
      ld = RS_LineData(p1, p3);
      line = new RS_Line(this, ld);    /* firstLine */
      line->setPen(RS_Pen(RS2::FlagInvalid));
      line->setLayer(NULL);
      addEntity(line);      
      
      p2.setPolar(-SecondLineLength, angle);  
      p2 += edata.SecondLine;
      ld = RS_LineData(p2, edata.SecondLine);
      line = new RS_Line(this, ld);    /* secondLine */
      line->setPen(RS_Pen(RS2::FlagInvalid));
      line->setLayer(NULL);
      addEntity(line);
      
      ld = RS_LineData(p2, p1);
      line = new RS_Line(this, ld);    /* connectingLine */
      line->setPen(RS_Pen(RS2::FlagInvalid));
      line->setLayer(NULL);
      addEntity(line);
      
      
      textAngle = M_PI / 2;      
  
    }
else		       /* direction Y */
    {
      angle = 0.0;
      
      if(edata.FirstLine.x > edata.SecondLine.x)
	angle += M_PI;
      
      //std::cout << "edata.is_x_type  angle = " << angle << "\n";
      
      p3.setPolar(lo, angle);
      p3 += edata.FirstLine;
      p1.setPolar(-(SecondLineLength + ConnectingLineLength), angle);
      p1 += RS_Vector(edata.SecondLine.x,edata.FirstLine.y);
      ld = RS_LineData(p1, p3);
      line = new RS_Line(this, ld);
      line->setPen(RS_Pen(RS2::FlagInvalid));
      line->setLayer(NULL);
      addEntity(line);      
      
      p2.setPolar(-SecondLineLength, angle);  
      p2 += edata.SecondLine;
      ld = RS_LineData(p2, edata.SecondLine);
      line = new RS_Line(this, ld);
      line->setPen(RS_Pen(RS2::FlagInvalid));
      line->setLayer(NULL);
      addEntity(line);
      
      ld = RS_LineData(p2, p1);
      line = new RS_Line(this, ld);
      line->setPen(RS_Pen(RS2::FlagInvalid));
      line->setLayer(NULL);
      addEntity(line);
      
      textAngle = 0.0;
    }
  
  RS_MTextData   textData = RS_MTextData(textPos,
					 dimtxt, 30.0,
					 data.valign,	/* RS_MTextData::VABottom, */
					 data.halign,    /* RS_MTextData::HACenter, */
					 RS_MTextData::LeftToRight,
					 RS_MTextData::Exact,
					 1.0,
					 getLabel(),
					 "standard",
					 textAngle);
  
  RS_MText* text = new RS_MText(this, textData);
  
      // move text to the side:
      
  text->setPen(RS_Pen(RS2::FlagInvalid));
           text->setLayer(NULL);
           addEntity(text);
   
   if(false)	   /* definitionPoint = ???? */
     {
	RS_CircleData cd;
	cd = RS_CircleData(data.definitionPoint, 5.555);
	RS_Circle* c = new RS_Circle(this, cd);
	addEntity(c);
     }
   
  calculateBorders();
  
}



void RS_DimOrdinate::move(const RS_Vector& offset) 
{
    RS_Dimension::move(offset);

    edata.SecondLine.move(offset);
    edata.FirstLine.move(offset);
    edata.OriginPoint.move(offset);
  
  update();
}



void RS_DimOrdinate::rotate(const RS_Vector& center, const double& angle) 
{
  if(fabs(angle) < RS_TOLERANCE)
    return;
  
    RS_Vector angleVector(angle);
    RS_Dimension::rotate(center, angleVector);

  // I think it doesn't make sense for ordinate dimensions
 
  
  edata.SecondLine = RS_Vector(false);
  edata.FirstLine = RS_Vector(false);
  edata.OriginPoint = RS_Vector(false);
  
  update();  
   
   //std::cout << "RS_DimOrdinate::rotate(const RS_Vector& center, const double& angle) : " << angle << "\n";
}


void RS_DimOrdinate::rotate(const RS_Vector& center, const RS_Vector& angleVector) 
{
    if(fabs(angleVector.angle()) < RS_TOLERANCE)
          return;
    
    RS_Dimension::rotate(center, angleVector);

  // I think it doesn't make sense for ordinate dimensions
    
  edata.SecondLine = RS_Vector(false);
  edata.FirstLine = RS_Vector(false);
  edata.OriginPoint = RS_Vector(false);
    
  update();

  // std::cout << "RS_DimOrdinate::rotate(const RS_Vector& center, const RS_Vector& angleVector) \n";
}



void RS_DimOrdinate::scale(const RS_Vector& center, const RS_Vector& factor) 
{
    RS_Dimension::scale(center, factor);

  edata.SecondLine.scale(center, factor);
  edata.FirstLine.scale(center, factor);
  edata.OriginPoint.scale(center, factor);
  
  update();
}



void RS_DimOrdinate::mirror(const RS_Vector& axisPoint1, const RS_Vector& axisPoint2) {
    RS_Dimension::mirror(axisPoint1, axisPoint2);

  // it makes sense only in axis direction
  
  if ((fabs(axisPoint1.x - axisPoint2.x) < RS_TOLERANCE) || (fabs(axisPoint1.y - axisPoint2.y) < RS_TOLERANCE))
    {
      edata.SecondLine.mirror(axisPoint1, axisPoint2);
    edata.FirstLine.mirror(axisPoint1, axisPoint2);
    edata.OriginPoint.mirror(axisPoint1, axisPoint2);
    }
  else
    {
       // std::cout << "RS_DimOrdinate::mirror, else \n";
       
      edata.SecondLine = RS_Vector(false);
      edata.FirstLine = RS_Vector(false);
      edata.OriginPoint = RS_Vector(false);
    }

    update();
}



void RS_DimOrdinate::stretch(const RS_Vector& firstCorner,
                           const RS_Vector& secondCorner,
                           const RS_Vector& offset) {

  Q_UNUSED(firstCorner);
  Q_UNUSED(secondCorner);
  Q_UNUSED(offset);

  // not implemented !   (do we need that ?)
  
  /*
    //e->calculateBorders();
    if (getMin().isInWindow(firstCorner, secondCorner) &&
            getMax().isInWindow(firstCorner, secondCorner)) {

        move(offset);
    } else {
        //RS_Vector v = data.definitionPoint - edata.extensionPoint2;
        //double len = edata.extensionPoint2.distanceTo(data.definitionPoint);
        //double ang1 = edata.extensionPoint1.angleTo(edata.extensionPoint2)
        //              + M_PI/2;

        if (edata.extensionPoint1.isInWindow(firstCorner,
                                            secondCorner)) {
            edata.extensionPoint1.move(offset);
        }
        if (edata.extensionPoint2.isInWindow(firstCorner,
                                            secondCorner)) {
            edata.extensionPoint2.move(offset);
        }

                / *
        double ang2 = edata.extensionPoint1.angleTo(edata.extensionPoint2)
                      + M_PI/2;

        double diff = RS_Math::getAngleDifference(ang1, ang2);
        if (diff>M_PI) {
            diff-=2*M_PI;
        }

        if (fabs(diff)>M_PI/2) {
            ang2 = RS_Math::correctAngle(ang2+M_PI);
        }

        RS_Vector v;
        v.setPolar(len, ang2);
        data.definitionPoint = edata.extensionPoint2 + v;
                * /
    }
 */
    update(true);
}



void RS_DimOrdinate::moveRef(const RS_Vector& ref, const RS_Vector& offset) 
{ 
    if (ref.distanceTo(edata.FirstLine)<1.0e-4) {
        edata.FirstLine += offset;
                update(true);
    }
        else if (ref.distanceTo(data.middleOfText)<1.0e-4) {
        data.middleOfText += offset;
                update(false);
    }
        else if (ref.distanceTo(edata.SecondLine)<1.0e-4) {
        edata.SecondLine += offset;
                update(true);
    }
        else if (ref.distanceTo(edata.OriginPoint)<1.0e-4) {
        edata.OriginPoint += offset;
                update(true);
    }

}

/**
 * Dumps the point's data to stdout.
 */
std::ostream& operator << (std::ostream& os, const RS_DimOrdinate& d) {
    os << " DimOrdinate: data: " << d.getData() << "\n   edata: " << d.getEData() << "\n";
    return os;
}

