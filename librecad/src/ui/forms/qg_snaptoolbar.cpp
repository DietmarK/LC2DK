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
#include <QContextMenuEvent>
#include <QToolBar>

#include "qg_snaptoolbar.h"
#include "rs_settings.h"
#include "rs_snapper.h"		       /* +++++++++++++++ */
/*
 *  Constructs a QG_CadToolBarSnap as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
QG_SnapToolBar::QG_SnapToolBar( const QString & title, QG_ActionHandler* ah, QWidget * parent )
  : QToolBar(title, parent)
    ,m_iActionCounts(0)
{
   actionHandler=ah;
   actionHandler->setSnapToolBar(this);
   init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_SnapToolBar::~QG_SnapToolBar()
{
   //@Save default snap mode to prefrences.
   //never being called
   
   // saveSnapMode();
   
   // no need to delete child widgets, Qt does it all for us
}

void QG_SnapToolBar::saveSnapMode()
{
   //@write default snap mode from prefrences.
   unsigned int snapFlags=RS_Snapper::snapModeToInt(getSnaps());
   
   // std::cout << "saveSnapMode() :  " << snapFlags  << "\n";
   
   
   RS_SETTINGS->beginGroup("/Snap");
   RS_SETTINGS->writeEntry("/SnapMode",QString::number(snapFlags));
   RS_SETTINGS->endGroup();
   // no need to delete child widgets, Qt does it all for us
}

void QG_SnapToolBar::setSnaps ( RS_SnapMode s )
{
if(SnapDK)
     snapAuto->setChecked(s.snapAuto);  /* ++++++++++++++++++++ */
   
   snapFree->setChecked(s.snapFree);
   snapGrid->setChecked(s.snapGrid);
   snapEnd->setChecked(s.snapEndpoint);
   snapOnEntity->setChecked(s.snapOnEntity);
   snapCenter->setChecked(s.snapCenter);
   snapMiddle->setChecked(s.snapMiddle);
   snapDistance->setChecked(s.snapDistance);
   snapIntersection->setChecked(s.snapIntersection);
   restrictHorizontal->setChecked(s.restriction==RS2::RestrictHorizontal ||  s.restriction==RS2::RestrictOrthogonal);
   restrictVertical->setChecked(s.restriction==RS2::RestrictVertical ||  s.restriction==RS2::RestrictOrthogonal);
   restrictOrthogonal->setChecked(s.restriction==RS2::RestrictOrthogonal);
   restrictNothing->setChecked(s.restriction==RS2::RestrictNothing);
}

RS_SnapMode QG_SnapToolBar::getSnaps ( void )
{
   RS_SnapMode s;
   
   if(SnapDK)   
     s.snapAuto         = snapAuto->isChecked();   /* +++++++++++++++++++++++++ */
   
   s.snapFree         = snapFree->isChecked();
   s.snapGrid         = snapGrid->isChecked();
   s.snapEndpoint     = snapEnd->isChecked();
   s.snapOnEntity     = snapOnEntity->isChecked();
   s.snapCenter       = snapCenter->isChecked();
   s.snapMiddle       = snapMiddle->isChecked();
   s.snapDistance       = snapDistance->isChecked();
   s.snapIntersection = snapIntersection->isChecked();
   // removed Restrict Othogonal button
   // todo simplify internal restrict rules
   if (restrictHorizontal->isChecked()) {
      if (restrictVertical->isChecked()) {
	 s.restriction = RS2::RestrictOrthogonal;
      } else {
	 s.restriction = RS2::RestrictHorizontal;
      }
   } else {
      if (restrictVertical->isChecked()) {
	 s.restriction = RS2::RestrictVertical;
      } else {
	 s.restriction = RS2::RestrictNothing;
      }
   }
   
   return s;
}

