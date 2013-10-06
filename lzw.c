/* par.c - LZW compression for text files, using 8-bit codes */
/* 	sccs id : @(#) par.c - LZW text file compression     */
/* Written by Egdares Futch H.                               */
/* Based on the BYTE magazine article : Lossless Data Compression */

#include <stdlib.h>           // Update to compile without warnings in Linux
#include <stdio.h>
#include <string.h>

void main(argc,argv)
int argc;
char *argv[];
{

   extern int lzw_compress();
   extern void lzw_expand();
   void usage();

	if ((argc == 1) || !(strcmp("-h",argv[1])))
		usage();
	if (argc > 2)
	{
		int tmp = 2;

		while (tmp < argc)	
		{
			if (!strcmp("-c",argv[1]))
			{
				printf("Compressing %s ... ",argv[tmp]);	
				printf("(%d%%) done\n",lzw_compress(argv[tmp]));
			}
			else if (!strcmp("-x",argv[1]))
				{
					printf("Expanding %s ... ",argv[tmp]);
					lzw_expand(argv[tmp]);
					printf("done\n");
				}
			else usage();
			++tmp;
		}
	}
	else usage();
}

void usage()
{
	puts("lzw - LZW compression for text files ONLY\n\
	usage : lzw (-h | -c | -x) file1 [file2 file3 ...]\n\
	where : 	-h	prints this message\n\
			-c	compresses the file(s)\n\
			-x	extracts the file(s)");
	exit(1);
}
