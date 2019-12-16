/*
 * This module contains usefull helper and
 * Wapper functions for things like opening
 * files and dynamic memory allocation.
 *
 * MIT License
 * Copyright (c) 2017 ElliePenguins 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "format.h"

void * mallocWrap( int numberOfBytes)
{
   void * ptr = NULL;
   if( (ptr = malloc(numberOfBytes)) == NULL )
   {
      fprintf(stderr, "Memory allocation error, closing");
      exit(1);
   }

   // Return null on fail. (redunancy???);
   return ptr;
}

// Don't forget to free() the ptr!
char * mallocString(const char * string)
{
   // TODO: What if the string is empty?
   int stringLength = 0;
   char * ptr = NULL;

   if ( (stringLength = strlen(string)) == 0 )
   {
      ; // ptr already NULL, just return.
   }
   else
   {
      if ( (ptr = malloc((sizeof(char)*stringLength))) == NULL)
      {
	 fprintf(stderr, "Memmory allocation error, closing");
	 exit(1);
      }
   }
   
   return ptr;
}


char * newlineStrip(char * str)
{
   if ( str[strlen(str)-1] == '\n')
      str[strlen(str)-1] = (char) 0x00;
   
   return str;

}

FILE * openFile( char * filename, char * options)
{
   // Code for file access goes here.
}

