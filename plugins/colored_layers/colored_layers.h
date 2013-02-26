
#ifndef cam6_H
#define cam6_H

#include <QDialog>
#include <QTextEdit>

#include "qc_plugininterface.h"

#include "../../cam/data_entity.h"     /* class EntityData */

class Plug_Entity;

class LC_colored_layers : public QObject, QC_PluginInterface
{
    Q_OBJECT
     Q_INTERFACES(QC_PluginInterface)

 public:
    virtual PluginCapabilities getCapabilities() const;
    virtual QString name() const;
    virtual void execComm(Document_Interface *doc,
                                       QWidget *parent, QString cmd);

};

#endif // cam6_H