void QG_SnapToolBar::init()
{
   /* ++++++++++++++++++ */
   RS_SETTINGS->beginGroup("/Privat");
   SnapDK = RS_SETTINGS->readEntry("/SnapDK", "0").toInt();
//   RS_SETTINGS->endGroup();
   

   /* +++++++++++++++++++ */
   if (SnapDK)      
     {    
	/* snap on non-atomic entities: */
	
	snapOnHatch = new QAction(QString::fromUtf8("snap\nhatch"), this);
	snapOnHatch->setCheckable(true);
	snapOnHatch->setToolTip(QString::fromUtf8("Snap on elements from hatch"));
	connect(snapOnHatch, SIGNAL(triggered()), this, SLOT(aTsnapOnHatch()));
	
	QString SnapOnHatch =  RS_SETTINGS->readEntry("/SnapOnHatch", "0");
	snapOnHatch->setChecked(SnapOnHatch=="1");
	
	
	m_vSnapActions<<snapOnHatch;
	this->addAction(snapOnHatch);
	

	snapOnText = new QAction(QString::fromUtf8("snap\ntext"), this);
	snapOnText->setCheckable(true);
	snapOnText->setToolTip(QString::fromUtf8("Snap on elements from hatch"));
	connect(snapOnText, SIGNAL(triggered()), this, SLOT(aTsnapOnText()));
	
	QString SnapOnText =  RS_SETTINGS->readEntry("/SnapOnText", "0");
	snapOnText->setChecked(SnapOnText=="1");
	
	m_vSnapActions<<snapOnText;
	this->addAction(snapOnText);
	

       snapOnInsert = new QAction(QString::fromUtf8("snap\ninsert"), this);
	snapOnInsert->setCheckable(true);
	snapOnInsert->setToolTip(QString::fromUtf8("Snap on elements from hatch"));
	connect(snapOnInsert, SIGNAL(triggered()), this, SLOT(aTsnapOnInsert()));
	   
	QString SnapOnInsert =  RS_SETTINGS->readEntry("/SnapOnInsert", "0");
	snapOnInsert->setChecked(SnapOnInsert=="1");
	
	m_vSnapActions<<snapOnInsert;
	this->addAction(snapOnInsert);
	

	snapOnPolyline = new QAction(QString::fromUtf8("snap\npolyl."), this);
	snapOnPolyline->setCheckable(true);
	snapOnPolyline->setToolTip(QString::fromUtf8("Snap on elements from hatch"));
	connect(snapOnPolyline, SIGNAL(triggered()), this, SLOT(aTsnapOnPolyline()));
	   
	QString SnapOnPolyline =  RS_SETTINGS->readEntry("/SnapOnPolyline", "0");
	snapOnPolyline->setChecked(SnapOnPolyline=="1");
	
	m_vSnapActions<<snapOnPolyline;
	this->addAction(snapOnPolyline);
	

	snapOnSpline = new QAction(QString::fromUtf8("snap\nspline"), this);
	snapOnSpline->setCheckable(true);
	snapOnSpline->setToolTip(QString::fromUtf8("Snap on elements from hatch"));
	connect(snapOnSpline, SIGNAL(triggered()), this, SLOT(aTsnapOnSpline()));
	   
	QString SnapOnSpline =  RS_SETTINGS->readEntry("/SnapOnSpline", "0");
	snapOnSpline->setChecked(SnapOnSpline=="1");
	
	m_vSnapActions<<snapOnSpline;
	this->addAction(snapOnSpline);
	

	snapOnDimension = new QAction(QString::fromUtf8("snap\ndimens."), this);
	snapOnDimension->setCheckable(true);
	snapOnDimension->setToolTip(QString::fromUtf8("Snap on elements from hatch"));
	connect(snapOnDimension, SIGNAL(triggered()), this, SLOT(aTsnapOnDimension()));
	   
	QString SnapOnDimension =  RS_SETTINGS->readEntry("/SnapOnDimension", "0");
	snapOnDimension->setChecked(SnapOnDimension=="1");
	
	m_vSnapActions<<snapOnDimension;
	this->addAction(snapOnDimension);
   
        this->addSeparator();
     }
   

   /* +++++++++++++++++++ */
   
   snapFree = new QAction(QIcon(":/extui/snapfree.png"), tr("Free Snap"), this);
   snapFree->setCheckable(true);
   connect(snapFree, SIGNAL(triggered()), this, SLOT(aTsnapFree()));
   m_vSnapActions<<snapFree;
   this->addAction(snapFree);
   
   snapGrid = new QAction(QIcon(":/extui/snapgrid.png"), tr("Snap on grid"), this);
   snapGrid->setCheckable(true);
   connect(snapGrid, SIGNAL(triggered()), this, SLOT(aTsnapGrid()));
   m_vSnapActions<<snapGrid;
   this->addAction(snapGrid);
   
   snapEnd = new QAction(QIcon(":/extui/snapendpoint.png"), tr("Snap on Endpoints"), this);
   snapEnd->setCheckable(true);
   connect(snapEnd, SIGNAL(triggered()), this, SLOT(aTsnapEnd()));
   m_vSnapActions<<snapEnd;
   this->addAction(snapEnd);
   
   snapOnEntity = new QAction(QIcon(":/extui/snaponentity.png"), tr("Snap on Entity"), this);
   snapOnEntity->setCheckable(true);
   connect(snapOnEntity, SIGNAL(triggered()), this, SLOT(aTsnapOnEntity()));
   m_vSnapActions<<snapOnEntity;
   this->addAction(snapOnEntity);
   
   snapCenter = new QAction(QIcon(":/extui/snapcenter.png"), tr("Snap Center"), this);
   snapCenter->setCheckable(true);
   connect(snapCenter, SIGNAL(triggered()), this, SLOT(aTsnapCenter()));
   m_vSnapActions<<snapCenter;
   this->addAction(snapCenter);
   
   snapMiddle = new QAction(QIcon(":/extui/snapmiddle.png"), tr("Snap Middle"), this);
   snapMiddle->setCheckable(true);
   connect(snapMiddle, SIGNAL(triggered()), this, SLOT(aTsnapMiddle()));
   m_vSnapActions<<snapMiddle;
   this->addAction(snapMiddle);
   
   snapDistance = new QAction(QIcon(":/extui/snapdist.png"), tr("Snap Distance"), this);
   snapDistance ->setCheckable(true);
   connect(snapDistance, SIGNAL(triggered()), this, SLOT(aTsnapDistance()));
   m_vSnapActions<<snapDistance;
   this->addAction(snapDistance);
   
   snapIntersection = new QAction(QIcon(":/extui/snapintersection.png"), tr("Snap Intersection"), this);
   snapIntersection->setCheckable(true);
   connect(snapIntersection, SIGNAL(triggered()), this, SLOT(aTsnapIntersection()));
   m_vSnapActions<<snapIntersection;
   this->addAction(snapIntersection);
   
   /* +++++++++++++++++++ */
   if (SnapDK)
     {
	
	this->addSeparator();
	
	SnapIntersectionManual = new QAction(QString::fromUtf8("SIM\n(sx)"), this);
	SnapIntersectionManual->setCheckable(true);
	SnapIntersectionManual->setToolTip(QString::fromUtf8("Snap Intersection Manually"));
	
	// connect(SnapIntersectionManual, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    
	connect(SnapIntersectionManual, SIGNAL(triggered()), actionHandler, SLOT(slotSnapIntersectionManual()));
	
//	connect(SnapIntersectionManual, SIGNAL(triggered()), this, SLOT(slotSIM0()));
	
	m_vSnapActions<<SnapIntersectionManual;
	this->addAction(SnapIntersectionManual);
	
	/* ----------------------- */
	
	this->addSeparator();
	
	snapAuto = new QAction(QString::fromUtf8("snap auto\n(sy)"), this);
	snapAuto->setCheckable(true);
	snapAuto->setToolTip(QString::fromUtf8("Snap Auto"));
	
	
    
	connect(snapAuto, SIGNAL(triggered()), actionHandler, SLOT(slotSnapAuto()));
	
	connect(snapAuto, SIGNAL(triggered()), this, SLOT(aTsnapAuto()));
	
	m_vSnapActions<<snapAuto;
	this->addAction(snapAuto);
	
	this->addSeparator();

	/* ----------------------- */
	
	/* snap modes for auto */
	
	autoSnapOnEndpoint = new QAction(QString::fromUtf8("autosnap\nendpoint"), this);
	autoSnapOnEndpoint->setCheckable(true);
	autoSnapOnEndpoint->setToolTip(QString::fromUtf8("autosnap on endpoints"));
	connect(autoSnapOnEndpoint, SIGNAL(triggered()), this, SLOT(slot_autoSnapOnEndpoint()));
   
	// RS_SETTINGS->beginGroup("/Privat");
   	// 
	QString AutoSnapOnEndp =  RS_SETTINGS->readEntry("/AutoSnapOnEndpoint", "1");
	autoSnapOnEndpoint->setChecked(AutoSnapOnEndp=="1");   
	     
	m_vSnapActions<<autoSnapOnEndpoint;
	this->addAction(autoSnapOnEndpoint);
   
	/* ----------------------- */

	autoSnapOnIntersection = new QAction(QString::fromUtf8("autosnap\nintersec."), this);
	autoSnapOnIntersection->setCheckable(true);
	autoSnapOnIntersection->setToolTip(QString::fromUtf8("autosnap on intersections"));
	connect(autoSnapOnIntersection, SIGNAL(triggered()), this, SLOT(slot_autoSnapOnIntersection()));
   
	// RS_SETTINGS->beginGroup("/Privat");
   	
	QString AutoSnapOnInters =  RS_SETTINGS->readEntry("/AutoSnapOnIntersection", "1");
	autoSnapOnIntersection->setChecked(AutoSnapOnInters=="1");   
	     
	m_vSnapActions<<autoSnapOnIntersection;
	this->addAction(autoSnapOnIntersection);
   
	/* ----------------------- */

	autoSnapOnGrid = new QAction(QString::fromUtf8("autosnap\ngrid"), this);
	autoSnapOnGrid->setCheckable(true);
	autoSnapOnGrid->setToolTip(QString::fromUtf8("autosnap on grid"));
	connect(autoSnapOnGrid, SIGNAL(triggered()), this, SLOT(slot_autoSnapOnGrid()));
   
	// RS_SETTINGS->beginGroup("/Privat");
   	 
	QString AutoSnapOnGrid =  RS_SETTINGS->readEntry("/AutoSnapOnGrid", "1");
	autoSnapOnGrid->setChecked(AutoSnapOnGrid=="1");   
	     
	m_vSnapActions<<autoSnapOnGrid;
	this->addAction(autoSnapOnGrid);
   
	/* ----------------------- */

	autoSnapOnMiddle = new QAction(QString::fromUtf8("autosnap\nmiddle"), this);
	autoSnapOnMiddle->setCheckable(true);
	autoSnapOnMiddle->setToolTip(QString::fromUtf8("autosnap on grid"));
	connect(autoSnapOnMiddle, SIGNAL(triggered()), this, SLOT(slot_autoSnapOnMiddle()));
   
	// RS_SETTINGS->beginGroup("/Privat");
   	 
	QString AutoSnapOnMiddle =  RS_SETTINGS->readEntry("/AutoSnapOnMiddle", "1");
	autoSnapOnMiddle->setChecked(AutoSnapOnMiddle=="1");   
	     
	m_vSnapActions<<autoSnapOnMiddle;
	this->addAction(autoSnapOnMiddle);
   
	/* ----------------------- */

	autoSnapOnCenter = new QAction(QString::fromUtf8("autosnap\ncenter"), this);
	autoSnapOnCenter->setCheckable(true);
	autoSnapOnCenter->setToolTip(QString::fromUtf8("autosnap on grid"));
	connect(autoSnapOnCenter, SIGNAL(triggered()), this, SLOT(slot_autoSnapOnCenter()));
   
	// RS_SETTINGS->beginGroup("/Privat");
   	 
	QString AutoSnapOnCenter =  RS_SETTINGS->readEntry("/AutoSnapOnCenter", "1");
	autoSnapOnCenter->setChecked(AutoSnapOnCenter=="1");   
	     
	m_vSnapActions<<autoSnapOnCenter;
	this->addAction(autoSnapOnCenter);   		
     }
   
   RS_SETTINGS->endGroup();
	
   /* +++++++++++++++++++ */
   
   
   this->addSeparator();
   
   /* +++++++++++++++++++ */
	
	
   
   
   
   m_iActionCounts = m_vSnapActions.size();
   
   this->addSeparator();
   
   /*
    restrictOrthoagonal = new QAction(QIcon(":/extui/restrictorthogonal.png"),
    "Restrict Orthogonal", this);
    restrictOrthoagonal->setCheckable(true);
    connect(restrictOrthoagonal, SIGNAL(triggered(bool)),
    this, SLOT(restrictOrthoagonalTriggered(bool)));
    connect(restrictOrthoagonal, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    this->addAction(restrictOrthoagonal);
    */
   restrictHorizontal = new QAction(QIcon(":/extui/restricthorizontal.png"),
				    tr("Restrict Horizontal"), this);
   restrictHorizontal->setCheckable(true);
   connect(restrictHorizontal, SIGNAL(triggered()), this, SLOT(actionTriggered()));
   m_vSnapActions<<restrictHorizontal;
   this->addAction(restrictHorizontal);
   restrictVertical = new QAction(QIcon(":/extui/restrictvertical.png"),
				  tr("Restrict Vertical"), this);
   restrictVertical->setCheckable(true);
   connect(restrictVertical, SIGNAL(triggered()), this, SLOT(actionTriggered()));
   m_vSnapActions<<restrictVertical;
   this->addAction(restrictVertical);
   
   restrictOrthogonal = new QAction(QIcon(":/extui/restrictorthogonal.png"),
				    tr("Restrict Orthogonal"), this);
   restrictOrthogonal->setCheckable(true);
   connect(restrictOrthogonal, SIGNAL(triggered(bool)), this,
	   SLOT(slotRestrictOrthogonal(bool)));
   m_vSnapActions<<restrictOrthogonal;
   
   restrictNothing = new QAction(QIcon(":/extui/restrictnothing.png"),
				 tr("Restrict Nothing"), this);
   restrictNothing->setCheckable(true);
   connect(restrictNothing, SIGNAL(triggered(bool)), this,
	   SLOT(slotRestrictNothing(bool)));
   m_vSnapActions<<restrictNothing;
   
   this->addSeparator();
   bRelZero = new QAction(QIcon(":/extui/relzeromove.png"), tr("Set relative zero position"), this);
   bRelZero->setCheckable(false);
   connect(bRelZero, SIGNAL(triggered()), actionHandler, SLOT(slotSetRelativeZero()));
   m_vSnapActions<<bRelZero;
   //connect(bRelZero, SIGNAL(triggered()), this, SLOT(slotSetRelativeZero()));
   this->addAction(bRelZero);
   bLockRelZero = new QAction(QIcon(":/extui/relzerolock.png"), tr("Lock relative zero position"), this);
   bLockRelZero->setCheckable(true);
   connect(bLockRelZero, SIGNAL(toggled(bool)),actionHandler, SLOT(slotLockRelativeZero(bool)));
   m_vSnapActions<<bLockRelZero;
   this->addAction(bLockRelZero);
   
   //restore snapMode from saved preferences
   RS_SETTINGS->beginGroup("/Snap");
   setSnaps(RS_Snapper::intToSnapMode(RS_SETTINGS->readNumEntry("/SnapMode",0)));
   RS_SETTINGS->endGroup();
}

