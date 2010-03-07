/*******************************************************************************
**
** Module Name: rm.c
**
** Project Name: Minishell-UVT
**
********************************************************************************
**
** Created By: Moraru Ionut (morion4000)
**
** Description: Implementation of the UNIX rm command;
**
********************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

// Declare functions used;

int rm_dir(char *, int, int);
int confirm(char *, char *);
int is_dir(const char*);
int exists(char *);

// Main function;
int main(int argc, char ** argv) {
        // Definition of local variables;
        char * path = argv[argc-1];

        int o;
        int i_flag = 0, r_flag = 0, v_flag = 0;

        // Reseting getopt internal index;
        optind = 0;

        while ((o = getopt(argc, argv, "huirRv")) != -1) {
        switch(o) {
                case 'i':
                        i_flag = 1;
                 break;
                case 'r':
                case 'R':
                        r_flag = 1;
                break;
                case 'v':
                        v_flag = 1;
                break;
                case '?':
                default:
                        abort();
                }
        }

        // check to see if the file or dir exists on disk;
        if(!exists(path)) {
                fprintf(stdout, "Directory or file does not exist on disk.\n");
                return -1;
        }

        if(i_flag && !confirm("Are you sure you want to delete %s? (y/n): ", path))
                return 1;

        if(is_dir(path)) {
        // delete dir;

                if(r_flag) {
                        // recursive directory delete;
                        if(rm_dir(path, i_flag, v_flag)) {
                                if(v_flag)
                                        fprintf(stdout, "%s has been deleted.\n", path);

                                return 0;
                        }
                } else {
                        // delete only empty directory;
                        if(rmdir(path) == 0)  {
                                if(v_flag)
                                        fprintf(stdout, "%s has been deleted.\n", path);

                                return 1;
                        } else fprintf(stdout, "Directory not empty.\n");
                }
        } else {
                // delete file;
                if(remove(path)) {
                        if(v_flag)
                                fprintf(stdout, "%s has been deleted.\n", path);

                        return 1;
                }
        }

        return -1;
}

/*
 * Prompts a confirmation message;
 */

int confirm(char * message, char * path) {
        char ch;

        // print custom message;
        fprintf(stdout, message, path);
        ch = getchar();


        // if not Y(es) return false else return true;
        if(toupper(ch) != 'Y') {
                return 0;
        }

        return 1;
}

/*
 * Recursively removes a directory;
 */

int rm_dir(char * path, int i_flag, int v_flag) {
        DIR *pdir = NULL;
        struct dirent *pent = NULL;
        char * file;
        int counter = 1;

        if (path[strlen(path)-1] != '/')
                strcat(path, "/");

        pdir = opendir (path);

        if (pdir == NULL) {
                return 0;
        }

        while ((pent = readdir (pdir))) {
                if (counter > 2) {
                        int i;

                        for (i = 0; i < 256; i++) file[i] = '\0';

                        strcat(file, path);

                        if (pent == NULL) {
                                return 0;
                        }

                        strcat(file, pent->d_name);

                        if (is_dir(file)) {
                                // if confirmed recursivelly delete directory;
                                if(i_flag && confirm("Are you sure you want to delete %s? (y/n): ", file)) {
                                        rm_dir(file, i_flag, v_flag);
                                }
                        } else {
                                // if confirmed delete file;
                                if(i_flag && confirm("Are you sure you want to delete %s? (y/n): ", file) && remove(file)) {
                                        // verbose;
                                        if(v_flag)
                                                fprintf(stdout, "%s has been deleted.\n", file);
                                }
                        }
                } counter++;
        }

        closedir (pdir);

        rmdir(path);

        // verbose;
        if(v_flag)

                fprintf(stdout, "%s has been deleted.\n", path);

        return 1;
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

/*
 * Checks to see if the path exists on disk;
 */

int exists(char * file) {
        if(fopen(file, "rb") != NULL) {
                return 1;
        }

        return 0;
}

