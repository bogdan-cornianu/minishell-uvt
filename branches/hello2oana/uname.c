/**
 * @file uname.c
 * @author  Oana Munteanu, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * display uname
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/utsname.h>

/**
 * function executed to get the current name
 * 	
 * @return 0
 */
int uname_default ();

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
	 * @see run command if no arguments specified
	 * @see uname_default ();
	 */
    if (argc == 1) {
        return uname_default ();
    }

    printf ("\n");

    return 0;
}

int uname_default ()
{
    struct utsname name;
    
    if (uname (&name) != -1)
    {
        printf ("%s\n", name.sysname);
    }

    return 0;
}
