/*****************************************************************************/
/* update_dim_1 :  this plugin updates all dimensions to a small size        */ 
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


//#include <iostream>                    /* only for debug */

//#include "../../cam/filenames.h"

#include "document_interface.h"

//#include "rs_pen.h"

#include "update_dim_1.h"

void LC_update_dim_1::execComm(Document_Interface *doc,
		       QWidget *parent, QString cmd)
{
   Q_UNUSED(parent);
   Q_UNUSED(cmd);
   
   //int var;
       
   //doc->getVariableInt("$DIMTIH", &var);   
      
   doc->addVariable("$DIMTIH",  0, 70);
   
   doc->addVariable("$DIMTXT", 2.555, 40);     /* double  */
   
   doc->addVariable("$DIMEXE", 1.022, 40);     /* double  */
   
   doc->addVariable("$DIMEXO", 0.888, 40);     /* double  */
   
   doc->addVariable("$DIMGAP", 1.111, 40);     /* double  */
   
   doc->addVariable("$DIMASZ", 2.555, 40);     /* double  */
   
}

// -----------------------
// 
QString LC_update_dim_1::name() const
{
   return (tr("update dimensions 2.5"));
}

PluginCapabilities LC_update_dim_1::getCapabilities() const
{
   PluginCapabilities pluginCapabilities;
   pluginCapabilities.menuEntryPoints
     << PluginMenuLocation("CAM", tr("update dimensions 2.5"));
   return pluginCapabilities;
}

Q_EXPORT_PLUGIN2(lc_update_dim_1, LC_update_dim_1);
