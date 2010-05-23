#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char            head1[] = {"\n------- \""};
char            head2[] = {" -------\n"};
FILE *          fp;
int             filenum;
int             cc;
unsigned int    linenum = 20;
unsigned int    indx;
long int *      tail;

void getlinenum(int n, char * str[])
{
      for (--n; n; --n)
      {
            ++str;
            if ((**str == '/') || (**str == '-'))
            {
                  linenum = atoi(*(str) + 1);
                  if (linenum <= 0)
                        linenum = 20;
            }
      }
      linenum++;
}

void gettail(void)
{
      unsigned char outstr[15];
      unsigned long int currline = 0L;

      tail = (long int *)malloc(sizeof(*tail) * linenum);
      if (!tail)
      {
            fputs("Insufficient memory.", stderr);
            exit(1);
      }
      tail[0] = ftell(fp);
      indx = 0;

      for (cc = getc(fp); cc != EOF; cc = getc(fp))
      {
            if (cc == '\r')
            {
                  ++currline;
                  cc = getc(fp);
                  if (cc != '\n')
                        ungetc(cc, fp);
                  ++indx;
                  indx %= linenum;
                  tail[indx] = ftell(fp);
            }
            else
            {
                  if (cc == '\n')
                  {
                        ++currline;
                        cc = getc(fp);
                        if (cc != '\r')
                              ungetc(cc, fp);
                        ++indx;
                        indx %= linenum;
                        tail[indx] = ftell(fp);
                  }
            }
      }
      fputs("\" ", stderr);
      sprintf(currline, (char *)outstr, 10);
      fputs((char *)outstr, stderr);
      fputs(" lines", stderr);
      if (currline >= linenum - 1)
      {
            indx++;
            indx %= linenum;
      }
      else  indx = 0;

      if (fseek(fp, tail[indx], 0) == -1)
      {
            fputs("\nFile seek error.", stderr);
            exit(1);
      }
      free(tail);
}

int main(int argc, char **argv)
{
      if (argc <= 1)
      {
            exit(1);
      }

      getlinenum(argc, argv);

      for (filenum = 1; filenum < argc; ++filenum)
      {
            if (*argv[filenum] == '/')
                  continue;
            fp = fopen(argv[filenum], "rb");
            if (!fp)
            {
                  fputs(head1, stderr);
                  fputs(argv[filenum], stderr);
                  fputs("\" not found.", stderr);
                  fputs(head2, stderr);
            }
            else
            {
                  fputs(head1, stderr);
                  fputs(argv[filenum], stderr);
                  gettail();
                  fputs(head2, stderr);
                  for (cc = getc(fp); cc != EOF; cc = getc(fp))
                  {
                fputc(cc, stdout);
                  }
                  fclose(fp);
            }
      }
      return 0;
}
