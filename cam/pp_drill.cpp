#include <QFile>
#include <QTextStream>
#include "../librecad/src/plugins/document_interface.h"   /* DPI */
#include <math.h>		       /* fabs */


#include "pp_drill.h"

#include "functions.h"

void PP_drill::set_default_values()
{
   QString filename(dialog_drill_values_file);
   QFile d_file(filename);
   //QErrorMessage err;
   
   if (! d_file.open(QIODevice::ReadOnly))
     {
	//	err.showMessage("\n if bei d_file.open read ");
	//	exit (1);
     }
   else
     {
	//	err.showMessage("\n else bei d_file.open  read ");
	
	QTextStream t(&d_file);
	QString key, value;
	
	do 
	  {
	     if(t.atEnd())
	       break;
	     
	     key = t.readLine().toLatin1();
	     
	     // if(key.isEmpty())
	     //   break;
	      
	     if(t.atEnd())
	       break;
	     
	     value = t.readLine().toLatin1();
	     
	     if (!key.compare("lblnum"))
	       d.lblnum = value;
	     
	     else if (!key.compare("secure1"))
	       d.secure1 = value;
	     
	     else if (!key.compare("depth1"))
	       d.depth1 = value;
	     
	     else if (!key.compare("secure2"))
	       d.secure2 = value;
	     
	     else if (!key.compare("q216q217"))
	       d.q216q217 = value.toInt();
	     
	  } while (1);
	
     }   
   d_file.close ();
}

// ------------------------------
// 
void PP_drill::save_default_values()
{
   QString filename(dialog_drill_values_file); 
   QFile d_file(filename);
   
   if (! d_file.open(QIODevice::WriteOnly))
     {
	//QErrorMessage err;
	err.showMessage("\n err bei d_file.open write ");
	exit (1);
     }
   else
     {
	QTextStream t(&d_file);
	
	t << "lblnum" << "\n" << d.lblnum << "\n";
	t << "secure1" << "\n" << d.secure1 << "\n";
	t << "depth1" << "\n" << d.depth1 << "\n";
	t << "secure2" << "\n" << d.secure2 << "\n";
	if(d.q216q217)
	  t << "q216q217" << "\n" << 1  << "\n";
	else
	  t << "q216q217" << "\n" << 0  << "\n";
     }
   d_file.close ();
}

// --------------------------
 

/* like a postprocessor */
/* you have to adapt to other NC-controllers */

void PP_drill::generate_nc_lines()
{
   // QString nc;
   EntityData el;
   int k;
   int e_size = e.size();
   int max_idx = listlength - 1;
   int secure2_after_last_bo = 1;
   
   QString secure_end = d.secure1;
   
   if(0 < d.secure2.size() )
     {
	if (d.secure2.toDouble() > d.secure1.toDouble())
	  {
	     secure_end = d.secure2;
	     secure2_after_last_bo = 0;	
	  }
     }
   
   
   for (k = 0; k < e_size; ++k) 
     {        
	el = e[k];
	switch (el.typ) 
	  {	
	   case DPI::CIRCLE:
	   case DPI::ARC:
	     
	     //      case 4:
	     //      case 5:
	
	     if (k == 0)                        /* first element */
	       {	
		  if(0 < d.depth1.size())
		    nc.append(QString("\nq11 = %1 ; freitiefe ").arg(d.depth1)); 
		  
		  if(0 < d.lblnum.size())
		    nc.append(QString("\nlbl ") + d.lblnum);
		  
		  if(d.q216q217)
		    {
		       nc.append(QString("\nQ216 = %1 ; x").arg(my_sprintf(el.ccx,1))); 
		       nc.append(QString("\nQ217 = %1 ; y").arg(my_sprintf(el.ccy,1))); 
		       nc.append(QString("\nl x+q216 y+q217 z+%1 r0 f max m13").arg(d.secure1));
		    }
		  else
		    nc.append(QString("\nl x%1 y%2 z+%3 r0 f max m13")
			       .arg(my_sprintf(el.ccx)).arg(my_sprintf(el.ccy)).arg(d.secure1));
		  
		  nc.append( QString ( "\nl z+2 f max "));
		  
		  if(0 < d.depth1.size())
		    nc.append(QString("\nl iz+q11 f2222 "));
		  
		  nc.append(QString("\nm8 \nm99 "));
		  
                  if (k < max_idx)
		    {
		       if(0 < d.secure2.size())
			 nc.append(QString("\nl z+%1 f max ").arg(d.secure2));
		       else if(0 < d.depth1.size())
			 nc.append(QString("\nl z+2 f max "));
		    }		  
		  else
		    nc.append(QString("\nm9 "));
		  
	       }
	     else			       /* any other elements */
	       {
		  if(d.q216q217 or 0 < d.secure2.size() or 0 < d.depth1.size())
		    nc.append(QString("\n; . "));
		  
		  if(d.q216q217)
		    {
		       nc.append(QString("\nQ216 = %1 ; x").arg(my_sprintf(el.ccx,1))); 
		       nc.append(QString("\nQ217 = %1 ; y").arg(my_sprintf(el.ccy,1))); 
		       nc.append(QString("\nl x+q216 y+q217 f max "));
		    }
		  else
		    nc.append(QString("\nl x%1 y%2 f max ")
			       .arg(my_sprintf(el.ccx)).arg(my_sprintf(el.ccy)));
		  
		  if(0 < d.secure2.size())
		    nc.append(QString("\nl z+2 f max "));	     
		  
		  if(0 < d.depth1.size())
		    nc.append(QString("\nl iz+q11 f2222 "));
		  
		  nc.append(QString("m99 "));

		  if (k < max_idx)
		    {		       
		       if(0 < d.secure2.size())
			 nc.append(QString("\nl z+%1 f max ").arg(d.secure2));
		       else if(0 < d.depth1.size())
			 nc.append(QString("\nl z+2 f max "));
		    }
		  else
		    nc.append(QString("\nm9 "));
	       }
	     
	     break;	
	     
	   default:
	     break;

	  }  // switch (el.typ)
	
     }  // for (k = 0; k < e_size; ++k)

   /* after last element: */
   if(e_size)	 
     {
	// nc.append( QString ( "\nm9 "));
	nc.append(QString("\nl z+%1 f max ").arg(secure_end));	
	nc.append( QString ( "\nlbl 0 "));
     }
   else  // empty list
     nc.append(QString("\n you have to select circles or arcs > 266 degree !"));
   
   nc.append(QString("\n"));
}
