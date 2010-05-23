/**
 * @file echo.c
 * @author  Oana Munteanu, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * change the mode of a file / directory
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

/**
 * function executed to echo the command
 * 
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 * 	
 * @return 0
 */
int echo_default (int argcounter, char **argvector);

/**
 * command main function
 * 
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 * 	
 * @return 0 on success or a positive int on failure
 */
int main (int argc, char **argv) {

    optind = 0;
    int o;

    while ((o = getopt (argc, argv, "hu")) != -1) {
        switch (o) {
            case 'h':
                printf ("-h, display this help and exit\n");
                printf ("-u, shows Author and Version info and exit\n");
                return 0;
            case 'u':
                printf ("Author:\tMunteanu Oana\n");
                printf ("Version:\t1.0\n");
                return 0;
            default:
                return 2;
        }
    }

    /**
	 * @see run command if argc is bigger than 1
	 * @see echo_default (argc, argv);
	 */
    if (argc > 1) {
        return echo_default (argc, argv);
    }

    printf ("\n");

    return 0;
}

int echo_default (int argcounter, char **argvector)
{
    int temp = 1;

    while (temp < argcounter)
    {
        printf ("%s ", argvector[temp]);
        temp++;
    }

    printf ("\n");
    return 0;
}
