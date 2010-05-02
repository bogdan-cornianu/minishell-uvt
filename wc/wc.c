#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc,char **argv)
{

char c;
char prev;
long n_chars = 0L;
int n_lines = 0;
int n_words = 0;
int n_bytes = 0;
int ci, hv = 0, vv = 0, wv = 0, mv = 0, lv = 0, cv = 0;
//bool inword = false;
FILE *fp;
/*read options*/
while ((ci = getopt (argc, argv, "hvwmlc:")) != -1)
         switch (ci)
           {
           case 'h':
             hv = 1;
             break;
           case 'v':
             vv = 1;
             break;
	case 'w':
             wv = 1;
             break;
	case 'm':
             mv = 1;
             break;
	case 'l':
             lv = 1;
             break;
	case 'c':
             cv = 1;
             break;
	default: printf("Unknown option!");
}

if (argc == 2)
        fp = fopen(argv[1], "r");
	else
	fp = fopen(argv[2], "r");

if(fp == NULL)
{
//read from stdin

printf("Enter text(Use Ctrl+D to quit): ");
prev = '\n';
while((c = getchar()) != EOF)
{
if(mv == 1)
n_chars++;

if(cv == 1)
n_bytes++;

if(lv == 1)
{
if(c == '\n')
n_lines++;
}

if(wv ==1)
{
if( isspace(c) != 0)
//inword = true;
n_words++;
}

/*
if(isspace && inword)
inword = false;
prev = c;
*/
}
//printf("Characters = %ld, words = %d, lines = %d\n", n_chars, n_words, n_lines);
}

if(fp != NULL)
{
prev = '\n';

while((c = fgetc(fp)) != EOF)
{
if(mv == 1)
n_chars++;

if (vv == 1)
printf("WordCount - version 1.0 by Cornianu Bogdan");

if (hv == 1)
{
printf("Usage: wc [options] [filename]");
printf("Options: -w Count words");
printf("Options: -l Count lines");
printf("Options: -c Count bytes");
printf("Options: -m Count characters");
}
if(cv == 1)
n_bytes++;

if(lv ==1)
{
if(c == '\n')
n_lines++;
}

if(wv ==1)
{
if( isspace(c) != 0)
//inword = true;
n_words++;
}

//printf("Characters = %ld, words = %d, lines = %d\n", n_chars, n_words, n_lines);
}
fclose(fp);
}

//if(argc<=2)
printf("\nCharacters = %ld, bytes = %d, words = %d, lines = %d\n", n_chars, n_bytes, n_words, n_lines);

return 0;
}

