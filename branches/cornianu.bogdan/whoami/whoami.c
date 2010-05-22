/**
* @whoami.c
* @author Cornianu Bogdan-Iancu <cornianu.bogdan@gmail.com>
* @version 1.0.0.0
*
* @section DESCRIPTION
*
* Print effective userid
*
*/
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  register struct passwd *pw;
  register uid_t uid;
  int c,ci,hv = 0, vv = 0;

	while ((ci = getopt (argc, argv, "hv:")) != -1)
         switch (ci)
           {
           case 'h':
             hv = 1;
             break;
           case 'v':
             vv = 1;
             break;
	default: printf("Unknown option!");
  }
  uid = geteuid ();
  pw = getpwuid (uid);
  if (pw)
    {
      puts (pw->pw_name);
	if (vv = 1)
	printf("whoami - version 1.0 by Cornianu Bogdan");
	if (hv == 1)
	printf("Usage: whoami");     

	exit (EXIT_SUCCESS);
    }
  fprintf (stderr,"whoami: cannot find username for UID %u\n", (unsigned) uid);
  exit (EXIT_FAILURE);
  
}

