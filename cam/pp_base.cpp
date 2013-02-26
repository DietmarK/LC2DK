#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>

#include "pp_base.h"


// declare static members 
QString  PP_base::programmtyp;
int PP_base::listlength;
int PP_base::index;
QList<EntityData> PP_base::e;


// ---------------------------------
 

void PP_base::write_nc_lines()
  
{
   
   // write to file:
   
   QString filename(nc_machine_code_file);  
   QFile o_file(filename);
   
   if (! o_file.open(QIODevice::WriteOnly))
     {
	//QErrorMessage err;
	std::cerr << "\n err bei o_file.open \n";
	// exit (1);
     }
   else
     {
	QTextStream txt(&o_file);
	
	txt << nc.mid(1) << "\n";
     }
   o_file.close ();
   
   // ----------------------------
   // show in a window:
	
   QMessageBox dlg;  /* window for output */

    dlg.resize ( 600, 1000 );	       /* ???????? */
   
   QFont f("courier", 12);
   
   dlg.setFont(f);
   
   
   dlg.setText(nc);
   dlg.exec();
   
}

// ------------------------------------

void PP_base::read_entity_data_file()
{
   QString filename(cad_to_cam_exch_file); 
   QFile ifile(filename);
   
   if (! ifile.open(QIODevice::ReadOnly))
     {
	std::cerr << "\n err bei open entity_data_file \n";
	//err.showMessage("\n err bei ifile.open ");
	exit (1);
     }
   else
     {
	QTextStream t(&ifile);
	EntityData el;		       /* empty */
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
	     
	     // if (value.isEmpty())
	     // break;
	     
	     
	     
	     //	     QLocale::setDefault(QLocale::C);
	     
	     if (!key.compare("programmtyp"))
	       programmtyp = value;
	     
	     else if (!key.compare("listlength"))
	       listlength = value.toInt();
	     
	     else if (!key.compare("index"))
	       {
		  index = value.toInt();
		  e.insert(index, el);
	       }
	     
	     else if (!key.compare("typ"))
	       e[index].typ = value.toInt();
	     
	     else if (!key.compare("cw"))
	       e[index].cw = value.toInt();
	     
	     else if (!key.compare("x1"))
	       e[index].x1 = value.toDouble();
	     
	     else if (!key.compare("y1"))
	       e[index].y1 = value.toDouble();
	     
	     else if (!key.compare("x2"))
	       e[index].x2 = value.toDouble();
	     
	     else if (!key.compare("y2"))
	       e[index].y2 = value.toDouble();
	     
	     else if (!key.compare("len"))
	       e[index].len = value.toDouble();
	     
	     else if (!key.compare("wi"))
	       e[index].wi = value.toDouble();
	     
	     else if (!key.compare("r"))
	       e[index].r = value.toDouble();
	     
	     else if (!key.compare("w1"))
	       e[index].w1 = value.toDouble();
	     
	     else if (!key.compare("w2"))
	       e[index].w2 = value.toDouble();
	     
	     else if (!key.compare("ccx"))
	       e[index].ccx = value.toDouble();
	     
	     else if (!key.compare("ccy"))
	       e[index].ccy = value.toDouble();
	     
	     else
	       continue; 
	  }
	while (true);
     }
}

