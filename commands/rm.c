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

int com_rm(int argc, char ** argv) {
        // Definition of local variables;
        char * path = argv[argc-1];

        int o;
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
