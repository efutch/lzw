/* table.c - table management module */

#include "lzw.h"

int table_not_full = 1;
struct lzw_table_entry lzw_table[256];

void init_table()
{
	int h;

	for (h = 0 ; h < 128 ; h++)
		lzw_table[h].base_code = lzw_table[h].character = (unsigned char)h;
   for (h = 128 ; h < 256 ; h++)
		lzw_table[h].base_code = lzw_table[h].character = '\0';
}

int lookup(ch,bcode,table_offset)
unsigned char ch,bcode;
int *table_offset;
{
	int h;

	for (h = 128 ; h < 256 ; h++)
	{
		if ((lzw_table[h].base_code == bcode) &&
		    (lzw_table[h].character == ch))
		{
			*table_offset = h;
			return(1);
		}
		else if (lzw_table[h].character == '\0')
		{
			*table_offset = h;
			return(0);
		}
	}
	table_not_full = 0;
	*table_offset = (int)ch;
	return(0);
}

void addcode(ch,bcode,table_offset)
unsigned char ch,bcode;
int table_offset;
{
	lzw_table[table_offset].base_code = bcode;
	lzw_table[table_offset].character = ch;
}

int not_code_in_table(c)
unsigned char c;
{
   if (lzw_table[c].character == '\0')
      return(1);
   else
       return(0);
}
