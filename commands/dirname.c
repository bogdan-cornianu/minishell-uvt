int com_dirname(int argc, char** argv) {

	if (argc > 2) {
		printf("dirname: extra operand %s", argv[2]);
		return 0;
	} else if (argc == 1) {
		printf("dirname: missing operand");
		return 0;
	} else {
		printf("%s", dirname(argv[1]));
	}

	return 1;
}