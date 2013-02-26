/*****************************************************************************/
/* mill contour 
/*                                                                           */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#include <QFile>
#include <QTextStream>

#include <QTextEdit>
#include <QColor>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <math.h>
#include "document_interface.h"
#include "contour.h"
#include "../../cam/filenames.h"

#include  <stdio.h>
#include <iostream> 

   
// ------------------------------------


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

QString LC_contour::name() const
 {
     return (tr("mill contour"));
 }

PluginCapabilities LC_contour::getCapabilities() const
{
    PluginCapabilities pluginCapabilities;
    pluginCapabilities.menuEntryPoints
            << PluginMenuLocation("CAM", tr("mill contour"));
    return pluginCapabilities;
}


// -------------
 
// on success it returns index in liste, and set "change" to 0 or 1
// on failure it returns -1

int search_in_cam_liste (double x, double y, QList<EntityData> & liste, int l, int & change)
{
   int k;
   int a = -1;
   
   for (k = 0; k < l; ++k)
     {
	if (liste.at(k).typ == DPI::CIRCLE)
	  continue;
	
	if ((liste.at(k).typ == DPI::LINE || liste.at(k).typ == DPI::ARC)
	    && 0 == abs_diff(x, liste.at(k).x1) && 0 == abs_diff(y, liste.at(k).y1))
	  {
	     a = k;
	     change = 0;
	     break;
	  }
     }
   if (a == -1)
     {
	for (k = 0; k < l; ++k)
	  {
	if (liste.at(k).typ == DPI::CIRCLE)
	  continue;
	
	     if ((liste.at(k).typ == DPI::LINE || liste.at(k).typ == DPI::ARC)
		 && 0 == abs_diff(x, liste.at(k).x2) && 0 == abs_diff(y, liste.at(k).y2)) 
	       {
		  a = k;
		  change = 1;
		  break;
	       }
	  }
     }
   return a;
}

// -------------


EntityData change_endpoints(EntityData i)
{
   EntityData o = i;
   
	o.x1 = i.x2;
	o.y1 = i.y2;
	o.x2 = i.x1;
	o.y2 = i.y1;
        o.wi = i.wi - 180;
	if (o.wi < 0)
	  o.wi += 360;
	o.w1 = i.w2;
	o.w2 = i.w1;
	if (i.cw)
	  o.cw = 0;
	else
	  o.cw = 1;

   return o;
}


// -------------

