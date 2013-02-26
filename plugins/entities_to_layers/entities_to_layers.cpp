/*****************************************************************************/
/* entities to layers :  some imported dxf-files have only one or two layers */ 
/*               here we create some new layers, and put entities into them  */
/*               so we can simply remove or modify groups of entities        */
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

#include <iostream>                    /* only for debug */

#include "../../cam/filenames.h"

#include "document_interface.h"

#include "rs_pen.h"

#include "entities_to_layers.h"

void LC_entities_to_layers::execComm(Document_Interface *doc,
		       QWidget *parent, QString cmd)
{
   Q_UNUSED(parent);
   Q_UNUSED(cmd);
   
   QList<Plug_Entity *> obj;
   bool yes  = doc->getSelect(&obj);
   if (!yes || obj.isEmpty()) return;
   
   QString text;
   
   for (int i = 0; i < obj.size(); ++i) 
     {
	QHash<int, QVariant> data;
	
	QString str;
	
	//common entity data
	if (obj.at(i) == 0)
	  return;
	
	obj.at(i)->getData(&data);
	
	int et = data.value(DPI::ETYPE).toInt();
	
       if (et > DPI::HATCH)
	  {
	     doc->setLayer("allDimensions");
	     data.insert(DPI::LAYER, "allDimensions");
	     obj.at(i)->updateData(&data);     
	  }
       else if (et == DPI::HATCH)
	  {
	     doc->setLayer("hatch");
	     data.insert(DPI::LAYER, "hatch");
	     obj.at(i)->updateData(&data);     
	  }
       else if (et == DPI::SPLINE)
	  {
	     doc->setLayer("spline");
	     data.insert(DPI::LAYER, "spline");
	     obj.at(i)->updateData(&data);     
	  }
	else if (et == DPI::POLYLINE)
	  {
	     doc->setLayer("polyline");
	     data.insert(DPI::LAYER, "polyline");
	     obj.at(i)->updateData(&data);     
	  }
	else if (et == DPI::INSERT)
	  {
	     doc->setLayer("insert");
	     data.insert(DPI::LAYER, "insert");
	     obj.at(i)->updateData(&data);     
	  }
	else if (et == DPI::TEXT)
	  {
	     doc->setLayer("text");
	     data.insert(DPI::LAYER, "text");
	     obj.at(i)->updateData(&data);     
	  }
	else if (et == DPI::MTEXT)
	  {
	     doc->setLayer("mtext");
	     data.insert(DPI::LAYER, "mtext");
	     obj.at(i)->updateData(&data);     
	  }
	else if (et == DPI::SOLID)
	  {
	     doc->setLayer("solid");
	     data.insert(DPI::LAYER, "solid");
	     obj.at(i)->updateData(&data);     
	  }
	else if (et == DPI::OVERLAYBOX)
	  {
	     doc->setLayer("box");
	     data.insert(DPI::LAYER, "box");
	     obj.at(i)->updateData(&data);     
	  }
	else if (et == DPI::IMAGE)
	  {
	     doc->setLayer("image");
	     data.insert(DPI::LAYER, "image");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LTYPE) == "CenterLineX2" 
		 || data.value(DPI::LTYPE) == "CenterLine2"
		 || data.value(DPI::LTYPE) == "CenterLine" )
	  {
	     doc->setLayer("centerLine");
	     data.insert(DPI::LAYER, "centerLine");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LTYPE) == "DashLine"
		 || data.value(DPI::LTYPE) == "DashLine2"
		 || data.value(DPI::LTYPE) == "DashLineX2" )
	  {
	     doc->setLayer("dashLine");
	     data.insert(DPI::LAYER, "dashLine");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.00mm"
		 || data.value(DPI::LWIDTH) ==  "0.05mm" )
	  {
	     doc->setLayer("smallLines");
	     data.insert(DPI::LAYER, "smallLines");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.09mm" )
	  {
	     doc->setLayer("Lines_009");
	     data.insert(DPI::LAYER, "Lines_009");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.13mm")
	  {
	     doc->setLayer("Lines_013");
	     data.insert(DPI::LAYER, "Lines_013");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.15mm")
	  {
	     doc->setLayer("Lines_015");
	     data.insert(DPI::LAYER, "Lines_015");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.18mm")
	  {
	     doc->setLayer("Lines_018");
	     data.insert(DPI::LAYER, "Lines_018");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.20mm")
	  {
	     doc->setLayer("Lines_020");
	     data.insert(DPI::LAYER, "Lines_020");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.25mm")
	  {
	     doc->setLayer("Lines_025");
	     data.insert(DPI::LAYER, "Lines_025");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.30mm")
	  {
	     doc->setLayer("Lines_030");
	     data.insert(DPI::LAYER, "Lines_030");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.35mm")
	  {
	     doc->setLayer("Lines_035");
	     data.insert(DPI::LAYER, "Lines_035");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.40mm")
	  {
	     doc->setLayer("Lines_040");
	     data.insert(DPI::LAYER, "Lines_040");
	     obj.at(i)->updateData(&data);     
	  }
	else if (data.value(DPI::LWIDTH) ==  "0.50mm")
	  {
	     doc->setLayer("Lines_050");
	     data.insert(DPI::LAYER, "Lines_050");
	     obj.at(i)->updateData(&data);     
	  }
	else   // if (data.value(DPI::LWIDTH).toInt() > 1 )
	  {
	     //std::cerr << data.value(DPI::LWIDTH).toString().toStdString() << " ::  " << data.value(DPI::LWIDTH).toInt() << "\n";
	     
	     doc->setLayer("otherLines");
	     data.insert(DPI::LAYER, "otherLines");
	     obj.at(i)->updateData(&data);     
	  }
     }
   
}

// -----------------------
 
QString LC_entities_to_layers::name() const
{
   return (tr("entities -> layers"));
}

PluginCapabilities LC_entities_to_layers::getCapabilities() const
{
   PluginCapabilities pluginCapabilities;
   pluginCapabilities.menuEntryPoints
     << PluginMenuLocation("CAM", tr("entities -> layers"));
   return pluginCapabilities;
}

Q_EXPORT_PLUGIN2(lc_entities_to_layers, LC_entities_to_layers);
