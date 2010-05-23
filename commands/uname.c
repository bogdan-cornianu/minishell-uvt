/*
 * uname command
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/utsname.h>

int uname_default ();

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

    // run if argc contains arguments
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
