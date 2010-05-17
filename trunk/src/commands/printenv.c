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

int com_printenv(int argc, char ** argv) {
	// Definition of local variables;
	int i = 0;

    extern char ** environ;

	while (environ[i])
		puts(environ[i++]);

	return 0;
}
