/**
 * @file ls.c
 * @author  Patricia Minica, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * display directory content
 */


/**
 * list curent directory content (no other info)
 *
 * @param dirname   - directory to be listed
 *
 * @return 0 on success or a positive int on failure
 */
int ext_ls_default(char * dirname);

/**
 * list curent directory content (with . and ..)
 *
 * @param dirname   - directory to be listed
 *
 * @return 0 on success or a positive int on failure
 */
int ext_ls_a(char * dirname);

/**
 * list curent directory content (with formating options)
 *
 * @param dirname   - directory to be listed
 *
 * @return 0 on success or a positive int on failure
 */
int ext_ls_F(char * dirname);

/**
 * list curent directory content (with access, owner, group and timestamp)
 *
 * @param dirname   - directory to be listed
 *
 * @return 0 on success or a positive int on failure
 */
int ext_ls_l(char * dirname);

/**
 * list curent directory content (with size in blocks)
 *
 * @param dirname   - directory to be listed
 *
 * @return 0 on success or a positive int on failure
 */
int ext_ls_s(char * dirname);

/**
 * parse rights from int to mode
 *
 * @param st_mode   - int more to be converted
 *
 * @return void
 */
void readrights(mode_t st_mode);

/**
 * command main function
 *
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 *
 * @return 0 on success or a positive int on failure
 */
int com_ls(int argc, char *argv[]) {

    optind = 0;
    int o;

    char *w_dir = malloc(PATH_MAX * sizeof (char));
    if (w_dir == NULL) {
        fprintf(stderr, "ls: cannot allocate memory for \'w_dir\'\n");
        return 1;
    }

    if ((w_dir = getcwd(w_dir, PATH_MAX)) == NULL) {
        fprintf(stderr, "ls: -a: cannot get working directory\n");
        free(w_dir);
        return 1;
    }

    while ((o = getopt(argc, argv, "aFlshu")) != -1) {
        switch (o) {
            case 'a':
                if (argc == 2) { //if called with no dir name then list the curent dir
                    int tempres = ext_ls_a(w_dir);
                    free(w_dir);
                    return tempres;
                } else if (argc == 3) {
                    int tempres = ext_ls_a(argv[2]);
                    free(w_dir);
                    return tempres;
                }
                free(w_dir);
                return 1;
            case 'F':
                if (argc == 2) {
                    int tempres = ext_ls_F(w_dir);
                    free(w_dir);
                    return tempres;
                } else if (argc == 3) {
                    int tempres = ext_ls_F(argv[2]);
                    free(w_dir);
                    return tempres;
                }
                free(w_dir);
                return 1;
            case 'l':
                if (argc == 2) {
                    int tempres = ext_ls_l(w_dir);
                    free(w_dir);
                    return tempres;
                } else if (argc == 3) {
                    int tempres = ext_ls_l(argv[2]);
                    free(w_dir);
                    return tempres;
                }
                free(w_dir);
                return 1;
            case 's':
                if (argc == 2) {
                    int tempres = ext_ls_s(w_dir);
                    free(w_dir);
                    return tempres;
                } else if (argc == 3) {
                    int tempres = ext_ls_s(argv[2]);
                    free(w_dir);
                    return tempres;
                }
                free(w_dir);
                return 1;
            case 'h':
                printf("lists dir content\n");
                printf("-a, do not hide entries starting with .\n");
                printf("-F, append indicator (one of */=@|) to entries\n");
                printf("-l, use a long listing format\n");
                printf("-s, print size of each file, in blocks \n");
                printf("-h, display this help and exit\n");
                printf("-u, shows Author and Version info and exit\n");
                free(w_dir);
                return 0;
            case 'u':
                printf("Author: ls: Patricia Minica\n");
                printf("Version: ls: 1.0\n");
                free(w_dir);
                return 0;
            default:
                free(w_dir);
                return 2;
        }
    }

    //lists the content of working dir
    if (argc == 1) {
        int tempres = ext_ls_default(w_dir);
        free(w_dir);
        return tempres;
    }

    //lists the content of the argv[1] dir name
    if (argc == 2) {
        int tempres = ext_ls_default(argv[1]);
        free(w_dir);
        return tempres;
    }

    free(w_dir);
    return 0;
}

