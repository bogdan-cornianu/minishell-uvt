/**
* @cal.c
* @author Cornianu Bogdan-Iancu <cornianu.bogdan@gmail.com>
* @version 1.0.0.0
*
* @section DESCRIPTION
*
* Simple calendar viewer
*
*/

#include<stdio.h>

#define TRUE    1
#define FALSE   0

/**
* Months length in days
*
*/
int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
/**
* Months as caracters
*
*/
char *months[]=
{
	" ",
	"\n\n\nJanuary",
	"\n\n\nFebruary",
	"\n\n\nMarch",
	"\n\n\nApril",
	"\n\n\nMay",
	"\n\n\nJune",
	"\n\n\nJuly",
	"\n\n\nAugust",
	"\n\n\nSeptember",
	"\n\n\nOctober",
	"\n\n\nNovember",
	"\n\n\nDecember"
};
/**
* Determine the day code of provided year
* @param year
* @return daycode
*/
int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;

	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}
/**
* Determine if parameter is a leap year
* @param year
* @return TRUE or FALSE
*/
int determineleapyear(int year)
{
	if(year% 4 == FALSE && year%100 != FALSE || year%400 == FALSE)
	{
		days_in_month[2] = 29;
		return TRUE;
	}
	else
	{
		days_in_month[2] = 28;
		return FALSE;
	}
}
/**
* Print the calendar for the specified year having the provided daycode
* @param year, daycode
*/
void calendar(int year, int daycode)
{
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("%s", months[month]);
		printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );

		// Correct the position for the first date
		for ( day = 1; day <= 1 + daycode * 5; day++ )
		{
			printf(" ");
		}

		// Print all the dates for one month
		for ( day = 1; day <= days_in_month[month]; day++ )
		{
			printf("%2d", day );

			// Is day before Sat? Else start next line Sun.
			if ( ( day + daycode ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
			// Set position for next month
			daycode = ( daycode + days_in_month[month] ) % 7;
	}
}

int main(int argc, char* argv)
{
	int year, daycode, leapyear;
	
	//read your from command line
	year = argv[1];
	//determine day code
	daycode = determinedaycode(year);
	//determine leap year	
	determineleapyear(year);
	//print the calendar
	calendar(year, daycode);
	printf("\n");
}

