/*****************************************************************************/
/* delete_empty_layers :  this plugin deletes empty layers                   */ 
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

#include "delete_empty_layers.h"

// #include <QtGui/QApplication>
 
void LC_delete_empty_layers::execComm(Document_Interface *doc,
		       QWidget *parent, QString cmd)
{
   Q_UNUSED(parent);
   Q_UNUSED(cmd);
   
   QList<Plug_Entity *> obj;

   bool yes  = doc->getAllEntities(&obj);   
   /* see plugins/document_interface.h main/doc_plugin_interface.h / .cpp */

   if (!yes || obj.isEmpty()) return;

   QStringList layers = doc->getAllLayer();
   
   QHash<QString, int> layer_el;
   
    for (int i = 0; i < layers.size(); ++i)
     {
	layer_el[layers[i]] = 0;
	
     }
   
     
   
   for (int i = 0; i < obj.size(); ++i) 
     {
	//   QString strdata = getStrData(obj.at(i));
 
	QHash<int, QVariant> data;
	
	//common entity data
	if (obj.at(i) == 0)
	  return;
	
	obj.at(i)->getData(&data);
	
	QString lay = (data.take(DPI::LAYER)).toString();
	
	layer_el[lay] +=1;
	
     }
   
    for (int i = 0; i < layers.size(); ++i)
     {
       // std::cerr << layers[i].toStdString() << " = " <<  layer_el[layers[i]] << "\n";
	
	if(0 == layer_el[layers[i]])
	  doc->deleteLayer(layers[i]);
	
     }
   
   /* ++++++++++ probieren ++++++++ */
   
   int var;
   
       
   doc->getVariableInt("$DIMTIH", &var);   
      
    // std:: cerr << "\n alignment: " << var << " \n";
   
   doc->addVariable("$DIMTIH",  0, 70);
   
   // dimension line gap usw., should be extra plugin ? :

   doc->addVariable("$DIMTXT", 2.555, 40);     /* double  */
   
   doc->addVariable("$DIMEXE", 1.022, 40);     /* double  */
   
   doc->addVariable("$DIMEXO", 0.888, 40);     /* double  */
   
   doc->addVariable("$DIMGAP", 1.111, 40);     /* double  */
   
   doc->addVariable("$DIMASZ", 2.555, 40);     /* double  */
   
   
   
}

// -----------------------
// 
QString LC_delete_empty_layers::name() const
{
   return (tr("delete empty layers"));
}

PluginCapabilities LC_delete_empty_layers::getCapabilities() const
{
   PluginCapabilities pluginCapabilities;
   pluginCapabilities.menuEntryPoints
     << PluginMenuLocation("CAM", tr("delete empty layers"));
   return pluginCapabilities;
}

Q_EXPORT_PLUGIN2(lc_delete_empty_layers, LC_delete_empty_layers);
