#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    int c;

    if (argc > 3){
        printf("Malformed usage. Use -h to get more help.\n");
	return 1;
	}

    	if (strcmp(argv[1],"-a") == 0){
		
	fp = fopen(argv[2], "a+");	

	if (fp != NULL)
		    {
        while ((c = getchar()) != EOF)
        fputc(c, fp);

        fclose(fp);
		}

	}

	if (strcmp(argv[1],"-a") != 0){
		
	fp = fopen(argv[2], "w");	

	if (fp != NULL)
		    {
        while ((c = getchar()) != EOF)
        fputc(c, fp);

        fclose(fp);

		}
	}		
return 0;
}
