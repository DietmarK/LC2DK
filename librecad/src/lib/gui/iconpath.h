
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ohne inhalt, nur kommentar


#ifndef ICONPATH_H
#define ICONPATH_H

#include <QFile>

#include "rs_settings.h"

// in all files $(grep -r '":/extui/' src/) :
// replace all QIcon(":iconname")  with QIcon(getIconPath("iconname"))  !
// filter:
// sed 's#^\(.*setIcon(QIcon(\)\(.*:/extui/\)\(.*png\)\(.*\)$#\1getIconPath("\3")));#g'


// filter for intermediate/ui/ui_qg_...... :
// 
//  grep -r '":/extui/' intermediate/     ( grep -r 'addFile(QString::fromUtf8(":/extui/' intermediate/)
// 
// sed 's#^\(.*addFile(\)\(QString.*:/extui/\)\(.*png\)\(.)\)\(.*\)$#\1getIconPath("\3")\5#g'

//  in main.cpp  einbauen ?
  
//  ueberall wo (grep -r '":/extui/')  deklarieren:  QString getIconPath(QString);

/* 
QString getIconPath(QString base)
{
   
      QString path;
      
      RS_SETTINGS->beginGroup("/Paths");
   
   // it's for linux, replace it for other OS'es 
   // 
      path = RS_SETTINGS->readEntry("/Iconpath", "/usr/share/LibreCAD/icons");
      
   RS_SETTINGS->endGroup();
      
      
      if(!path.endsWith('/'))
          path.append('/');
      
      path.append(base);
      
      QFile f(path);
      
   if (!f.open(QIODevice::ReadOnly))
     {
	
	std::cerr << "could not load icon: file " << path.toStdString() << " is not readable! \n";
	        return NULL;
     }
      else
             f.close();
      
      return path;
}

*/

#endif