bool QG_SnapToolBar::lockedRelativeZero()
{
   return bLockRelZero->isChecked();
}
void QG_SnapToolBar::setLockedRelativeZero(bool on)
{
   bLockRelZero->setChecked(on);
}
QVector<QAction*> QG_SnapToolBar::getActions() const
{
   return m_vSnapActions;
}
void QG_SnapToolBar::setActionHandler(QG_ActionHandler* ah){
   actionHandler=ah;
}

/* Slots */

void QG_SnapToolBar::slotRestrictNothing(bool checked)
{
   if( restrictVertical != NULL) restrictVertical->setChecked(!checked);
   if( restrictHorizontal != NULL) restrictHorizontal->setChecked(!checked);
   if( restrictOrthogonal != NULL) restrictOrthogonal->setChecked(!checked);
   actionTriggered();
}

void QG_SnapToolBar::slotRestrictOrthogonal(bool checked)
{
   if( restrictVertical != NULL) restrictVertical->setChecked(checked);
   if( restrictHorizontal != NULL) restrictHorizontal->setChecked(checked);
   if( restrictNothing != NULL) restrictNothing->setChecked(checked);
   actionTriggered();
}

void QG_SnapToolBar::actionTriggered()
{
   actionHandler->slotSetSnaps(getSnaps());
}

