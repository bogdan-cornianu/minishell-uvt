/*
 * Project: Unix Find command
 * Author: Rimescu Adi-Ciprian
 * Date: Feb 23 2010
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <ftw.h>
#include <getopt.h>

/*
 * Constants declaration
 */

#define ERR_DIR_NOT_OPEN "Directory could not be opened."
#define ERR_DIR_STAT_FAILED "Stat could not be read."
#define ERR_DIR_CH_FAILED "Directory could not be changed."

#define MAX_OPTIONS 20

/*
 * Functions prototypes
 */

void find(char *);
int list(const char*, const struct stat *, int);

/*
 * Global variables;
 */
static int verbose_flag;
char **options_array = NULL;
char **argument_array = NULL;
int opt_arg_array_index = 0;


int main(int argc, char **argv)
{
    // If no last argument is provided,
    // then consider root as default.
    char *search_path = NULL;
    int c;

    // Dynamic alocate memory.
    options_array = malloc(MAX_OPTIONS * sizeof(char *));
    argument_array = malloc(20 * sizeof(char *));

    while (1) {
       static struct option long_options[] = {
           /* These options set a flag. */
           {"verbose",      0, &verbose_flag, 1},
           {"brief",        0, &verbose_flag, 0},
           /* These options don't set a flag.
              We distinguish them by their indices. */
            {"amin",        1, 0, 'a'},
            {"anewer",      1, 0, 'b'},
            {"atime",       1, 0, 'c'},
            {"cmin",        1, 0, 'd'},
            {"cnewer",      1, 0, 'e'},
            {"ctime",       1, 0, 'f'},
            {"mmin",        1, 0, 'g'},
            {"newer",       1, 0, 'h'},
            {"mtime",       1, 0, 'i'},
            {"name",        1, 0, 'j'},
            {"iname",       1, 0, 'k'},
            {"type",        1, 0, 'l'},
            {"size",        1, 0, 'm'},
            {"perm",        1, 0, 'n'},
            {"readable",    1, 0, 'o'},
            {"executable",  1, 0, 'p'},
            {"writable",    1, 0, 'r'},
            {0, 0, 0, 0}
        };

       /* getopt_long stores the option index here. */
       int option_index = 0;

       c = getopt_long_only (argc, argv, "a:b:c:d:e:f:g:h:i:j:k:l:m:n:o:p:r:",
                             long_options, &option_index);

       /* Detect the end of the options. */
       if (c == -1)
         break;

       switch (c) {
         case 0:
           /* If this option set a flag, do nothing else now. */
           if (long_options[option_index].flag != 0)
             break;
           printf ("option %s", long_options[option_index].name);
           if (optarg)
             printf (" with arg %s", optarg);
           printf ("\n");
         break;

         /// AMIN
         case 'a':
           options_array[opt_arg_array_index] = malloc(100 * sizeof(char));
           strcpy(options_array[opt_arg_array_index], "amin");

           argument_array[opt_arg_array_index] = malloc(sizeof(optarg));
           strcpy(argument_array[opt_arg_array_index], optarg);

           opt_arg_array_index++;
         break;

         /// TYPE
         case 'l':
           options_array[opt_arg_array_index] = malloc(100 * sizeof(char));
           strcpy(options_array[opt_arg_array_index], "type");

           argument_array[opt_arg_array_index] = malloc(sizeof(optarg));
           strcpy(argument_array[opt_arg_array_index], optarg);

           opt_arg_array_index++;
         break;

         case '?':
           /* getopt_long already printed an error message. */
           break;

         default:
           abort ();
         }
     }

    search_path = malloc(100 * sizeof(char));

    /* Any remaining command line argument is considered to be the search path. */
    if (optind < argc) {
       search_path = argv[optind++];
    } else {
       search_path = "/";
    }

    find(search_path);

    return 0;
}


int list(const char *name, const struct stat *status, int type) {
    // FTW_F    The object is a  file
    // FTW_D    ,,    ,,   ,, ,, directory
    // FTW_DNR  ,,    ,,   ,, ,, directory that could not be read
    // FTW_SL   ,,    ,,   ,, ,, symbolic link
    // FTW_NS   The object is NOT a symbolic link and is one for
    //          which stat() could not be executed

    if(type == FTW_NS)
        return 0;

    int is_valid_result = 1;

    // If we have elements in the options array,
    // then apply search filters, else simply act
    // as recursive "ls".
    if(opt_arg_array_index > 0) {
        int i;
        for(i=0; i<opt_arg_array_index; i++) {
            /// AMIN - accessed minutes ago
            if(strcmp(options_array[opt_arg_array_index], "amin") == 0) {
                char *argument = argument_array[opt_arg_array_index];

                if(argument[0] == '+') {
                    //status->st_atime
                } else if(argument[0] == '-') {

                } else {

                }

                is_valid_result = 0;
            }

            /// TYPE (file, directory, link)
            if(strcmp(options_array[opt_arg_array_index], "type") == 0) {
                is_valid_result = 0;

                if((strcmp(argument_array[opt_arg_array_index], "file") == 0) &&
                    type == FTW_F)
                    is_valid_result = 1;
                if((strcmp(argument_array[opt_arg_array_index], "directory") == 0) &&
                    type == FTW_D)
                    is_valid_result = 1;
                if((strcmp(argument_array[opt_arg_array_index], "link") == 0) &&
                    type == FTW_SL)
                    is_valid_result = 1;
            }

        }
    }

    if(is_valid_result) {
        if(type == FTW_F)
            printf("%s\n", name);

        if(type == FTW_D && strcmp(".", name) != 0)
            printf("%s/\n", name);
    }

    return 0;
}

void find(char *path) {
    printf("Results found:\n\n");
    ftw(path, list, 1);
}
