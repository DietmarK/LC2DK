/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#ifndef cam8_H
#define cam8_H

#include <QDialog>
#include <QTextEdit>

#include "qc_plugininterface.h"

#include "../../cam/data_entity.h"     /* class EntityData */

class Plug_Entity;

class LC_delete_empty_layers : public QObject, QC_PluginInterface
{
    Q_OBJECT
     Q_INTERFACES(QC_PluginInterface)

 public:
    virtual PluginCapabilities getCapabilities() const;
    virtual QString name() const;
    virtual void execComm(Document_Interface *doc,
                                       QWidget *parent, QString cmd);

};

#endif // cam8_H
