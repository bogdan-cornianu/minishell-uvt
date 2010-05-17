#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) 
{

  	FILE *fp;//file pointer
	char c;

	fp = fopen(argv[1], "r");

        if (fp != NULL)
        {
	while ((c = fgetc(fp)) != EOF)
        fputc(c, stdout);            
        }
	else
	printf(stderr, "File not found!\n");
        //exit;
	
	close(fp);
	
return 0;

}        
	
