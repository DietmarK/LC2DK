#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <math.h>		       /* fabs */

#include "../librecad/src/plugins/document_interface.h"   /* DPI */

#include "pp_contour.h"

#include "functions.h"

#include <iostream>                    /* only for debug */

void PP_contour::set_default_values()
{
   QString filename(dialog_contour_values_file); 
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
	     
	     if (!key.compare("secure1"))
	       d.secure1 = value;
	     
	     else if (!key.compare("z_begin"))
	       d.z_begin = value;
	     
	     else if (!key.compare("z_end"))
	       d.z_end = value;
	     
	     else if (!key.compare("num_steps"))
	       d.num_steps = value;
	     
	     else if (!key.compare("feed"))
	       d.feed = value;
	     
	     else if (!key.compare("b_e_exch"))
	       d.b_e_exch = value.toInt();
	     
	     else if (!key.compare("rl_rr"))
	       d.rl_rr = value.toInt();
	     
	     else if (!key.compare("lblnum"))
	       d.lblnum = value;
	     
	     else if (!key.compare("lblkom"))
	       d.lblkom = value;
	     
	  } while (1);
	
     }   
   d_file.close ();
}

// ------------------------------
// 
void PP_contour::save_default_values()
{
   QString filename(dialog_contour_values_file); 
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
	
	t << "secure1" << "\n" << d.secure1 << "\n";
	t << "z_begin" << "\n" << d.z_begin << "\n";
	t << "z_end" << "\n" << d.z_end << "\n";
	t << "num_steps" << "\n" << d.num_steps << "\n";
	t << "feed" << "\n" << d.feed << "\n";
	t << "lblnum" << "\n" << d.lblnum << "\n";
	t << "lblkom" << "\n" << d.lblkom << "\n";
	
	if(d.b_e_exch)		                   /* bool or int ??? */
	  t << "b_e_exch" << "\n" << 1  << "\n";
	else
	  t << "b_e_exch" << "\n" << 0  << "\n";
	
	t << "rl_rr" << "\n" <<  d.rl_rr << "\n";
	
     }
   d_file.close ();
}

// --------------------------
// 
// 
void PP_contour::read_circles()
{
   e_size = e.size();
   circles_count = 0;
   
   //  ----> cam4
   if (e_size < 1)
     {
	QMessageBox msgBox1;
	msgBox1.setText("You have to select lines or arcs");
	msgBox1.setIcon(QMessageBox::Warning);
	msgBox1.exec();
	exit (-1);	
     }
   
   
   EntityData el;
   int k;
   
   
   //   std::cerr << " e_size: " << e_size << "\n";
   
   
   for (k = 0; k < e_size; ++k) 
     {        
        el = e[k];
	if (el.typ == DPI::CIRCLE)
	  {	  
	     if (circles_count == 0)
	       {
		  circle_1 = el;
		  circles_count++;
	       }	     
	     else if (circles_count == 1)
	       {
		  circle_2 = el;
		  circles_count++;
	       }	  
	     else
	       { 
		  char *msg;
		  asprintf(&msg, "found more than 2 circles: discarding x=%.3f y=%.3f",el.x1,el.y1);
		  QMessageBox msgBox;
		  msgBox.setText(msg);
		  msgBox.setIcon(QMessageBox::Warning);
		  msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
		  msgBox.setDefaultButton(QMessageBox::Cancel);
		  int ret = msgBox.exec();
		  if (ret == QMessageBox::Cancel)
		    exit (-1) ;
		  
		  //std::cerr << " else: " << msg << "\n";
		  
	       }	     
	     
	     //std::cerr << " circles_count: " << circles_count << "\n";
	  }
	
     } 
   
}

 // --------------------------

QString PP_contour::rl_rr_r0 (int rk)
{
   QString ret("r0");
   if (rk == 1)
     ret = "rl";
   else if (rk == 2)
     ret = "rr";
   return ret;
}

 // --------------------------

QString PP_contour::dr_plumi (int cw)
{
   QString ret("dr+");
   if (cw)
     ret = "dr-";
   return ret;
}

 // --------------------------

/* like a postprocessor */
/* you have to adapt to other NC-controllers */

