///
///	@author Christopher Lewis
///
///	CS370 Project6 - Thread implementation and testing in xv6.
///
///
///


#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"



#define MIN 1


#define true 1
#define false 0

int argValidation(int argc, char *argv[]);

int amicableNums1[1000] = {0};
int amicableNums2[1000] = {0};
int amicableIndex = 0;
int userLimit = 0;
int threadCount = 0;


void addToAmicableNums(int num1, int num2);

void printAmicableNums();

int properDividingSums(int currNum);

 
int main(int argc, char *argv[])
{
	
	
	
	if ( argValidation(argc, argv) == 0)
	{
		
		 for (int i = MIN; i <= userLimit; i++) 
		 {
        		int newNum = properDividingSums (i);

				if ((i < newNum) && (newNum <= userLimit) && (properDividingSums(newNum) == i)) 
				{				
					addToAmicableNums(i,newNum);
					
				}
        }	
    }
		
		
	
	
	printAmicableNums();
	
	
	
	
	
	
	exit();
}
void addToAmicableNums(int num1,int num2)
{
	
	amicableNums1[amicableIndex] = num1;
	amicableNums2[amicableIndex] = num2;
	amicableIndex++;
}

int properDividingSums(int num)
{
    int sum = 0;
    int i = 0;
 
    for( i = 1; i <= (num / 2 ); i++)
    {
        if( num%i==0 )
        {
            sum +=i;
        }
    }
    return sum;
	
}
void printAmicableNums()
{
	printf(1, "CS 370 Project #6 - Amicable Numbers.\n");
	printf(1, "\t\t Thread Count: %d \n" , threadCount);
	printf(1, "\t\t Amicable Limit: %d\n", userLimit);
	
	printf(1,"Results:\n");
	
	printf(1,"Count of amicable pairs between 1 & %d is %d\n", userLimit, amicableIndex);
	printf(1,"Amicable Pairs\n");
	
	printf(1,"-------------     -----------\n");
	
	for ( int i = 0 ; i < amicableIndex ; i++ )
	{
		printf(1,"\t%d\t\t%d\n" , amicableNums1[i], amicableNums2[i]);
	}
	
	
}


int argValidation(int argc, char *argv[])
{	
	
	if ( argc != 5 )
	{
		printf(1,"Usage: amicableNums -t [threadCount] -l [LIMIT]\n");
		exit();
	}
	
	if (argv[1][0] != '-' && argv[1][1] != 't')	 
	{
		printf(1,"Usage: amicableNums -t [threadCount] -l [LIMIT]\n");
		exit();		
	}
	if (argv[3][0] != '-' && argv[3][1] != 'l')	
	{
		printf(1,"Usage: amicableNums -t [threadCount] -l [LIMIT]\n");
		exit();	
		
	}
	
	threadCount = (atoi(argv[2]));
	userLimit = atoi(argv[4]); // changes input from user to number...
		
	
	return 0;
}
