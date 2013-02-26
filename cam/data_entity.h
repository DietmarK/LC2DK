#ifndef DATA_ENTITY_H
#define DATA_ENTITY_H

class EntityData
{
 public:
   int typ;      /* 1=line, 3=circle, 4=arc  same as enum ETYPE */
   int cw;			       /* clockwise or not */
   
   double x1;
   double y1; 			       /* first endpoint */
   
   double x2;
   double y2;			       /* second endpoint */
   
   double len;
   double wi;			       /* ? */
   
   double r;			       /* radius */
   
   double w1; 
   double w2; 			       /* angles (typ 4) */
   
   double ccx; 
   double ccy;			       /* center (typ 3 or 4) */

   // ----------------------------
   // 
   void clear()
     {
	typ = cw = 0;
	x1=y1=x2=y2=len=wi=r=w1=w2=ccx=ccy=0;
     };
   
};



#endif
