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

// ++++++++++++++++++++++++++++++


#ifndef RS_ACTIONSELECTCIRCLES_H
#define RS_ACTIONSELECTCIRCLES_H

// #include "rs_actioninterface.h"
#include "rs_previewactioninterface.h"


/**
 * This action class can handle user events to select circles with same diameter.
 *
 * @author Andrew Mustun
 */
class RS_ActionSelectCircles : public RS_PreviewActionInterface 
{
	Q_OBJECT
public:
    RS_ActionSelectCircles(RS_EntityContainer& container,
                          RS_GraphicView& graphicView, int select_type);


   
   
   ~RS_ActionSelectCircles() {}

    /**
     * Action States.
     */
   enum Status 
     {
	SelectCircle1,
	  SelectCircle2,
	  SetCorner1,
	  SetCorner2
     };

       
   static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

   virtual RS2::ActionType rtti() {return RS2::ActionSelectCircles;}

    virtual void init(int status=0);
   
   virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
	
    virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
    virtual void updateToolBar();

    virtual void trigger();

private:
    RS_Entity* circle1;
    RS_Entity* circle2;
   int select_type;
    RS_Vector v1;
    RS_Vector v2;
};

#endif