/* +++++++++++++++++ */

void QG_SnapToolBar::aTsnapFree()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapFree->setChecked(true);
	
	RS_SnapMode sm = getSnaps();
	sm.snapFree = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapGrid()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapGrid->setChecked(true);
	
	RS_SnapMode sm= getSnaps();
	sm.snapGrid = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapEnd()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapEnd->setChecked(true);
	
	RS_SnapMode sm= getSnaps();
	sm.snapEndpoint = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapOnEntity()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapOnEntity->setChecked(true);
	
	RS_SnapMode sm = getSnaps();
	sm.snapOnEntity = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapCenter()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapCenter->setChecked(true);
	
	RS_SnapMode sm = getSnaps();
	sm.snapCenter = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapMiddle()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapMiddle->setChecked(true);
	
	RS_SnapMode sm = getSnaps();
	sm.snapMiddle = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapDistance()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapDistance->setChecked(true);
	
	RS_SnapMode sm = getSnaps();
	sm.snapDistance = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapIntersection()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapIntersection->setChecked(true);
	
	RS_SnapMode sm = getSnaps();
	sm.snapIntersection = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

void QG_SnapToolBar::aTsnapAuto()
{
   if (SnapDK)
     {	
	disableSnaps();
	snapAuto->setChecked(true);
	
	RS_SnapMode sm = getSnaps();
	sm.snapAuto = 1;   
	setSnaps(sm);
	saveSnapMode();
     }
   
   actionHandler->slotSetSnaps(getSnaps());
}

