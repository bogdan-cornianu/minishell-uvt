/**
 * @file umask.c
 * @author  Oana Munteanu, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * display and set default umask
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PROFILE_FILE "/etc/profile"

/**
 * function executed to get the current umask setting
 * 	
 * @return 0 on success or a positive int on failure
 */
int umask_get ();

/**
 * function executed to set the umask setting
 * 	
 * @return 0 on success or a positive int on failure
 */
int umask_set (char *mask);

/**
 * function executed to validate a mask settings
 * 
 * @param mask  - calling arguments counter
 * 	
 * @return mask or NULL on error
 */
char* validateMask (char *mask);

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
	 * @see umask_get ();
	 */
    if (argc == 1)
    {
        return umask_get ();
    }

    /**
	 * @see run command if argv contains a new mask
	 * @see umask_set (argv[1]);
	 */
    if (argc == 2) {
        return umask_set (argv[1]);
    }

    printf ("\n");

    return 0;
}

int umask_get ()
{
    FILE *inFile;
    int bytes_read;
    size_t nbytes = 100;
    char *line = NULL;

    inFile = fopen (PROFILE_FILE, "r");

    if (inFile == NULL)
    {
        fprintf (stderr, "umask: Cannot open profile file for read\n");
        return 1;
    }

    bytes_read = getline (&line, &nbytes, inFile);

    while (bytes_read != -1)
    {
        if (strncmp (line, "umask xxx", 5) == 0 && strlen (line) == 10)
        {
            printf ("0%c%c%c\n", line[6], line[7], line[8]);
            bytes_read = -1;
        }
        else
        {
            bytes_read = getline (&line, &nbytes, inFile);
        }
    }

    fclose (inFile);

    return 0;
}

int umask_set (char *mask)
{
    FILE *inFile;
    FILE *tempFile;

    int bytes_read;
    size_t nbytes = 100;
    char *line = NULL;

    char c;

    if (validateMask (mask) == NULL)
    {
        fprintf (stderr, "umask: invalid mask\n");
        return 1;
    }

    // reading and creating temp
    inFile = fopen (PROFILE_FILE, "r");

    if (inFile == NULL)
    {
        fprintf (stderr, "umask: Cannot open profile file for read\n");
        return 1;
    }

    tempFile = fopen ("_temp", "w");

    if (tempFile == NULL)
    {
        fprintf (stderr, "umask: Cannot open temp file for write\n");
        return 1;
    }

    bytes_read = getline (&line, &nbytes, inFile);

    while (bytes_read != -1)
    {
        if (strncmp (line, "umask xxx", 5) == 0 && strlen (line) == 10)
        {
            fprintf (tempFile, "umask %s\n", mask);
            bytes_read = getline (&line, &nbytes, inFile);
        }
        else
        {
            fputs (line, tempFile);
            bytes_read = getline (&line, &nbytes, inFile);
        }
    }

    fclose (inFile);
    fclose (tempFile);

    // writing back to profile file
    inFile = fopen ("profile", "w");

    if (inFile == NULL)
    {
        fprintf (stderr, "umask: Cannot open profile file for write\n");
        return 1;
    }

    tempFile = fopen ("_temp", "r");

    if (tempFile == NULL)
    {
        fprintf (stderr, "umask: Cannot open temp file for read\n");
        return 1;
    }

    while ((c = fgetc (tempFile)) != EOF)
    {
        fputc ((int)c, inFile);
    }

    fclose (inFile);
    fclose (tempFile);

    // cleanup | remove _temp file used
    if (remove ("_temp") != 0)
    {
        fprintf(stderr, "umask: removing \'_temp\' file faild\n");
        return 1;
    }

    return 0;
}

// check mask and return it or return NULL on error
char* validateMask (char *mask)
{
    if (strlen (mask) != 3)
        return NULL;
    if (mask[0] >= '0' && mask [0] <= '7')
        return mask;
    if (mask[1] >= '0' && mask [1] <= '7')
        return mask;
    if (mask[2] >= '0' && mask [2] <= '7')
        return mask;

    return NULL;
}
//-----------------------------------------------------------------------
