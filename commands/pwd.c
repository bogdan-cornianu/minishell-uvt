int com_pwd(int argc, char **argv) {
        char *pwd = NULL;

        if((pwd = get_pwd())) {
                printf("%s\n", pwd));
                return 0;
        }

        return -1;
}