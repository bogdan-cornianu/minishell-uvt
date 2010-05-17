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

int com_dir(int argc, char **argv) {
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
