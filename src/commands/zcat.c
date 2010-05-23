
/*
 * zcat command
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <unistd.h>

//#include <zlib/zlib.h>
#include <zlib.h>

#define SET_BINARY_MODE(file)

#define CHUNK 16384

int zcat_default (int argcounter, char **argvector);

int main(int argc, char **argv) {

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
                printf("Author:\tMunteanu Oana\n");
                printf("Version:\t1.0\n");
                return 0;
            default:
                return 2;
        }
    }

    printf( "Command will now read gzip sturcture\n");

    // run if argc contains arguments
    if (argc == 2) {
        return zcat_default (argc, argv);
    }

    printf ("\n");

    return 0;
}

int zcat_default (int argcounter, char **argvector)
{
    FILE *inFile;
    int c;

    char *extensionMark = strstr( argvector[1], ".gz" );

    if( extensionMark == NULL )
    {
        fprintf(stderr, "File is not in .gz format\n");
        return 1;
    }

    if( *extensionMark != argvector[1][strlen(argvector[1])-3] )
    {
        fprintf(stderr, "File is not in .gz format\n");
        return 2;
    }

    inFile = fopen(argvector[1], "rb");

    if( inFile == NULL )
    {
        fprintf(stderr, "Cannot open file %s\n", argvector[1]);
        return 3;
    }

/* Decompress from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. */
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
    {
        fclose(inFile);
        return ret;
    }
        
    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, inFile);
        if (ferror(inFile)) {
            (void)inflateEnd(&strm);
            fclose(inFile);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                fprintf(stderr, "Need Dict error - ");
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
                (void)inflateEnd(&strm);
                fclose(inFile);
                fprintf(stderr, "Data Error\n");
                return ret;
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                fclose(inFile);
                fprintf(stderr, "Out of memory\n");
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, stdout) != have || ferror(stdout)) {
                (void)inflateEnd(&strm);
                fclose(inFile);
                fprintf(stderr, "Error writing stdout\n");
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    fclose(inFile);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}