void LC_contour::execComm(Document_Interface *doc,
                             QWidget *parent, QString cmd)
{
   Q_UNUSED(parent);
   Q_UNUSED(cmd);
   
   QPointF base1;
   
   QList<Plug_Entity *> obj;
   
   bool yes  = doc->getSelect(&obj);
    if (!yes || obj.isEmpty()) return;

   yes = doc->getPoint(&base1, QString("starte an point:"));

   if (0) 
     {
	std::cerr << " x: " << base1.x() << "    y: " << base1.y() << "\n";
     };
   
   EntityData el;
   
   QList<EntityData> cam_liste1;
      
   int j;
   for (j = 0; j < obj.size(); ++j) 
     {
	QHash<int, QVariant> data2;
	
	obj.at(j)->getData(&data2);

	if(!data2.value(DPI::VISIBLE).toInt())
	  continue;
	
	int et = data2.value(DPI::ETYPE).toInt();
	
	el.clear();
	
	el.typ = et;
		
	switch (et) 
	  {
	   case DPI::LINE:	       /* 1 */
	     
	     el.x1 = data2.value(DPI::STARTX).toDouble();
	     el.y1 = data2.value(DPI::STARTY).toDouble();
	     el.x2 = data2.value(DPI::ENDX).toDouble();
	     el.y2 = data2.value(DPI::ENDY).toDouble();
	            
	     el.len = sqrt( (el.x2 - el.x1) * (el.x2 - el.x1) + (el.y2 - el.y1) * (el.y2 - el.y1));
	     
	     el.wi = asin((el.y2 - el.y1) / el.len) * 180 / M_PI;
	     
	     if (el.x2 - el.x1 < 0)
	       el.wi = 180 - el.wi;
	     if (el.wi < 0)
	       el.wi += 360;

	     break;
	   case DPI::ARC:	       /* 4 */
	     
	     el.ccx = data2.value(DPI::STARTX).toDouble();
	     el.ccy = data2.value(DPI::STARTY).toDouble();
	     el.r = data2.value(DPI::RADIUS).toDouble();
	     el.w1 = data2.value(DPI::STARTANGLE).toDouble();
	     el.w2 = data2.value(DPI::ENDANGLE).toDouble();
	     
	     el.x1 = el.ccx + el.r * cos(el.w1);
	     el.y1 = el.ccy + el.r * sin(el.w1);
	     el.x2 = el.ccx + el.r * cos(el.w2);
	     el.y2 = el.ccy + el.r * sin(el.w2);
	     el.cw = data2.value(DPI::REVERSED).toInt();
	     
	     el.len = 0;
	     // el.wi = 0;
	     
             break;
	   case DPI::CIRCLE:	       /* 3 */
	     
	     el.ccx = data2.value(DPI::STARTX).toDouble();
	     el.ccy = data2.value(DPI::STARTY).toDouble();
	     el.r = data2.value(DPI::RADIUS).toDouble();
	     	       
	     break;
	   default:
	     break;

	  }
	cam_liste1 << el;
     }				       /* for (j = 0; j < obj.size(); ++j) */
      
   // ----------------

   int list_len = cam_liste1.size();
   
   QList<EntityData> cam_liste2;   /* sortiert, anfang <--> ende bei bedarf getauscht */
   
   int change = 0;		       /* anfang <--> ende  ??  */

   /* first element: */
   
   int m, n;
   
   m = search_in_cam_liste (base1.x(), base1.y(), cam_liste1, list_len, change );
	
//   std::cerr << " m = " << m << "    change: " << change  << "\n";

   if(m < 0)
     return;
   
   if(change)
     cam_liste2 << change_endpoints(cam_liste1[m]);
   else
     cam_liste2 << cam_liste1[m];

   cam_liste1[m].typ = DPI::UNKNOWN; 	       /* gelesen */
   
   // -----------------  die restlichen elemente kopieren:
   
   n = 0;
   
   int p;
   for (p = 0; p < list_len; ++p)
     {
	m = search_in_cam_liste (cam_liste2[n].x2, cam_liste2[n].y2, cam_liste1, list_len, change );

	if (m < 0)		       /* kein treffer */
	  break;
	
	if(change)
	  cam_liste2 << change_endpoints(cam_liste1[m]);
	else
	  cam_liste2 << cam_liste1[m];
	
	cam_liste1[m].typ = DPI::UNKNOWN;             /* gelesen */
	
	n++;
     }
   
   // -----------------  circles found ?

   for (p = 0; p < list_len; ++p)
     {
	if (cam_liste1.at(p).typ == DPI::CIRCLE)   /* 3 */
	  cam_liste2 << cam_liste1[p];
     }
   
   
   
   
   
   // ----------------------------------

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

	t << "programmtyp" << "\n" << "contour"  << "\n";
	t << "listlength" << "\n" << cam_liste2.size() << "\n";
	
	for (int i = 0; i < cam_liste2.size(); ++i) 
	  {        
	     t << "index" << "\n" << i  << "\n"; 	     
	     t << "typ" << "\n" << cam_liste2[i].typ << "\n";
	     t << "cw" << "\n" << cam_liste2[i].cw << "\n";
	     t << "x1" << "\n" << cam_liste2[i].x1 << "\n";
	     t << "y1" << "\n" << cam_liste2[i].y1 << "\n";
	     t << "x2" << "\n" << cam_liste2[i].x2 << "\n";
	     t << "y2" << "\n" << cam_liste2[i].y2 << "\n";
	     t << "len" << "\n" << cam_liste2[i].len << "\n";
	     t << "wi" << "\n" << cam_liste2[i].wi << "\n";
	     t << "r" << "\n" << cam_liste2[i].r << "\n";
	     t << "w1" << "\n" << cam_liste2[i].w1  * 180 / M_PI << "\n";
	     t << "w2" << "\n" << cam_liste2[i].w2  * 180 / M_PI << "\n";
	     t << "ccx" << "\n" << cam_liste2[i].ccx << "\n";
	     t << "ccy" << "\n" << cam_liste2[i].ccy << "\n";

	     //	     t << "" << "\n" << cam_liste2[i]. << "\n";
	     	
	  }
	
	t << "ende" << "\n" << 0 << "\n";
	
	ofile.close();
     }
   
   // ----------------------------

    while (!obj.isEmpty())
        delete obj.takeFirst();

   // start the "postprocessor":
   
   int ret = system(cam_exec_file);

    // std::cerr << "\n cam returned: " << ret << "\n";

}

// ---------------------------------------------------------

Q_EXPORT_PLUGIN2(lc_contour, LC_contour);

