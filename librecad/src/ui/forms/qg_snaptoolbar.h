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
#ifndef QG_SNAPTOOLBAR_H
#define QG_SNAPTOOLBAR_H

class QG_CadToolBar;
class QG_ActionHandler;

#include <QToolBar>

#include "rs_snapper.h"
#include "qg_actionhandler.h"

// #include "ui_qg_snaptoolbar.h"      /* ++++++++++++++++++++  */

#include <QtGui/QAction>


class QG_SnapToolBar : public QToolBar
{
    Q_OBJECT
        
public:
    QG_SnapToolBar( const QString & title, QG_ActionHandler* ah, QWidget * parent = 0 );
    virtual ~QG_SnapToolBar();

    RS_SnapMode getSnaps ( void );
    void saveSnapMode(void );
    virtual void setActionHandler(QG_ActionHandler* ah);
    bool lockedRelativeZero();
    void setLockedRelativeZero(bool on);
    QVector<QAction*> getActions() const;

   void disableSnaps();		       /* +++++++++++++ */
   
protected:
    QG_ActionHandler* actionHandler;

private slots:
    void actionTriggered(void);
    void slotRestrictOrthogonal(bool checked);
    void slotRestrictNothing(bool checked);

   /* ++++++++++++++++++ */
   void slot_autoSnapOnEndpoint();
   void slot_autoSnapOnIntersection();
   void slot_autoSnapOnGrid();
   void slot_autoSnapOnMiddle();
   void slot_autoSnapOnCenter();
   /* ++++++++++++++++++++ */
     
public slots:
    void setSnaps(RS_SnapMode);
   
   /* ++++++++++++++++++++++++ */
   void slotSIM0();
   void slotSIM1();
   void aTsnapFree();
   void aTsnapGrid();
   void aTsnapEnd();
   void aTsnapOnEntity();
   void aTsnapCenter();
   void aTsnapMiddle();
   void aTsnapDistance();
   void aTsnapIntersection();
   void aTsnapAuto();
   void aTsnapOnHatch();
   void aTsnapOnText();
   void aTsnapOnInsert();
   void aTsnapOnPolyline();
   void aTsnapOnSpline();
   void aTsnapOnDimension();
   /* +++++++++++++++++++++++++++ */

signals:
    void snapsChanged(RS_SnapMode);

private:
    QAction *snapFree;
    QAction *snapGrid;
    QAction *snapEnd;
    QAction *snapOnEntity;
    QAction *snapCenter;
    QAction *snapMiddle;
    QAction *snapDistance;
    QAction *snapIntersection;
   
   /* ++++++++++++++++++++++++ */
    QAction *snapAuto;
    QAction *snapOnHatch;
    QAction *snapOnText;
    QAction *snapOnInsert;
    QAction *snapOnPolyline;
    QAction *snapOnSpline;
    QAction *snapOnDimension;
   
   QAction *SnapIntersectionManual;
   QAction *autoSnapOnEndpoint;   
   QAction *autoSnapOnIntersection;   
   QAction *autoSnapOnGrid;   
   QAction *autoSnapOnMiddle;   
   QAction *autoSnapOnCenter;      
   /* ++++++++++++++++++++++ */
   
    QAction *restrictHorizontal;
    QAction *restrictVertical;
    QAction *restrictOrthogonal;
    QAction *restrictNothing;
    QAction *bRelZero;
    QAction *bLockRelZero;
    RS_SnapMode snapMode;
    QVector<QAction*> m_vSnapActions;
    int m_iActionCounts;

    void init();


   int SnapDK;			       /* +++++++++++++ single SnapMode, or Auto */
};

#endif // QG_SNAPTOOLBAR_H
