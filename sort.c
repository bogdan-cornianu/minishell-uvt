/**
 * @file sort.c
 * @author  Oana Munteanu, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * sort columns in file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define M 50
#define datalen 20

struct x {
	char one[datalen];
	char two[datalen];
	char thr[datalen];
} data[M];

/**
 * function executed to sort the columns in the file
 * 
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 * 	
 * @return 0
 */
int sort_default (int argcounter, char **argvector);

/**
 * command main function
 * 
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 * 	
 * @return 0 on success or a positive int on failure
 */
int main(int argc, char **argv)
{
    optind = 0;
    int o;

    while ((o = getopt(argc, argv, "hu")) != -1)
    {
        switch (o)
        {
        case 'h':
            printf("-h, display this help and exit\n");
            printf("-u, shows Author and Version info and exit\n");
            return 0;
        case 'u':
            printf("Author:\tMunteanu Oana\n");
            printf("Version:\t1.0\n");
            return 0;
        default:
            return 2;
        }
    }

    /**
	 * @see run command if argv contains a filename
	 * @see sort_default (argc, argv);
	 */
    if (argc == 2)
    {
        return sort_default (argc, argv);
    }

    return 0;
}

int sort_default (int argcounter, char **argvector)
{
    FILE *inFile = fopen( argvector[1], "r" );

    if ( inFile == NULL )
    {
        fprintf( stderr, "Failed to open %s as input file", argvector[1] );
        return 1;
    }

    int n = 0, i = 0, j, c;
    char tempstr[100];
    char keyone[datalen];
    char keytwo[datalen];
    char keythr[datalen];

	while ((c = fgetc (inFile)) != EOF)
	{
		if (c == '\n')
		{
			sscanf (tempstr, "%s %s %s", data[n].one, data[n].two, data[n].thr);
			n++;
			i = 0;
		}
		else
		{
			tempstr[i++] = c;
		}
	}

	// sorting
    for (i = 2; i <= n-1; i++)
    {
        strcpy (keyone, data[i].one);
        strcpy (keytwo, data[i].two);
        strcpy (keythr, data[i].thr);
        
        j=i-1;
        
        while ((strcmp (keyone ,data[j].one) < 0) && (j >= 1))
        {
       		strcpy (data[j+1].one, data[j].one);
       		strcpy (data[j+1].two, data[j].two);
       		strcpy (data[j+1].thr, data[j].thr);
       		
            j=j-1;
        }
        
        strcpy (data[j+1].one, keyone);
        strcpy (data[j+1].two, keytwo);
        strcpy (data[j+1].thr, keythr);
    }
    // end sorting
    
    for (i=1;i<=n;i++)
    {
		printf ("%s\t", data[i].one);
		printf ("%s\t", data[i].two);
		printf ("%s\n", data[i].thr);
	}

    return 0;
}
