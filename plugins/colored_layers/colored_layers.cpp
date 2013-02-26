/*****************************************************************************/
/* colored layers :  this plugin creates some layers, with different colors, */ 
/*                   for use as tool paths, help lines ....                  */
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
	  
#include "colored_layers.h"

void LC_colored_layers::execComm(Document_Interface *doc,
		       QWidget *parent, QString cmd)
{
   Q_UNUSED(parent);
   Q_UNUSED(cmd);
   Q_UNUSED(doc);
   
   // when calling second time we need activateLayer() !
   
   doc->setLayer("mass");   
   doc->activateLayer("mass");
   doc->setCurrentLayerPen(RS_Pen(RS_Color(0,0,0), RS2::Width01, RS2::SolidLine));
   
   
   doc->setLayer("rot");
   doc->activateLayer("rot");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(255,0,0), RS2::Width05, RS2::SolidLine));
   
   doc->setLayer("gruen");
   doc->activateLayer("gruen");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(0,255,0), RS2::Width05, RS2::SolidLine));

   doc->setLayer("gelb");
   doc->activateLayer("gelb");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(255,200,0), RS2::Width08, RS2::SolidLine));

   doc->setLayer("dugelb");
   doc->activateLayer("dugelb");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(144,144,0), RS2::Width07, RS2::SolidLine));

   doc->setLayer("dugruen");
   doc->activateLayer("dugruen");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(0,133,0), RS2::Width05, RS2::SolidLine));

   doc->setLayer("blau");
   doc->activateLayer("blau");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(0,0,255), RS2::Width05, RS2::SolidLine));

   doc->setLayer("dumag");
   doc->activateLayer("dumag");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(133,0,133), RS2::Width05, RS2::SolidLine));

   doc->setLayer("magenta");
   doc->activateLayer("magenta");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(255,0,255), RS2::Width05, RS2::SolidLine));

   doc->setLayer("violett");
   doc->activateLayer("violett");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(133,0,255), RS2::Width05, RS2::SolidLine));

   doc->setLayer("cyan");
    doc->activateLayer("cyan");   
  doc->setCurrentLayerPen(RS_Pen(RS_Color(0,255,133), RS2::Width08, RS2::SolidLine));

   doc->setLayer("grau");
   doc->activateLayer("grau");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(133,133,133), RS2::Width08, RS2::SolidLine));

   
   doc->setLayer("mittellinie");
   doc->activateLayer("mittellinie");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(255,255,255), RS2::Width02, RS2::CenterLine));

   
   doc->setLayer("verdeckt");
   doc->activateLayer("verdeckt");   
   doc->setCurrentLayerPen(RS_Pen(RS_Color(0,0,0), RS2::Width02, RS2::DashLine));

   doc->activateLayer("0");
   doc->setCurrentLayerPen(RS_Pen(RS_Color(0,0,0), RS2::Width01, RS2::SolidLine));
   
   doc->setLayer("00");   
   doc->activateLayer("00");
   doc->setCurrentLayerPen(RS_Pen(RS_Color(255,255,255), RS2::Width08, RS2::SolidLine));
   
   /* ++++++++ */

   QStringList lali;
   
   lali = doc->getAllLayer();
   
   for (int i = 0; i < lali.size(); ++i)
     {
	RS_Pen   pen1;
   
	doc->activateLayer(lali[i]);
	
	pen1 = doc->getCurrentLayerPen();
	
       if(0)
	 {
	   std::cerr << "\n " << lali[i].toStdString() 
	     << " w " << pen1.getWidth()
	     << " t " << pen1.getLineType()
	     << " c " << pen1.getColor() <<  "\n";
	 }
     }
}

// -----------------------

QString LC_colored_layers::name() const
{
   return (tr("colored layers"));
}

PluginCapabilities LC_colored_layers::getCapabilities() const
{
   PluginCapabilities pluginCapabilities;
   pluginCapabilities.menuEntryPoints
     << PluginMenuLocation("CAM", tr("colored layers"));
   return pluginCapabilities;
}

Q_EXPORT_PLUGIN2(lc_colored_layers, LC_colored_layers);