// ------------------------------

void QG_SnapToolBar::aTsnapOnHatch()
{
   if (SnapDK)
     {	
	RS_SETTINGS->beginGroup("/Privat");
	RS_SETTINGS->writeEntry("/SnapOnHatch", QString("%1").arg((int)snapOnHatch->isChecked()));
	RS_SETTINGS->endGroup();
	
     }
}

void QG_SnapToolBar::aTsnapOnText()
{
   if (SnapDK)
     {	
	RS_SETTINGS->beginGroup("/Privat");
	RS_SETTINGS->writeEntry("/SnapOnText", QString("%1").arg((int)snapOnText->isChecked()));

       if (snapOnText->isChecked())
	 {
	   // snapOnInsert and snapOnPolyline also have to be checked 
	   
	   snapOnInsert->setChecked(true);
	   snapOnPolyline->setChecked(true);
	   RS_SETTINGS->writeEntry("/SnapOnInsert", QString("%1").arg((int)snapOnInsert->isChecked()));
	   RS_SETTINGS->writeEntry("/SnapOnPolyline", QString("%1").arg((int)snapOnPolyline->isChecked()));
	 }
	RS_SETTINGS->endGroup();
     }
}

void QG_SnapToolBar::aTsnapOnInsert()
{
   if (SnapDK)
     {	
	RS_SETTINGS->beginGroup("/Privat");
	RS_SETTINGS->writeEntry("/SnapOnInsert", QString("%1").arg((int)snapOnInsert->isChecked()));
	RS_SETTINGS->endGroup();
	
     }
}

