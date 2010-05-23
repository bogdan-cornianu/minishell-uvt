/**
 * @file sleep.c
 * @author  Patricia Minica, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * make directory passed as calling function argument
 */

 /**
 * function executed to hold the shell interface for some time
 *
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 *
 * @return 0
 */
int sleep_default (int argcounter, char **argvector);

/**
 * command main function
 *
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 *
 * @return 0 on success or a positive int on failure
 */
int com_sleep (int argc, char **argv) {

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
	 * @see run command to hold shell for time specied in argv[1]
	 * @see sleep_default (argc, argv);
	 */
    if (argc == 2) {
        return sleep_default (argc, argv);
    }

    printf ("\n");

    return 0;
}

int sleep_default (int argcounter, char **argvector)
{
    sleep ( atoi(argvector[1]) );
    return 0;
}
