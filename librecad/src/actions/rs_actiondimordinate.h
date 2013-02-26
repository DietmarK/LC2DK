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

/* kopiert von rs_actiondimlinear.h */

#ifndef RS_ACTIONDIMORDINATE_H
#define RS_ACTIONDIMORDINATE_H

#include "rs_actiondimension.h"
// #include "rs_dimlinear.h"
#include "rs_dimordinate.h"

/**
 * This action class can handle user events to draw 
 * aligned dimensions.
 *
 * @author Andrew Mustun
 */
class RS_ActionDimOrdinate : public RS_ActionDimension {
	Q_OBJECT
public:
    /**
     * Action States.
     */
    enum Status {
        SetFirstLine,
        SetSecondLine,
        SetOriginPoint
    };

public:
    RS_ActionDimOrdinate(RS_EntityContainer& container,
                       RS_GraphicView& graphicView,
                       RS2::ActionType type = RS2::ActionDimOrdinate);
   
    ~RS_ActionDimOrdinate();
	
   static QAction* createGUIAction(RS2::ActionType type, QObject* /*parent*/);
	
    virtual RS2::ActionType rtti();

    void reset();

    virtual void trigger();

   void preparePreview();
	
    virtual void mouseMoveEvent(QMouseEvent* e);
   
   virtual void mouseReleaseEvent(QMouseEvent* e);

	virtual void coordinateEvent(RS_CoordinateEvent* e);
    virtual void commandEvent(RS_CommandEvent* e);
        virtual QStringList getAvailableCommands();
	
    virtual void hideOptions();
    virtual void showOptions();
	
    virtual void updateMouseButtonHints();

   double getOriginX()
     {
       return edata.OriginPoint.x;
     }
   
   void setOriginXY(double x, double y);
   
   double getOriginY()
     {
       return edata.OriginPoint.y;
     }
   
   bool getXtype()
     {
       return X_type;
     }
   
   void setXtype(bool a);
   
   void setOrig(bool a);
   
   bool getOrig()
     {
       return set_Origin;
     }

protected:
    /**
     * Ordinate dimension data.
     */
    RS_DimOrdinateData edata;

   /** Last status before entering text or angle. */
    Status lastStatus;
    RS2::ActionType actionType;
   
   bool X_type;
   bool set_Origin;

   double textDist;
   void showOrigin();
   void writeSettingsOriginPoint();
};

#endif