void QG_SnapToolBar::aTsnapOnPolyline()
{
   if (SnapDK)
     {	
	RS_SETTINGS->beginGroup("/Privat");
	RS_SETTINGS->writeEntry("/SnapOnPolyline", QString("%1").arg((int)snapOnPolyline->isChecked()));
	RS_SETTINGS->endGroup();
	
     }
}

void QG_SnapToolBar::aTsnapOnSpline()
{
   if (SnapDK)
     {	
	RS_SETTINGS->beginGroup("/Privat");
	RS_SETTINGS->writeEntry("/SnapOnSpline", QString("%1").arg((int)snapOnSpline->isChecked()));
	RS_SETTINGS->endGroup();
	
     }
}

void QG_SnapToolBar::aTsnapOnDimension()
{
   if (SnapDK)
     {	
	RS_SETTINGS->beginGroup("/Privat");
	RS_SETTINGS->writeEntry("/SnapOnDimension", QString("%1").arg((int)snapOnDimension->isChecked()));
	RS_SETTINGS->endGroup();
	
     }
}

void  QG_SnapToolBar::slot_autoSnapOnEndpoint()
{
           RS_SETTINGS->beginGroup("/Privat");
           RS_SETTINGS->writeEntry("/AutoSnapOnEndpoint", QString("%1").arg((int)autoSnapOnEndpoint->isChecked()));
           RS_SETTINGS->endGroup();   
}

