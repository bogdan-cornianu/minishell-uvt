#include "internal.h"
#include <errno.h>
#include <stdio.h>

const char head_usage[] =
	"head [OPTION] [FILE]...\n"
#ifndef BB_FEATURE_TRIVIAL_HELP
	"\nPrint first 10 lines of each FILE to standard output.\n"
	"With more than one FILE, precede each with a header giving the\n"
	"file name. With no FILE, or when FILE is -, read standard input.\n\n"

	"Options:\n" "\t-n NUM\t\tPrint first NUM lines instead of first 10\n"
#endif
	;

int head(int len, FILE * src)
{
	int i;
	char buffer[1024];

	for (i = 0; i < len; i++) {
		fgets(buffer, 1024, src);
		if (feof(src)) {
			break;
		}
		fputs(buffer, stdout);
	}
	return 0;
}

/* BusyBoxed head(1) */
int head_main(int argc, char **argv)
{
	char opt;
	int len = 10, tmplen, i;

	/* parse argv[] */
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			opt = argv[i][1];
			switch (opt) {
			case 'n':
				tmplen = 0;
				if (++i < argc)
					tmplen = atoi(argv[i]);
				if (tmplen < 1)
					usage(head_usage);
				len = tmplen;
				break;
			case '-':
			case 'h':
				usage(head_usage);
			default:
				fprintf(stderr, "head: invalid option -- %c\n", opt);
				usage(head_usage);
			}
		} else {
			break;
		}
	}

	/* get rest of argv[] or stdin if nothing's left */
	if (i >= argc) {
		head(len, stdin);

	} else {
		int need_headers = ((argc - i) > 1);

		for (; i < argc; i++) {
			FILE *src;

			src = fopen(argv[i], "r");
			if (!src) {
				fprintf(stderr, "head: %s: %s\n", argv[i],
						strerror(errno));
			} else {
				/* emulating GNU behaviour */
				if (need_headers) {
					fprintf(stdout, "==> %s <==\n", argv[i]);
				}
				head(len, src);
				if (i < argc - 1) {
					fprintf(stdout, "\n");
				}
			}
		}
	}
	return(0);
}
