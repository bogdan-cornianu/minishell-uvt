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

int com_cd(int argc, char ** argv) {
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