//print directory content without . and .. (default behaviour)

int ext_ls_default(char * dirname) {

    DIR *odir = opendir(dirname);
    struct dirent *rdir;

    if (odir == NULL) {
        printf("%s\n", dirname);
        return 1;
    }

    while ((rdir = readdir(odir)) != NULL) {
        if (rdir->d_name[0] != '.') {
            printf("%-10.20s", rdir->d_name);
        }
    }
    printf("\n");

    if (closedir(odir) == -1) {
        fprintf(stderr, "ls: unable to close \'%s\' directory\n", dirname);
        return 1;
    }

    return 0;
}
//-----------------------------------------------------------------------

//print all directory content

int ext_ls_a(char * dirname) {

    DIR *odir= opendir(dirname);
    struct dirent *rdir;

    if (odir == NULL) {
        printf("%s\n", dirname);
        return 1;
    }

    while (rdir = readdir(odir)) {
        printf("%-10.20s ", rdir->d_name);
    }
    printf("\n");

    if (closedir(odir) == -1) {
        fprintf(stderr, "ls: unable to close \'%s\' directory\n", dirname);
        return 1;
    }

    return 0;
}
//-----------------------------------------------------------------------

//print directory content and add * or / to the file name

int ext_ls_F(char * dirname) {

    DIR *odir;
    struct dirent *rdir;
    struct stat f_info;
    char * temp = malloc(NAME_MAX * sizeof (char *));
    if (temp == NULL) {
        fprintf(stderr, "ls -F: cannot allocate memory for \'temp\'\n");
        return 1;
    }

    char * tempp = malloc(PATH_MAX * sizeof (char *));
    if (tempp == NULL) {
        fprintf(stderr, "ls -F: cannot allocate memory for \'tempp\'\n");
        free(temp);
        return 1;
    }

    if (dirname[strlen(dirname) - 1] == '/') { //remove / from the end of the string
        dirname[strlen(dirname) - 1] = '\0';
    }

    odir = opendir(dirname);
    if (odir == NULL) {
        printf("%s\n", dirname);
        free(temp);
        free(tempp);
        return 1;
    }

    while (rdir = readdir(odir)) {
        if (rdir->d_name[0] != '.') {
            strcpy(tempp, dirname);
            strcat(tempp, "/");
            strcat(tempp, rdir->d_name);

            if (stat(tempp, &f_info) != 0) {
                fprintf(stderr, "ls: -F: cannot read \'%s\' file atributes\n", rdir->d_name);
                free(temp);
                free(tempp);
                return 1;
            }

            if (f_info.st_mode & S_IFDIR) { //if file is a dir add / at the end
                strcpy(temp, rdir->d_name);
                strcat(temp, "/");
                printf("%-10.20s ", temp);
            }
            else if ((f_info.st_mode & S_IXUSR) || (f_info.st_mode & S_IXGRP) || (f_info.st_mode & S_IXOTH)) {
                //if file is exe
                strcpy(temp, rdir->d_name);
                strcat(temp, "*");
                printf("%-10.20s ", temp);
            }
            else {
                printf("%-10.20s ", rdir->d_name);
            }
        }
    }

    printf("\n");

    if (closedir(odir) == -1) {
        fprintf(stderr, "ls: unable to close \'%s\' directory\n", dirname);
        free(temp);
        free(tempp);
        return 1;
    }

    free(temp);
    free(tempp);
    return 0;
}
//-----------------------------------------------------------------------

//print directory content without . and .. long format

