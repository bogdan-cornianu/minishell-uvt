/**
 * @file time.c
 * @author  Oana Munteanu, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * display the time 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>

#define MAX_ARGS 20

/**
 * function executed to run a command in fork and display the time of running
 * 
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 * 	
 * @return 0 on success or a positive int on failure
 */
int time_default (int argcounter, char **argvector);

/**
 * command main function
 * 
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 * 	
 * @return 0 on success or a positive int on failure
 */
int main(int argc, char **argv) {

    char **argvector = (char**)malloc (MAX_ARGS * sizeof (char *));
    int argcounter;

    optind = 0;
    int o;

    while ((o = getopt(argc, argv, "hu")) != -1) {
        switch (o) {
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
	 * @see time_default (argcounter, argvector);
	 */
    if (argc > 1) {
        for( argcounter = 2; argcounter <= argc; argcounter++)
        {
            argvector[argcounter-2] = (char*)malloc (sizeof (argv[argcounter-1]));
            strcpy( argvector[argcounter-2], argv[argcounter-1] );
        }
        argvector[argcounter] == NULL; // add null to the argv string
        return time_default (argcounter, argvector);
    }

    printf ("\n");

    // clean up
    for( argcounter--; argcounter >=0; argcounter--)
    {
        free( argvector );
    }
    free( argvector );

    return 0;
}

int time_default (int argcounter, char **argvector)
{
    int status;
    pid_t pid, waitPid;

    time_t startTime, endTime;
    double difTime;

    time( &startTime );

    pid = fork();

    if (pid < 0)
    {
        // fork faild, report failure
        fprintf(stderr, "Fork faild");
        status = -1;
    }
    else if (pid == 0)
    {
        // child process
        execvp (argvector[0], argvector); // exec only returns on failure

        fprintf (stderr, "Exec faild, command did not run\n");
        _exit (EXIT_FAILURE);
    }
    else
    {
        // parrent process
        waitPid = waitpid (pid, &status, 0);

        time( &endTime );

        difTime = difftime( endTime, startTime );

        printf("Running time of command: %.2lf seconds\n", difTime);
    }

    return 0;
}
