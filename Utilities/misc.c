/*
 * misc.c
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#include "misc.h"

// modulus calculation done for 2 given values
uint32 mod (sint32 a, sint32 b)
{
	sint32 ret = 0;
   if(a >= 0)
   {
	   ret =  a % b;
   }
   else
   {
	   ret = a;
	   while(ret < 0)
	        ret+=b;
   }

   return (uint32)ret;
}


