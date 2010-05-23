/**
 * @file mkdir.c
 * @author  Patricia Minica, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * make directory passed as calling function argument
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * function executed to get and display the curent date and time
 * 
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 * 	
 * @return 0 on success or a positive int on failure
 */
int mkdir_default (int argcounter, char **argvector);

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
	 * @see run command to make the argv[1] file
	 * @see mkdir_default (argc, argv);
	 */
    if (argc == 2) {
        return mkdir_default (argc, argv);
    }

    return 0;
}

int mkdir_default (int argcounter, char **argvector)
{
	/**
	 * @see make directory or return 1 if failure
	 */
    if (mkdir (argvector[1], 0644) != 0) {
        fprintf(stderr, "Cannot create directory: \'%s\'. Please write full path\n", argvector[1]);
        return 1;
    }

    return 0;
}

