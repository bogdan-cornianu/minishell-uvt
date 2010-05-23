/*
 * echo command
 */



int com_echo (int argcounter, char **argvector);

int com_echo (int argc, char **argv) {

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
