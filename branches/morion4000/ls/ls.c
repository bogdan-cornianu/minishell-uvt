/*******************************************************************************
 **
 ** Module Name: ls.c
 **
 ** Project Name: Minishell-UVT
 **
 ********************************************************************************
 **
 ** Created By: Moraru Ionut (morion4000)
 **
 ** Description: Implementation of the UNIX ls command;
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

// Main function;
int main(int argc, char **argv) {
	// Definition of local variables;
	DIR *dir;
	struct dirent *dp;
	struct stat     statbuf;
	struct passwd  *pwd;
	struct group   *grp;
	struct tm      *tm;
	char            datestring[256];

	char * dir_path = ".";

	int l_flag = 0, s_flag = 0, a_flag = 0, F_flag = 0;
	int o;

	// Reseting getopt internal index;
	optind = 0;

	while ((o = getopt(argc, argv, "lsaF")) != -1) {
	 switch(o) {
		case 'l':
			l_flag = 1;
		break;
		case 's':
			s_flag = 1;
		break;
		case 'a':
			a_flag = 1;
		break;
		case 'F':
		 	F_flag = 1;
		break;
		case '?':
		default:
			abort();
		}
	}

	dir_path = argv[argc-1];

        if(a_flag || s_flag || l_flag || F_flag) {
		if(!is_dir(dir_path)) {
			dir_path = ".";
		}
	} else {
		if(strcmp(argv[argc-1], "ls") == 0)
			dir_path = ".";
	}

	if ((dir = opendir (dir_path)) == NULL) {
        	fprintf (stderr, "%s is not a directory.\n", dir_path);
        	return -1;
	}

	while ((dp = readdir (dir)) != NULL) {
		if(!a_flag) {
			char c = dp->d_name[0];
			if(c == '.') continue;
		}

		if(stat(dp->d_name, &statbuf) == -1)
			;//continue;

		if(l_flag) {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			/* Print out type, permissions, and number of links. */
			printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
			printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
			printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
			printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");

			printf("%4d", statbuf.st_nlink);

		    	/* Print out owner's name if it is found using getpwuid(). */
		   	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		    		printf(" %-8.8s", pwd->pw_name);
			//else
			//printf(" %-8d", statbuf.st_uid);

	   		/* Print out group name if it is found using getgrgid(). */
		   	if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			        printf(" %-8.8s", grp->gr_name);
			//else
			//printf(" %-8d", statbuf.st_gid);

			/* Print size of file. */
			printf(" %9jd", (intmax_t)statbuf.st_size);

			tm = localtime(&statbuf.st_mtime);

	   		/* Get localized date string. */
			strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
			printf(" %s %s\n", datestring, dp->d_name);

		} else if(s_flag) {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			printf("%ld", statbuf.st_blocks/2);
			printf(" %s\t", dp->d_name);
		} else if(F_flag) {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			printf("%s", dp->d_name);
			if(S_ISDIR(statbuf.st_mode))  {
				printf("/\t");
			} else if(S_ISLNK(statbuf.st_mode)) {
				printf("@\t");
			} else if(statbuf.st_mode & S_IXUSR) {
                        	printf("*\t");
                        } else {
				printf("\t");
			}
		} else {
			if(!a_flag && (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)) {
                	        continue;
			}

			printf("%s\t", dp->d_name);
		}

	}

	printf("\n");

	closedir(dir);

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
