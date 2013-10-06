/* table.h - include file for LZW table definition */

struct lzw_table_entry
{
	unsigned char base_code;
	unsigned char character;
};

/* #define GETCHAR(x) read(inputfd,&(x),sizeof(unsigned char)) */
#define GETCHAR(x) fread(&(x),sizeof(unsigned char),1,inputfd)

/* #define PUTCHAR(x) write(outputfd,&(x),sizeof(unsigned char)) */
#define PUTCHAR(x) fwrite(&(x),sizeof(unsigned char),1,outputfd)