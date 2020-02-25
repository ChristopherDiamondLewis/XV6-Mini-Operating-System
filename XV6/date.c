/*
 * @Author Christopher Lewis
 * 
 * Meant to be a date system call for XV6.
 * 
 * 
 * 
 * 
 * */

#define NULL 0
#define true 1
#define false 0
#define TIMEZONEFLAG "-t"

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "date.h"


struct rtcdate date;
char suffix[3]= "AM\0";
int numToadd = 0;
int negateFlag = false;
int twelveHourFlag = false;

void printDate(struct rtcdate date);
int checkArgs(int argc , char *argv[]);
void printUsage();
void checkTimeZone(int timeZone);
void changeTimeZone(struct rtcdate *date);

int main(int argc ,char *argv[])
{
	if( argc > 4 )
	{
		printUsage();
		exit();
	}
	
	
	getDate(&date);
	
	checkArgs(argc, argv);
	
	changeTimeZone(&date);
	
	
	
	
	
	
	printDate(date);
	
	
	exit();
}
int checkArgs(int argc , char *argv[])
{
	
	
	if ( argc == 2 || argc ==  4 )
	{
		if( *argv[1] != '1' && *argv[1] != '0' )
		{
			printUsage();
			exit();
		}
		if ( *argv[1] == '1' )	// 12HR format if flag for it...
		{
			if ( date.hour > 12 )
			{
				strcpy(suffix,"PM\0");	
			}
			twelveHourFlag = true;
			
			date.hour = date.hour - 12;
		}
		else if ( *argv[1] == '0' )
		{
			
			for ( int i = 0; i < strlen(suffix) ; i++ )
			{
				suffix[0] = '\0';
			}
			
		}
			
	}
	

	 if ( argc == 1 || argc == 3 )
	{
		strcpy(suffix,"\0");
	}
	
	if (argc == 3)
	{
		if (argv[1][0] != '-' && argv[1][1] != 't')	// timezone extension check
		{
			printf(1,"Error wrong TIMEZONE flag\n");
			exit();
			
		}
		
		// Checking timezone format...
		
		if ( argv[2][0] != '-' && argv[2][0] != '+' ) 
		{
			//printf(1,"Where argc == %d...\n" , argc);
			printf(1,"Wrong timezone format..\n");
			exit();
		}
		if(argv[2][2] != '\0' )	// checks if two digit timezone...
		{
			 numToadd = (argv[2][1] + argv[2][2] ) - 87;
				
		}
		else 
		{
			 numToadd = argv[2][1];
			 numToadd -= '0';
			//printf(1,"Add %d to the timezone\n" , numToadd );
		}
		
		if ( argv[2][0] == '-' )
		{
			negateFlag = true;
		}
		
		
	}
	if (argc == 4)
	{
		if (argv[2][0] != '-' && argv[2][1] != 't')	// timezone extension check
		{
			printf(1,"Error wrong TIMEZONE flag\n");
			exit();
		}
		
		// Checking timezone format...
		
		if ( argv[3][0] != '-' && argv[3][0] != '+' ) 
		{
			//printf(1,"Where argc == %d...\n" , argc);
			printf(1,"Wrong timezone format..\n");
			exit();
		}
		if(argv[3][2] != '\0' )	// checks if two digit timezone...
		{
			 numToadd = (argv[3][1] + argv[3][2] ) - 87;
			
		}
		else 
		{
			 numToadd = argv[3][1];
			 numToadd -= '0';
			// printf(1,"Add %d to the timezone\n" , numToadd );
		}
		if ( argv[3][0] == '-' )
		{
			negateFlag = true;
		}
		
		
							
		//printf(1,"Add %d to the timezone\n" , numToadd );
	}
	
	
	checkTimeZone(numToadd);
	
	
		
	
	
	// Getting to this point means we have gone through all test cases for
	// incorrect input...hopefully.
	
	
	
	
	
	
	
	return 0;
}
void checkTimeZone(int timeZone)
{
	//printf(1,"This is timeZone variable in checkTimezone() %d\n", timeZone);
	if ( negateFlag == true )
	{
		timeZone = timeZone * -1;
	}
	
	if ( timeZone < -12 || timeZone > 14 )
	{
		//printf(1,"This is timeZone variable in checkTimezone() %d\n", timeZone);
		printf(1,"TimeZone does not exist...\n");
		exit();
	}
	
	numToadd = timeZone;
}	
void changeTimeZone(struct rtcdate *date)
{
	
	int timeZoneholder = date->hour;
	
	
	//printf(1,"This is what is added to timeZone in changeTimeZone() %d\n", numToadd);
	timeZoneholder += numToadd;
	
	if ( timeZoneholder == 0 )
	{
		timeZoneholder = 12;
	}
	if ( timeZoneholder < 0 )
	{
		//printf(1,"Current numtoAdd to timeZone is %d\n" , numToadd);
		timeZoneholder += 12;
		strcpy(suffix, "AM\0");
	}
	
	
	date->hour = timeZoneholder;
	
	
}
void printDate(struct rtcdate date)
{
	if ( twelveHourFlag == true )	// if 12HR format...
	{
		
		if ( date.hour < 10 )
		{
			printf(1,"The date is 0%d:%d:%d " , date.hour , date.minute, date.second , suffix);
			printf(1,"on %d/%d/%d\n" , date.month , date.day, date.year);
		}
		 if ( date.minute < 10 )
		{
			printf(1,"The date is %d:0%d:%d " , date.hour , date.minute, date.second , suffix);
			printf(1,"on %d/%d/%d\n" , date.month , date.day, date.year);
		}
	    if ( date.second < 10 )
		{
			printf(1,"The date is %d:%d:0%d " , date.hour , date.minute, date.second , suffix);
			printf(1,"on %d/%d/%d\n" , date.month , date.day, date.year);
		}
		else{
			
			printf(1,"The date is %d:%d:%d " , date.hour , date.minute, date.second , suffix);
			printf(1,"on %d/%d/%d\n" , date.month , date.day, date.year);
		}
		
		
	}
	
	
	else{
	
		printf(1,"The date is %d:%d:%d %s " , date.hour , date.minute, date.second , suffix);
		printf(1,"on %d/%d/%d\n" , date.month , date.day, date.year);
	}
}

void printUsage()
{
	printf(1, "Usage: date [Optional:12/24HR flag] [Optional -t TIMEZONE]\n");
	printf(1, "1 for 12 Hour, 0 for 24 Hour\n");
	printf(1, "Use -t TIMEZONE for a timezone. Default is GMT\n");
}

