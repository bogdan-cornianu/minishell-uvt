#include <stdio.h>
#include <time.h>
#include <errno.h>

#define FSHIFT          16              
#define FIXED_1         (1<<FSHIFT)     
#define LOAD_INT(x) ((x) >> FSHIFT)
#define LOAD_FRAC(x) LOAD_INT(((x) & (FIXED_1-1)) * 100)


int main(int argc, char* argv[])
{
	int updays, uphours, upminutes;
	struct sysinfo info;
	struct tm *current_time;
	time_t current_secs;

	time(&current_secs);
	current_time = localtime(&current_secs);

	sysinfo(&info);

	fprintf(stdout, " %2d:%02d%s  up ", 
			current_time->tm_hour%12 ? current_time->tm_hour%12 : 12, 
			current_time->tm_min, current_time->tm_hour > 11 ? "pm" : "am");
	updays = (int) info.uptime / (60*60*24);
	if (updays)
		fprintf(stdout, "%d day%s, ", updays, (updays != 1) ? "s" : "");
	upminutes = (int) info.uptime / 60;
	uphours = (upminutes / 60) % 24;
	upminutes %= 60;
	if(uphours)
		fprintf(stdout, "%2d:%02d, ", uphours, upminutes);
	else
		fprintf(stdout, "%d min, ", upminutes);

	printf("load average: %ld.%02ld, %ld.%02ld, %ld.%02ld\n", 
			LOAD_INT(info.loads[0]), LOAD_FRAC(info.loads[0]), 
			LOAD_INT(info.loads[1]), LOAD_FRAC(info.loads[1]), 
			LOAD_INT(info.loads[2]), LOAD_FRAC(info.loads[2]));

	return(TRUE);
}
