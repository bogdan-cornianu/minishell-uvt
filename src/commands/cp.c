/*******************************************************************************
**
** Module Name: cp.c
**
** Project Name: Minishell-UVT
**
********************************************************************************
**
** Created By: Moraru Ionut (morion4000)
**
** Description: Implementation of the UNIX cp command;
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
int exists(char *);
int copy_file(char *, char *);
int make_dir(char *, mode_t);

// Main function;
int main(int argc, char **argv) {
	// Definition of local variables;
	int o;
	char *source = NULL, *dest = NULL;
	int i_flag = 0, r_flag = 0, v_flag = 0;

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "irRv")) != -1) {
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

	if(argc < 3) {
		fprintf(stderr, "Please enter SOURCE and DESTINATION.\n");
		return -1;
	}

	source = argv[argc-2];
	dest = argv[argc-1];

	if(is_dir(source) && !is_dir(dest)) {
		fprintf(stderr, "Cannot copy directory to file.\n");
		return -1;
	}

	/* file to file case */
	if((!is_dir(source) && !is_dir(dest)) || (!is_dir(source) && is_dir(dest))) {

		/* file to dir case */
		if(!is_dir(source) && is_dir(dest)) {
			if(dest[strlen(dest)-1] != '/')
				strcat(dest, "/");
			strcat(dest, source);
		}

		if(i_flag) {
			char ch;

	 		printf("DESTINATION file already exists. Overwrite? (y/n): ");
			ch = getchar();
			if(toupper(ch) != 'Y') {
				return 1;
			}
		}

		if(copy_file(source, dest)) {
			if(v_flag)
				fprintf(stdout, "%s copied to %s\n", source, dest);

			return 0;
		}

		return -1;
	} else
	if(is_dir(source) && is_dir(dest)) {
		/* dir to dir case */
		/*
		 * TODO: recursivity;
		 */
		if(r_flag) printf("-r parameter has not yet been implemented.\n");

		if(dest[strlen(dest)-1] != '/')
			strcat(dest, "/");
		strcat(dest, source);

		if(i_flag && is_dir(dest)) {
			char ch;

	 		printf("DESTINATION file already exists. Overwrite? (y/n): ");
			ch = getchar();
			if(toupper(ch) != 'Y') {
				return 1;
			}
		}

		if(make_dir(dest, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
			if(v_flag)
				printf("%s copied to %s\n", source, dest);
			return 0;
		}

		return -1;
	} else fprintf(stderr, "the universe is gonna implode\n");

	return 0;
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

/*
 * Copies one file to another;
 */

int copy_file(char * source, char * destination) {
        char ch;
        FILE *in, *out;

        // open SOURCE file;
        if((in=fopen(source, "rb")) == NULL) {
                fprintf(stderr, "The SOURCE file does not exists.\n");
        return -1;
        }

        // open DESTINATION file;
        if((out=fopen(destination, "wb")) == NULL) {
                fprintf(stderr, "Cannot open DESTINATION for writting.\n");
        return -1;
        }

        // copy character by character from SOURCE to DESTINATION;
        while(!feof(in)) {
                ch = getc(in);
                if(ferror(in)) {
                        printf("Read Error.\n");
                        clearerr(in);
                break;
                } else {
                        if(!feof(in)) putc(ch, out);
                                if(ferror(out)) {
                                        printf("Write Error.\n");
                                        clearerr(out);
                        break;
                        }
                }
        }

        // cleanup;
        fclose(in);
        fclose(out);

        return 1;
}

/*
 * Makes a directory;
 */

int make_dir(char * path, mode_t cmask) {
        return mkdir(path, cmask);
}
