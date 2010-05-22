/**
* @cat.c
* @author Cornianu Bogdan-Iancu <cornianu.bogdan@gmail.com>
* @version 1.0.0.0
*
* @section DESCRIPTION
*
* Concatenate files to standard output
*
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	int i,ci;
	FILE *fp;//file pointer
        int j = 0;
        char c;
        int ln = 1,Av = 0, bv = 0, ev = 0, Ev = 0, nv = 0, sv = 0, tv = 0, Tv = 0, hv = 0, vv = 0;

/**
* Read options from the command line
*/
while ((ci = getopt (argc, argv, "AbeEnstThv:")) != -1)
         switch (ci)
           {
           case 'A':
             Av = 1;
             break;
           case 'b':
             bv = 1;
             break;
           case 'e':
             ev = 1;
             break;
	case 'E':
	/** Show $ at end of lines*/
             Ev = 1;
             break;
	case 'n':
	/** Number the lines*/
             nv = 1;
             break;
	case 's':
             sv = 1;
             break;
	case 't':
             tv = 1;
             break;
	case 'T':
	/** Show tabs*/
             Tv = 1;
             break;
	case 'h':
	/** Show help*/
             hv = 1;
             break;
	case 'v':
	/** Show version*/
             vv = 1;
             break;
	 default: printf("Unknown argument(s)!");
	}

	if (argc == 2)
        fp = fopen(argv[1], "r");
	else
	fp = fopen(argv[2], "r");
        if (fp == NULL)
        {
            fprintf(stderr, "File not found...Aborting\n");
            //exit;
        }

        while ((c = fgetc(fp)) != EOF)
        {
            fputc(c, stdout);
        
	
	//number the lines
	if (nv == 1)
	{
	if (c == '\n') 
            {
                printf("%2d", ln);
                ln++;
                putc(' ', stdout);
            }
	}

	
	//print version
	if (vv == 1)
	printf("cat - version 1.0 by Cornianu Bogdan");

	//print help
	if (hv == 1)
	{
	printf("Usage: cat [options] filename");
	printf("Options: -n Number all output lines");
	printf("Options: -T Display TAB characters as ^I");
	printf("Options: -E Display $ at end of each line");
	}

	
	//show tabs
	if (Tv == 1)
	{
	if (c == '\t')
	printf("^I");	
	}

	//display $ at end of each line
	if (Ev == 1)
	{
	if (c == '\n')
	printf("$");	
	}

	
}

        fclose(fp);
	
return 0;
}