void PP_contour::generate_nc_lines()
{
   EntityData el;
   int k;
   e_size = e.size();
   int max_idx = listlength - 1 - circles_count;
   
   if (circles_count)
     {
	
	double xa, ya, xe, ye, x1, y1, x2, y2, a1, a2, e1;
	
	xa = e[0].x1;
	ya = e[0].y1;
	
	xe = e[max_idx].x2;
	ye = e[max_idx].y2;
	  
	x1 = circle_1.ccx;
	y1 = circle_1.ccy;
	
	a1 = (x1-xa)*(x1-xa) + (y1-ya)*(y1-ya);   /* x^2 + y^2 */
	
	if (1)     // compute distanz to first point
	  {   
	     x2 = circle_2.ccx;
	     y2 = circle_2.ccy;
	     
	     a2 = (x2-xa)*(x2-xa) + (y2-ya)*(y2-ya);
	     
	     // exchange circle_1 with circle_2 ?
	     
	     if ((a2 < a1 && ! d.b_e_exch) || (a2 > a1 && d.b_e_exch))  
	       {		  
		  circle_x = circle_2;
		  circle_2 = circle_1;
		  circle_1 = circle_x;
	       }
		
	     else if (circles_count == 1)	   // compare distanz to first and last point
	       {
		  e1 = (x1-xe)*(x1-xe) + (y1-ye)*(y1-ye);   /* x^2 + y^2 */
		  
		  double toleranz = 1.8;  // ??
		  
		  std::cerr << "a/e = " << a1 / e1 << "   e/a = " << e1/a1 << std::endl;
		  
		  if(a1 == e1 || (a1 < e1 && a1 * toleranz > e1) || (a1 > e1 && e1 * toleranz > a1))
		    {
		       circle_2 = circle_1;    // use the same circle
		       circles_count++;
		    }
	       }
	  }
     }
   

   // std::cerr << "circle 1  x = " << circle_1.x1 << "   y = " << circle_1.y1 << std::endl;
   // std::cerr << "circle 2  x = " << circle_2.x1 << "   y = " << circle_2.y1 << std::endl;
   
   
   
   // --------------
   
   
   
   double z_begin = 0;
   
   if (d.z_begin.size())
     z_begin = d.z_begin.toDouble();
   
   double z_end = 1;
   
   if (d.z_end.size())
     z_end = d.z_end.toDouble();
   
   int num_steps = 1;
   
   if (d.num_steps.size())
     num_steps = d.num_steps.toInt();
   
   double iz = 1;
   
   //if (d.z_end.size() && d.z_begin.size() && num_steps > 1)
   iz = (z_end - z_begin) / num_steps;
   
   double q1 = z_begin;
   
   //if (iz < 0)
   q1 += iz;		// first plunging depth (and last, if num_steps == 1)
   
   
   // --------------------

   // if (num_steps > 1) 
   //     nc.append(QString("\n; (begin z%1 end z%2 iz%3)").arg(my_sprintf(z_begin)).arg(my_sprintf(z_end)).arg(my_sprintf(iz))); 

   if (d.feed.size())
     nc.append(QString("\nq2 = %1 ; F ").arg(d.feed));
   
   nc.append(QString("\nq1 = %1 ; Z ").arg(my_sprintf(q1))); 
   
   nc.append(QString("\nlbl %1 ; %2 ").arg(d.lblnum).arg(d.lblkom));
   
   double x0 = 99999;   // save starting position
   double y0 = 99999;
   
   if (circle_1.typ == DPI::CIRCLE)  // goto starting position
     {
	nc.append(QString("\nl x%1 y%2 z%3 r0 f max m13").arg(my_sprintf(circle_1.ccx)).arg(my_sprintf(circle_1.ccy)).arg(d.secure1));
	nc.append(QString("\nl z+2 f max  "));
	nc.append(QString("\nl z+q1 f2222 ")); 
	
	x0 = circle_1.x1;
	y0 = circle_1.y1;
     }
   else
     nc.append(QString("\n\n error: no circle nr.1 found ! \n"));
   
   // -----------------------
   
   for (k = 0; k < e_size; ++k) 
     {        
	el = e[k];
	switch (el.typ) 
	  {	
	   case DPI::LINE:
	     
	     if (k == 0)      // first element of contour:
	       {	
		  if (abs_diff(x0,el.x1) || abs_diff(y0,el.y1))    // begin with x1 y1
		    {
		       nc.append(QString("\nl x%1 y%2").arg(my_sprintf(el.x1)).arg(my_sprintf(el.y1)));
		       
		       nc.append(QString(" %1 fq2 m8 ").arg(rl_rr_r0(d.rl_rr)));
		       
		       nc.append(QString("\nl x%1 y%2").arg(my_sprintf(el.x2)).arg(my_sprintf(el.y2)));
		       
		       // nc.append( QString ( " ; (%1) ").arg(my_sprintf(k,1)));
		       
		    }
		  else  // begin with x2 y2
		     {
			if (d.rl_rr != 0)
			  nc.append("\n\nError: RL/RR and circle at first point \n");
		  
			nc.append(QString("\nl x%1 y%2").arg(my_sprintf(el.x2)).arg(my_sprintf(el.y2)));
		        
			nc.append(QString(" %1 fq2 m8 ").arg(rl_rr_r0(d.rl_rr)));
			
			// nc.append( QString ( " ; (%1) ").arg(my_sprintf(k,1))); 
		     }		  
	       }	       
	  
	     else   // other elements
	       {
		  nc.append(QString("\nl x%1 y%2 ").arg(my_sprintf(el.x2)).arg(my_sprintf(el.y2)));

		  // nc.append( QString (" ; (%1) ").arg(my_sprintf(k,1)));
	       }
	     
	     break;	
	   case DPI::ARC:
	     
	     nc.append(QString("\ncc x%1 y%2 ; r=%3 ").arg(my_sprintf(el.ccx))
		       .arg(my_sprintf(el.ccy)).arg(my_sprintf(el.r,1)));

	     if (k == 0)      // first element of contour:
	       {	
		  if (abs_diff(x0,el.x1) || abs_diff(x0,el.x1))    // begin with x1 y1
		    {
		       nc.append(QString("\nlp pr%1 pa%2").arg(my_sprintf(el.r)).arg(my_sprintf(el.w1)));
		       
		       nc.append(QString(" %1 fq2 m8 ").arg(rl_rr_r0(d.rl_rr)));

		       nc.append(QString("\ncp pa%1 %2 ").arg(my_sprintf(el.w2)).arg(dr_plumi(el.cw)));

		       // nc.append( QString ( " ; (%1) ").arg(my_sprintf(k,1))); 
		    }
		  
		  else  // begin with x2 y2
		    {
		       nc.append(QString("\ncp pa%1 %2 ").arg(my_sprintf(el.w2)).arg(dr_plumi(el.cw)));
		                              
		       // nc.append( QString ( " ; (%1) ").arg(my_sprintf(k,1)));
		    }
		  
	       }
	     else  // other elements
	       {
		  nc.append(QString("\ncp pa%1 %2 ").arg(my_sprintf(el.w2)).arg(dr_plumi(el.cw)));
		  
		  // nc.append( QString ( " ; (%1) ").arg(my_sprintf(k,1)));
		  
	       }
	     break;
	     
	   default:
	     break;
	  }
     }  //    for (k = 0; k < e_size; ++k)
   
   
   
   /* after last element: */
   if(e_size)	 
     {
	nc.append( QString ( "\nm9 "));

	if (circle_2.typ == DPI::CIRCLE)
	  nc.append(QString("\nl x%1 y%2 r0 ").arg(my_sprintf(circle_2.ccx)).arg(my_sprintf(circle_2.ccy)));
	else
	  nc.append(QString("\n\n error: missing second circle ! \n")); 
	  
	
	nc.append(QString("\nl z+%1 f max ").arg(d.secure1));	
	nc.append( QString ( "\nlbl 0 "));
	
	if (num_steps > 1)
	  {
	     nc.append(QString("\n; .. "));
	     
	     for (int j = 1; j < num_steps; j++)
	       {		  
		  q1 += iz;		// new depth
		  
		  nc.append(QString("\nq1 = %1 ; z ").arg(my_sprintf(q1)));
		  
		  nc.append(QString("\ncall lbl %1 ").arg(d.lblnum));
	     
	       }
	  }
	nc.append(QString("\n; * "));
     }
   else  // empty list
     nc.append(QString("\n you have to select circles or arcs > 266 degree !"));
   
   nc.append(QString("\n"));
}

   
