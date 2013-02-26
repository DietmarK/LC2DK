#include <math.h> 
#include <locale.h>
#include  <stdio.h>           /* sprintf */
#include <string.h>

char *my_sprintf (double d, int plus = 0)	       
{
   /* "sprintf" mit anpassungen an deutsche sprache: */
   /* tausender-separator entfernen, Komma als decimal-point, Nachnullen entfernen */
   /* wenn plus != 0 dann ohne '+'-vorzeichen */
   
   static char num[222];
   int i,k, len;
   
   
   setlocale(LC_ALL, "C");
   
   
   strcpy (num, "");
   
   if (plus)
     sprintf (num, "%.3f", d);
   else
     sprintf (num, "%+.3f", d);
   
   len = strlen (num);
   
   for (k=0; k<len; k++)
     {
	if (num[k] == ',')
	  { 
	     for (i=k; i<len; i++)
	       {
		  num[i] = num[i+1];
	       }
	     num[len] = '\0';
	  }
	else if (num[k] == '.')
	  num[k] = ',';
     }
   
   
   
   if (strchr(num, ','))
     {		     
	len = strlen (num);
	
	for (k=len-1; k>0; k--)
	  {
	     if ( num[k] == ',')
	       {
		  num[k] = '\0';
		  break;
	       }
	     else if (num[k] == '0')
	       num[k] = '\0';
	     else
	       break;	     
	  }
     }

   if(0 == strcmp(num, "-0"))	       /* avoid  "-0"  */
     {
	if(plus)
	  strcpy (num, "0");
	else
	  strcpy (num, "+0");
     }
   
   return num;
}

// ------------------------------------

int abs_diff (double a, double b)
{
   /* compare 2 doubles */
   
   double c;
   
   c = fabs ( a - b );
   
   if ( c > 0.0003 )     /*  max. diff */
     return 1;
   else
     return 0;   
}
