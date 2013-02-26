/*****************************************************************************/
/* re_run_postpro :  this plugin only restarts the postprocessor,            */ 
/*             with the stored informations from last "bores" or "contour"   */
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
	  
#include "re_run_postpro.h"


void LC_re_run_postpro::execComm(Document_Interface *doc,
		       QWidget *parent, QString cmd)
{
   Q_UNUSED(parent);
   Q_UNUSED(cmd);
   Q_UNUSED(doc);
   

      // start the "postprocessor":
   
   int ret = system(cam_exec_file);
   
   if(0)
     std::cerr << "\n cam returned: " << ret << "\n";

}

// -----------------------

QString LC_re_run_postpro::name() const
{
   return (tr("re-run postprocessor"));
}

PluginCapabilities LC_re_run_postpro::getCapabilities() const
{
   PluginCapabilities pluginCapabilities;
   pluginCapabilities.menuEntryPoints
     << PluginMenuLocation("CAM", tr("re-run postpro."));
   return pluginCapabilities;
}

Q_EXPORT_PLUGIN2(lc_re_run_postpro, LC_re_run_postpro);