void  QG_SnapToolBar::slot_autoSnapOnIntersection()
{
           RS_SETTINGS->beginGroup("/Privat");
           RS_SETTINGS->writeEntry("/AutoSnapOnIntersection", QString("%1").arg((int)autoSnapOnIntersection->isChecked()));
           RS_SETTINGS->endGroup();   
}

void  QG_SnapToolBar::slot_autoSnapOnGrid()
{
           RS_SETTINGS->beginGroup("/Privat");
           RS_SETTINGS->writeEntry("/AutoSnapOnGrid", QString("%1").arg((int)autoSnapOnGrid->isChecked()));
           RS_SETTINGS->endGroup();   
}

void  QG_SnapToolBar::slot_autoSnapOnMiddle()
{
           RS_SETTINGS->beginGroup("/Privat");
           RS_SETTINGS->writeEntry("/AutoSnapOnMiddle", QString("%1").arg((int)autoSnapOnMiddle->isChecked()));
           RS_SETTINGS->endGroup();   
}

void  QG_SnapToolBar::slot_autoSnapOnCenter()
{
           RS_SETTINGS->beginGroup("/Privat");
           RS_SETTINGS->writeEntry("/AutoSnapOnCenter", QString("%1").arg((int)autoSnapOnCenter->isChecked()));
           RS_SETTINGS->endGroup();   
}


// --------------------------------

void QG_SnapToolBar::slotSIM0()
{
   SnapIntersectionManual->setChecked(false);
   
   // SnapIntersectionManual->setStatusTip("SnapIntersectionManual");
}

void QG_SnapToolBar::slotSIM1()
{
   SnapIntersectionManual->setChecked(true);
   
   // SnapIntersectionManual->setStatusTip("SnapIntersectionManual");
}


void QG_SnapToolBar::disableSnaps() 
{
   //int mode = snapModeToInt(getSnaps());
  // unsigned int snapFlags=RS_Snapper::snapModeToInt(getSnaps());   
   
   // std::cout << "SnapDK = " << SnapDK << "    mode " << snapFlags  << "\n";

  RS_SnapMode sm = getSnaps();
  setSnaps(sm.clear());
  
   if (snapFree->isChecked()) 
     {	
	snapFree->setChecked(false);
     }
   
   if (snapGrid->isChecked()) 
     {	
	snapGrid->setChecked(false);
     }
   
   if (snapEnd->isChecked()) 
     {	
	snapEnd->setChecked(false);
     }
   
   if (snapOnEntity->isChecked()) 
     {	
	snapOnEntity->setChecked(false);
     }
   
   if (snapCenter->isChecked()) 
     {	
	snapCenter->setChecked(false);
     }
   
   if (snapMiddle->isChecked()) 
     {	
	snapMiddle->setChecked(false);
     }
   
   if (snapDistance->isChecked()) 
     {	
	snapDistance->setChecked(false);
     }
   
   if (snapIntersection->isChecked()) 
     {	
	snapIntersection->setChecked(false);
     }
   
   if (snapAuto->isChecked()) 
     {	
	snapAuto->setChecked(false);
     }
   
   /* ist nicht noetig: */
   if (SnapIntersectionManual->isChecked()) 
     {	
	SnapIntersectionManual->setChecked(false);
     }
   
}
