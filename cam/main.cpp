#include <iostream>

#include "includes.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   
   
   PP_base::read_entity_data_file();
   
   if(! PP_base::programmtyp.compare("bohren"))
     {
	
	PP_drill *b = new PP_drill;
	
	b->set_default_values();
	
	Dialog_drill dialog_window;
	
	dialog_window.setData(b->d);
	
	if(dialog_window.exec())
	  {
	     dialog_window.updateData();
	     
	     b->save_default_values();
	     
	     b->generate_nc_lines();
	     
	     b->write_nc_lines();
	     
	  }
	
     }				       /* "bohren" */
   
   else if (! PP_base::programmtyp.compare("contour"))
     {
	// std::cerr << "\n kontur ..... ? \n";
	
	PP_contour *b = new PP_contour;

	b->read_circles();
	
	b->set_default_values();
	
	Dialog_contour dialog_window;
	
	dialog_window.setData(b->d);
	
	if(dialog_window.exec())
	  {
	     dialog_window.updateData();
	     
	     b->save_default_values();
	     
	     b->generate_nc_lines();
	     
	     b->write_nc_lines();
	     
	  }
	
	
     }
   else
     std::cerr << "unknown programmtyp: " << PP_base::programmtyp.toStdString() << "\n";
   
}
