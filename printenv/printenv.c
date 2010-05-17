/*******************************************************************************
**
** Module Name: printenv.c
**
** Project Name: Minishell-UVT
**
********************************************************************************
**
** Created By: Moraru Ionut (morion4000)
**
** Description: Implementation of the UNIX printenv command;
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

int main(int argc, char ** argv) {
	// Definition of local variables;
	int i = 0;

    extern char ** environ;

	while (environ[i])
		puts(environ[i++]);

	return 0;
}
