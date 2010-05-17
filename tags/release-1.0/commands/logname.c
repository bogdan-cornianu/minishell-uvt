/*******************************************************************************
**
** Module Name: logname.c
**
** Project Name: Minishell-UVT
**
********************************************************************************
**
** Created By: Moraru Ionut (morion4000)
**
** Description: Implementation of the UNIX logname command;
**
********************************************************************************/

int com_logname(int argc, char **argv) {
	// Create buffer to hold login name;
	char buffer[128];

	if(getlogin_r(buffer, sizeof(buffer)) == 0) {
		puts(buffer);
		return fflush(stdout);
	}

	return 1;
}
