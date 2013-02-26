#ifndef PP_CONTOUR_H
#define PP_CONTOUR_H

#include "pp_base.h"
#include "data_dialog_contour.h"

/* class CircleData : public EntityData
{
 public:
};  */


class PP_contour : public PP_base
{
   //  Q_OBJECT
     
 public:
   
   void set_default_values();
   void save_default_values();
   
   void generate_nc_lines();
   
   void read_circles();
   
   Data_dialog_contour d; 

 private:

   QString rl_rr_r0 (int rk);
   
   QString dr_plumi (int cw);
   
   EntityData circle_1;
   
   EntityData circle_2;
   
   EntityData circle_x;
   
   int circles_count;
   
   int e_size;
   
   //QString programmtyp;
   
   //int listlength;
   
   //QList<EntityData> e;		       /* all entities */


   // int i;

   
     
};

     
#endif
