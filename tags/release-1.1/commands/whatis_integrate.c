/**
 * @file whatis.c
 * @author Oana Munteanu, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * display the man pages for argument
 */


/**
 * function executed to display the man pages for argument
 *
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 *
 * @return 0
 */
int whatis_default (int argcounter, char **argvector);

/**
 * command main function
 *
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 *
 * @return 0 on success or a positive int on failure
 */
int com_whatis (int argc, char **argv) {

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
	 * @see run command if argc contais 1 more argument
	 * @see whatis_default (argc, argv);
	 */
    if (argc == 2) {
        return whatis_default (argc, argv);
    }

    printf ("\n");

    return 0;
}

int whatis_default (int argcounter, char **argvector)
{
	int flagPrintNextLine = 0;
	int bytes_read;
  	size_t nbytes = 100;
	char *manline;

	FILE *manCmdFile;

	manCmdFile = fopen (strcat (argvector[1], ".txt"), "r");

	if (manCmdFile == NULL)
	{
		fprintf (stderr, "Man file for command %s cannot be opened", argvector[1]);
		return 1;
	}

	manline = (char *) malloc (nbytes + 1);

  	bytes_read = getline (&manline, &nbytes, manCmdFile);

	while (bytes_read != -1)
	{
		if (strstr (manline, "NAME") != NULL)
		{
			flagPrintNextLine = 1;
		}
		else if (strstr (manline, "SYNOPSIS") != NULL)
		{
			flagPrintNextLine = 0;
		}
		else
		{
			if (flagPrintNextLine)
			{
				printf ("%s", manline);
			}
		}
		bytes_read = getline (&manline, &nbytes, manCmdFile);
	}

    free (manline);
    return 0;
}
