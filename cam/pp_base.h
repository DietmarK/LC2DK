#ifndef PP_BASE_H
#define PP_BASE_H

#include <QErrorMessage>
#include <QString>
#include <QList>

#include "data_dialog_drill.h"
#include "data_entity.h"

#include "filenames.h"


class PP_base  : public QObject  // QDialog
{
     Q_OBJECT
     
 public:
   QErrorMessage err;
   virtual void set_default_values() {};
   virtual void save_default_values() {};
   virtual void generate_nc_lines() {};
   
   static void read_entity_data_file();
   void write_nc_lines();
   
   //QString print_cam_line(EntityData el, int index);
   //QString show();

   Data_dialog_drill d; 

   
   static QString programmtyp;

   
 protected:
      
   static int listlength;
   
   static QList<EntityData> e;		       /* all entities */

   static int index;			       /* index in read_entity_data_file() */

   QString nc;    		       /* output for NC-controller */
   
 private:
     
   

   
     
};

     
#endif
