/**
 * @file gzip.c
 * @author  Patricia Minica, anul 2 Informatica - Engleza
 * @version 1.0
 *
 * archives a file passes with calling function argument
 */


#define SET_BINARY_MODE(file)
#define CHUNK 16384

/**
 * function executed to archive a file
 *
 * @param argcounter  - calling arguments counter
 * @param **argvector - calling arguments vector
 *
 * @return 0 on success or a positive int on failure
 */
int gzip_default (int argcounter, char **argvector);

/**
 * command main function
 *
 * @param argc   - calling arguments counter
 * @param **argv - calling arguments vector
 *
 * @return 0 on success or a positive int on failure
 */
int com_gzip(int argc, char **argv) {

    SET_BINARY_MODE(stdin);
    SET_BINARY_MODE(stdout);

    optind = 0;
    int o;

    while ((o = getopt(argc, argv, "hu")) != -1) {
        switch (o) {
            case 'h':
                printf("-h, display this help and exit\n");
                printf("-u, shows Author and Version info and exit\n");
                return 0;
            case 'u':
                printf("Author:\tMinica Patricia\n");
                printf("Version:\t1.0\n");
                return 0;
            default:
                return 2;
        }
    }

    /**
	 * @see run command to archive the argv[1] file
	 * @see gzip_default (argc, argv);
	 */
    if (argc == 2) {
        return gzip_default (argc, argv);
    }

    printf ("\n");

    return 0;
}

int gzip_default (int argcounter, char **argvector)
{
    FILE *inFile, *outFile;
    int c;
    char outfileName[20];

    inFile = fopen(argvector[1], "rb");

    if( inFile == NULL )
    {
        fprintf(stderr, "Cannot open file %s\n", argvector[1]);
        return 3;
    }

    strcpy (outfileName, argvector[1]);
    strcat (outfileName, ".gz");

    outFile = fopen(outfileName, "wb");

    if( inFile == NULL )
    {
        fprintf(stderr, "Cannot open file %s\n", outfileName);
        return 4;
    }

	/**
		@see
		Compress from file source to file dest until EOF on source.
		def() returns Z_OK on success, Z_MEM_ERROR if memory could not be
		allocated for processing, Z_STREAM_ERROR if an invalid compression
		level is supplied, Z_VERSION_ERROR if the version of zlib.h and the
		version of the library linked do not match, or Z_ERRNO if there is
		an error reading or writing the files
	*/
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /** @see allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK)
        return ret;

    /** @see compress until end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, inFile);
        if (ferror(inFile)) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }
        flush = feof(inFile) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /** @see run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, outFile) != have || ferror(outFile)) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /** @see clean up and return */
    (void)deflateEnd(&strm);

    return Z_OK;
}
