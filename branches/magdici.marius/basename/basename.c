#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	int i;
	char *p;
	char *string;


	for(i=0;i<argc;i++){	
	
	if(strcmp(argv[i],"-u") != 0 && strcmp(argv[i],"-h") != 0 && strcmp(argv[i],"dirname") != 0)
	{
	
	string = argv[1];
     	if (*string == '\0') {
	//printf(".");
	(void)puts(".");
		return 0;
     	}
            
    	p = string + strlen(string) - 1;
      	while (p >= string && *p == '/')
      		*p-- = '\0';
     
     	if (*string == '\0') {
	//printf("/");      		
	(void)puts("/");
     		return 0;
     	}

    	if ((p = strrchr(string, '/')) != NULL)
     	string = p + 1;
     		//printf("%s",string);
    		
	(void)puts(string);
	return 0;
	}
   }

return 0;

}
