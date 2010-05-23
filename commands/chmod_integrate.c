/*
 * chmod command
 */


int chmod_default (int mode, char *fdname);
mode_t itomode (int mode);

int com_chmod (int argc, char **argv) {

    optind = 0;
    int o;

    while ((o = getopt (argc, argv, "hu")) != -1) {
        switch (o) {
            case 'h':
                printf ("-h, display this help and exit\n");
                printf ("-u, shows Author and Version info and exit\n");
                return 0;
            case 'u':
                printf ("Author:\tMunteanu Oana\n");
                printf ("Version:\t1.0\n");
                return 0;
            default:
                return 2;
        }
    }

    if (argc < 3) {
        fprintf (stderr, "Usage: <chmod \"mode\" \"file/directory\">\n");
        return 1;
    }

    // run if argc contains arguments
    if (argc == 3) {
        return chmod_default (atoi(argv[1]), argv[2]);
    }

    printf ("\n");

    return 0;
}

int chmod_default (int mode, char *fdname)
{
    mode_t newmode;
    newmode = itomode(mode);

    if (newmode == -1) {
        fprintf (stderr, "chmod: \'%d\' invalid access rights\n", mode);
        return 1;
    }

    if (chmod(fdname, newmode) != 0) {
        fprintf (stderr, "chmod: changing access right for \'%s\' faild\n", fdname);
        return 1;
    }

    return 0;
}

// convert from int to mode_t
mode_t itomode (int mode)
{
    int ua;
    int ga;
    int oa;

    mode_t uam;
    mode_t gam;
    mode_t oam;

    if (mode >= 0 && mode <= 777) {
        oa = mode % 10;
        mode /= 10;
        ga = mode % 10;
        mode /= 10;
        ua = mode;
    }
    else
    {
        return -1;
    }

    if (oa > 7 || ga > 7 || ua > 7)
    {
        return -1;
    }

    if (ua == 7) uam = S_IRWXU;
    else if (ua == 6) uam = S_IRUSR | S_IWUSR;
    else if (ua == 5) uam = S_IRUSR | S_IXUSR;
    else if (ua == 4) uam = S_IRUSR;
    else if (ua == 3) uam = S_IWUSR | S_IXUSR;
    else if (ua == 2) uam = S_IWUSR;
    else if (ua == 1) uam = S_IXUSR;
    else uam = 0;
    if (ga == 7) gam = S_IRWXG;
    else if (ga == 6) gam = S_IRGRP | S_IWGRP;
    else if (ga == 5) gam = S_IRGRP | S_IXGRP;
    else if (ga == 4) gam = S_IRGRP;
    else if (ga == 3) gam = S_IWGRP | S_IXGRP;
    else if (ga == 2) gam = S_IWGRP;
    else if (ga == 1) gam = S_IXGRP;
    else gam = 0;
    if (oa == 7) oam = S_IRWXO;
    else if (oa == 6) oam = S_IROTH | S_IWOTH;
    else if (oa == 5) oam = S_IROTH | S_IXOTH;
    else if (oa == 4) oam = S_IROTH;
    else if (oa == 3) oam = S_IWOTH | S_IXOTH;
    else if (oa == 2) oam = S_IWOTH;
    else if (oa == 1) oam = S_IXOTH;
    else oam = 0;

    return uam | gam | oam;
}
//-----------------------------------------------------------------------
