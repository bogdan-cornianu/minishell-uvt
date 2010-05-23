/**
 * @file clear.c
 * @author  Patricia Minica, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * clears the shell screen using a number of tricky ASCII caracters
 */

/**
 * function executed to clear the screen
 *
 * @param argcounter   - calling arguments counter
 * @param **argvector - calling arguments vector
 *
 * @return 0
 */
int clear_default (int argcounter, char **argvector);

/**
 * command main function
 *
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 *
 * @return 0 on success or a positive int on failure
 */
int com_clear(int argc, char **argv) {

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
	 * @see run command to clear the screen only if function is called with no args
	 * @see clear_default (argc, argv);
	 */
    if (argc == 1) {
        return clear_default (argc, argv);
    }

    printf ("\n");

    return 0;
}

int clear_default (int argcounter, char **argvector)
{
    char esc = 27;
    printf("%c%s", esc, "[2J");
    printf("%c%s", esc, "[1;1H");
    return 0;
}

