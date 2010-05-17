/*******************************************************************************
**
** Module Name: dir.c
**
** Project Name: Minishell-UVT
**
********************************************************************************
**
** Created By: Moraru Ionut (morion4000)
**
** Description: Implementation of the UNIX dir command;
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

int main(int argc, char **argv) {
	// Definition of local variables;
	DIR *dir;
	struct dirent *dp;

	char * dir_path = ".";

	if ((dir = opendir (dir_path)) == NULL) {
        	fprintf (stderr, "%s is not a directory.\n", dir_path);
        	return 1;
	}

	while ((dp = readdir (dir)) != NULL) {
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
			continue;
		}
		char c = dp->d_name[0];
		if(c == '.') continue;

		fprintf(stdout, "%s\t", dp->d_name);
	}

	fprintf(stdout, "\n");

	closedir(dir);

	return 0;
}
