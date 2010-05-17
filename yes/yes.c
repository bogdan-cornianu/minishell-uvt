/*******************************************************************************
**
** Module Name: yes.c
**
** Project Name: Minishell-UVT
**
********************************************************************************
**
** Created By: Moraru Ionut (morion4000)
**
** Description: Implementation of the UNIX yes command;
**
********************************************************************************/

#include <stdio.h>

// Main function
int main(int argc, char ** argv) {
	// Definition of local variables;
	int o;

	if(argc < 2)
		argv[1] = "y";
	while(1) {
		printf("%s\n", argv[1]);
	}
}
