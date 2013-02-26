/*****************************************************************************/
/* bores : produces NC-lines for a group of bore holes                        */ 
/*        in Heidenhain dialog language                                      */
/*                                                                           */
/*  some parts copied from list.cpp :                                        */
/*  Copyright (C) 2011 Rallaz, rallazz@gmail.com                             */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#include <QtGui>

#include <QTextEdit>
#include <QColor>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <math.h>
#include <QtGui/QApplication>

#include "document_interface.h"

#include "bores.h"

#include "../../cam/filenames.h"
  
#include <iostream> 		       /* only for debug */

// ------------------

int abs_diff (double a, double b)
{
   double c;
   
   c = fabs ( a - b );
   
   if ( c > 0.0003 )		       /*  max. abweichung zum letzten punkt */
     return 1;
   else
     return 0;
   
}
  
// ------------------------------------

void LC_bores::execComm(Document_Interface *doc,
		       QWidget *parent, QString cmd)
{
   Q_UNUSED(parent);
   Q_UNUSED(cmd);
      
   QList<Plug_Entity *> obj;	       /* will be filled with selected entities */
   
   bool yes  = doc->getSelect(&obj);
   
   if (!yes || obj.isEmpty()) return;
       
   liste1.clear();
   
   int count_circles = 0;
   
   int j;

   for (j = 0; j < obj.size(); ++j) 
     {
	QHash<int, QVariant> data2;    /* element-daten aus librecad */
	
	EntityData le;		       /* ziel fuer daten aus data2, gefiltert nach le.typ, unsortiert */

	le.x1 = le.y1 = le.x2 = le.y2 = le.len = le.wi = le.r = le.w1 = le.w2 = le.ccx = le.ccy = 0;
	le.cw = 0;
	
	obj.at(j)->getData(&data2);
	
	le.typ = data2.value(DPI::ETYPE).toInt();
	
	int found = 0;

	//specific entity data
	switch (le.typ) 
	  {	     
	   case DPI::CIRCLE:
	   case DPI::ARC:
	     
	     le.ccx = data2.value(DPI::STARTX).toDouble();
	     le.ccy = data2.value(DPI::STARTY).toDouble();
             le.r   = data2.value(DPI::RADIUS).toDouble();
	     
	     
	     // doubletten ?
	     
	     if(0 < liste1.size())
	       {
		  for(int k=0; k<liste1.size(); ++k)
		    {
		       //std::cerr << k << "   " << liste1[k].ccx << "   " << liste1[k].ccy << "   " << liste1[k].r << "\n";
		   
		       // radius may be different
		       
		       if(0 == abs_diff(liste1[k].ccx, le.ccx)  &&  0 == abs_diff(liste1[k].ccy, le.ccy))
			 found++;
		    }
	       }
	     
	     if(0 == found)
	       {
		  liste1 << le;
		  count_circles++;
	       }
	     
	     break;

	   default:
	     break;
	  }
     }				       /* for (j = 0; j < obj.size(); ++j) */

   
   
   // write all values into a file (for postprocessor)
   
   QString filename(cad_to_cam_exch_file);
   
   QFile ofile(filename);
   
   if (! ofile.open(QIODevice::WriteOnly))
     {
	std::cerr << "\n err bei file.open \n" ;
     }
   else
     {
	QTextStream t(&ofile);

	t << "programmtyp" << "\n" << "bohren"  << "\n";
	t << "listlength" << "\n" << count_circles << "\n";
	
	for (int i = 0; i < count_circles; ++i) 
	  {        
	     t << "index" << "\n" << i  << "\n"; 	     
	     t << "typ" << "\n" << liste1[i].typ << "\n";
	     t << "cw" << "\n" << liste1[i].cw << "\n";
	     t << "x1" << "\n" << liste1[i].x1 << "\n";
	     t << "y1" << "\n" << liste1[i].y1 << "\n";
	     t << "x2" << "\n" << liste1[i].x2 << "\n";
	     t << "y2" << "\n" << liste1[i].y2 << "\n";
	     t << "len" << "\n" << liste1[i].len << "\n";
	     t << "wi" << "\n" << liste1[i].wi << "\n";
	     t << "r" << "\n" << liste1[i].r << "\n";
	     t << "w1" << "\n" << liste1[i].w1 << "\n";
	     t << "w2" << "\n" << liste1[i].w2 << "\n";
	     t << "ccx" << "\n" << liste1[i].ccx << "\n";
	     t << "ccy" << "\n" << liste1[i].ccy << "\n";

	     //	     t << "" << "\n" << liste1[i]. << "\n";
	     	
	  }
	
	t << "ende" << "\n" << 0 << "\n";
	
	ofile.close();
     }
   
   
   while (!obj.isEmpty())
     delete obj.takeFirst();
   
   // ----------------------------
   
   // start the "postprocessor":
   
   int ret = system(cam_exec_file);
   
   if(0)
     std::cerr << "\n cam returned: " << ret << "\n";

}

// -----------------------

QString LC_bores::name() const
{
   return (tr("bores"));
}

PluginCapabilities LC_bores::getCapabilities() const
{
   PluginCapabilities pluginCapabilities;
   pluginCapabilities.menuEntryPoints
     << PluginMenuLocation("CAM", tr("bores"));
   return pluginCapabilities;
}

Q_EXPORT_PLUGIN2(lc_bores, LC_bores);
