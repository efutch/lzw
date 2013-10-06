/* expand.c - LZW expansion module for Portable Archiver */


#include <stdlib.h>     // Update to compile without warnings in Linux
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "lzw.h"

FILE *inputfd,*outputfd;

void lzw_expand(file)
char *file;
{
   int next_code;
   unsigned char code,last_code,last_char,old_last_char;
   unsigned char outstring();
   int not_code_in_table();
   extern void init_table(),addcode();
   extern int table_not_full;

	inputfd = fopen(file,"r");
	if (inputfd == NULL)
	{
		fprintf(stderr,"File %s caused an error\n",file);
		exit(2);
	}
	outputfd = fopen("unzip.out","w+");
	if (outputfd == NULL)
	{
		fprintf(stderr,"File unzip.out caused an error\n");
		exit(3);
	}
	init_table();
	next_code = 128;
	GETCHAR(code);
	PUTCHAR(code);
	last_code = code;
   while (GETCHAR(code))
   {
      if (not_code_in_table(code))
      {
         old_last_char = last_char;
         last_char = outstring(last_code);
         PUTCHAR(old_last_char);
      }
      else
      {
         last_char = outstring(code);
      }
      if (table_not_full)
      {
         addcode(last_char,last_code,next_code);
         next_code++;
         if (next_code > 255)
            table_not_full = 0;
      }
      last_code = code;
   }
   close(outputfd);
   close(inputfd);
}

unsigned char outstring(c)
unsigned char c;
{
   unsigned char tmpstr[80];
   extern struct lzw_table_entry lzw_table[256];
   static unsigned char tmpchar;
   int i;

   if (c < 128)
   {
      PUTCHAR(c);
      return(c);
   }
   for (i = 0 ; i < 80 ; tmpstr[i++] = '\0')
       ;
   while (c > 127)
   {
      tmpchar = lzw_table[c].character;
      strcat(tmpstr,&tmpchar);
      c = lzw_table[c].base_code;
   }
   tmpchar = c;
   strcat(tmpstr,&tmpchar);
   for (i = strlen(tmpstr)-1 ; i >= 0 ; i--)
       PUTCHAR(tmpstr[i]);
   return(tmpstr[strlen(tmpstr)-1]);
}