int ext_ls_l(char * dirname) {

    DIR *odir;
    struct dirent *rdir;
    struct stat f_info;
    struct tm * ptm;
    struct passwd *uiname;
    struct group *giname;
    char * temp = malloc(PATH_MAX * sizeof (char *));
    if (temp == NULL) {
        fprintf(stderr, "ls -l: cannot allocate memory for \'temp\'\n");
        return 1;
    }

    if (dirname[strlen(dirname) - 1] == '/') { //remove / from the end of the string
        dirname[strlen(dirname) - 1] = '\0';
    }

    odir = opendir(dirname);
    if (odir == NULL) {
        printf("%s\n", dirname);
        free(temp);
        return 1;
    }

    while (rdir = readdir(odir)) {
        if (rdir->d_name[0] != '.') {
            strcpy(temp, dirname);
            strcat(temp, "/");
            strcat(temp, rdir->d_name);

            if (stat(temp, &f_info) == -1) {
                //if stst fails the "file" may be a symbolic link, try to open with lstat
                if (lstat(temp, &f_info) == -1) {
                    fprintf(stderr, "ls: -l: cannot read \'%s\' file atributes\n", rdir->d_name);
                    free(temp);
                    return 1;
                } else {
                    if (f_info.st_mode & S_IFLNK) printf("l");
                    else printf("-");
                }

            } else {
                if (f_info.st_mode & S_IFDIR) printf("d");
                else printf("-");
            }

            readrights(f_info.st_mode);

            printf("%2d ", (int) f_info.st_nlink);

            uiname = getpwuid(f_info.st_uid);
            printf("%-7.15s ", uiname->pw_name);

            giname = getgrgid(f_info.st_gid);
            printf("%-7.15s ", giname->gr_name);

            printf("%7d ", (int) f_info.st_size);

            ptm = gmtime(&f_info.st_mtime);
            printf("%4d-%02d-%02d %2d:%02d ", (ptm->tm_year) + 1900,
                    ptm->tm_mon, ptm->tm_mday, (ptm->tm_hour) % 24, ptm->tm_min);

            printf("%s\n", rdir->d_name);

        }
    }

    if (closedir(odir) == -1) {
        fprintf(stderr, "ls: unable to close \'%s\' directory\n", dirname);
        free(temp);
        return 1;
    }

    free(temp);
    return 0;
}
//-----------------------------------------------------------------------

//print directory content without . and .. and size in blocks

int ext_ls_s(char * dirname) {

    DIR *odir;
    struct dirent *rdir;
    struct stat f_info;
    char * temp = malloc(PATH_MAX * sizeof (char *));

    if (dirname[strlen(dirname) - 1] == '/') { //remove / from the end of the string
        dirname[strlen(dirname) - 1] = '\0';
    }

    odir = opendir(dirname);
    if (odir == NULL) {
        printf("%s\n", dirname);
        free(temp);
        return 1;
    }

    while (rdir = readdir(odir)) {
        if (rdir->d_name[0] != '.') {
            strcpy(temp, dirname);
            strcat(temp, "/");
            strcat(temp, rdir->d_name);

            if (stat(temp, &f_info) != 0) {
                fprintf(stderr, "ls: -s: cannot read \'%s\' file atributes\n", rdir->d_name);
                free(temp);
                return 1;
            }

            //FIXME the size if double then the console function reports (bug???)
            printf(" %d ", (int) f_info.st_blocks);
            printf("%s\t", rdir->d_name);
        }
    }

    printf("\n");

    if (closedir(odir) == -1) {
        fprintf(stderr, "ls: unable to close \'%s\' directory\n", dirname);
        free(temp);
        return 1;
    }

    free(temp);
    return 0;
}
//-----------------------------------------------------------------------

//read the file rights

void readrights(mode_t st_mode) {

    if (st_mode & S_IRUSR) printf("r");
    else printf(" -");
    if (st_mode & S_IWUSR) printf("w");
    else printf("-");
    if (st_mode & S_IXUSR) printf("x");
    else printf("-");
    if (st_mode & S_IRGRP) printf("r");
    else printf("-");
    if (st_mode & S_IWGRP) printf("w");
    else printf("-");
    if (st_mode & S_IXGRP) printf("x");
    else printf("-");
    if (st_mode & S_IROTH) printf("r");
    else printf("-");
    if (st_mode & S_IWOTH) printf("w");
    else printf("-");
    if (st_mode & S_IXOTH) printf("x ");
    else printf("- ");

}
//-----------------------------------------------------------------------
