/*******************************************************************************
**
** Module Name: cd.c
**
** Project Name: Minishell-UVT
**
********************************************************************************
**
** Created By: Moraru Ionut (morion4000)
**
** Description: Implementation of the UNIX cd command;
**
********************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

// Declare functions used;
int is_dir(const char*);

int main(int argc, char ** argv) {
	// Definition of local variables;
	char * directory; // Directory path;

	if(strcmp(argv[argc-1], "cd") == 0) {
		// If no parameters change to home directory;
		directory = getenv("HOME");
	} else {
		// else change to specified directory;
		directory = argv[argc-1];
		// check to see if directory exits;
		if(!is_dir(directory)) {
			fprintf(stderr, "The specified path does not exits.\n");
			return 0;
		}
	}

	return chdir (directory);
}

/*
 * Checks to see if the path is a directory;
 */

int is_dir(const char *dname) {
        struct stat sbuf;

        if (lstat(dname, &sbuf) == -1) {
                return 0;
        }

        if(S_ISDIR(sbuf.st_mode)) {
                return 1;
        }

        return 0;
}


