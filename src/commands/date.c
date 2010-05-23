/**
 * @file date.c
 * @author  Patricia Minica, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * displays the curent date and time
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

/**
 * function executed to get and display the curent date and time
 * 
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 * 	
 * @return 0
 */
int date_default (int argcounter, char **argvector);

/**
 * command main function
 * 
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 * 	
 * @return 0 on success or a positive int on failure
 */
int main(int argc, char **argv) {

    optind = 0;
    int o;

    while ((o = getopt(argc, argv, "hu")) != -1) {
        switch (o) {
            case 'h':
                printf("-h, display this help and exit\n");
                printf("-u, shows Author and Version info and exit\n");
                return 0;
            case 'u':
                printf("Author:\tMinica Patricia\n");
                printf("Version:\t1.0\n");
                return 0;
            default:
                return 2;
        }
    }

    /**
	 * @see run command to display date and time only if function is called with no args
	 * @see date_default (argc, argv);
	 */
    if (argc == 1) {
        return date_default (argc, argv);
    }

    return 0;
}

int date_default (int argcounter, char **argvector)
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer [80];

    time ( &rawtime );
    
    /**
     * @see get curent date and time in struct buffer
     */
    timeinfo = localtime ( &rawtime );

    /**
     * @see print current date and time in shell like format
     */
    strftime (buffer, 80, "%a %b %d %X %Z %Y", timeinfo);
    
    puts (buffer);

    return 0;
}
