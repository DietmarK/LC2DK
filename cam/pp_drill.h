#ifndef PP_DRILL_H
#define PP_DRILL_H

#include "pp_base.h"
#include "data_dialog_drill.h"

class PP_drill : public PP_base
{
   //  Q_OBJECT
     
 public:
   
   void set_default_values();
   void save_default_values();
   
   void generate_nc_lines();
   
   
   Data_dialog_drill d; 

// private:
     
   
   //QString programmtyp;
   
   //int listlength;
   
   //QList<EntityData> e;		       /* all entities */


   // int i;

   
     
};

     
#endif
