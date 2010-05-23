#include	windows.h
#include	stdio.h
#include	stdlib.h
#include	string.h

void usage()
{
    printf(Usagentwhereis [starting dir] filespecn);
}

char timestr(char buffer,FILETIME ft)
{
    SYSTEMTIME st;

    FileTimeToSystemTime(ft,&st);

    sprintf(buffer,%02d%02d%02d  %2d%02d,st.wMonth,st.wDay,st.wYear % 100,st.wHour,st.wMinute);
    return buffer;
}

void find(char dir,const char filespec)
{
    WIN32_FIND_DATA fileinfo;
    HANDLE h;
    char spec;
    char d2;
    char p;
    size_t dirlen;

    dirlen = strlen(dir);
    if (dirlen && dir[dirlen - 1] == '')
    {	dir[dirlen - 1] = 0;
	dirlen--;
    }

    spec = (char ) alloca(dirlen + 1 + strlen(filespec) + 1);
    strcpy(spec,dir);
    strcat(spec,);
    strcat(spec,filespec);

    p = strrchr(filespec,'');
    if (p)
    {
	d2 = (char ) alloca(strlen(filespec) + 1);
	strcpy(d2,filespec);
	d2[p - filespec + 1] = 0;
    }
    else
	d2 = ;

    h = FindFirstFile(spec,&fileinfo);
    if (h != INVALID_HANDLE_VALUE)
    {
	do
	{
	    long long size;
	    DWORD att;
	    char atts[8+1];
	    char timebuf[50];
	    int i;

	    att = fileinfo.dwFileAttributes;
	    for (i = 0; i  8; i++)
	    {	static char tab[8] = RHSVDAXX;

		if (att & (1  i))
		    atts[i] = tab[i];
		else
		    atts[i] = '-';
	    }
	    atts[8] = 0;

	    timestr(timebuf,&fileinfo.ftLastWriteTime);
	    size = fileinfo.nFileSizeHigh  0x100000000LL + fileinfo.nFileSizeLow;
	    printf(%s  %s  %9lldt%s%s%sn,timebuf,atts,size,dir,d2,fileinfo.cFileName);
	} while (FindNextFile(h,&fileinfo) != FALSE);
	FindClose(h);
    }

    spec = (char ) alloca(strlen(dir) + 2 + 1);
    strcpy(spec,dir);
    strcat(spec,);
    h = FindFirstFile(spec,&fileinfo);
    if (h != INVALID_HANDLE_VALUE)
    {	char d;
	int len = 0;

	do
	{
	    if (fileinfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
		strcmp(fileinfo.cFileName,.) &&
		strcmp(fileinfo.cFileName,..)
	       )
	    {	int x;

		x = strlen(dir) + 1 + strlen(fileinfo.cFileName) + 1;
		if (x  len)
		{   d = (char ) alloca(x);
		    len = x;
		}
		strcpy(d,dir);
		strcat(d,);
		strcat(d,fileinfo.cFileName);
		find(d,filespec);
	    }
	} while (FindNextFile(h,&fileinfo) != FALSE);
	FindClose(h);
    }
}

int main(int argc,char argv[])
{
    switch (argc)
    {
	default
	    usage();
	    return EXIT_FAILURE;
	case 2
	    find(,argv[1]);
	    break;
	case 3
	    find(argv[1],argv[2]);
	    break;
    }
    return EXIT_SUCCESS;
}
