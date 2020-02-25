#include "types.h"
#include "stat.h"
#include "user.h"



int main(void)
{
	
	char *argv[] = {"echo" ,"Hello"  , "xv6" , "world"};
	
	int pid = fork();
	

	
	if ( pid > 0 )
	{
		printf(1,"Inside parent process, child process ID [%d]\n" , pid);
		
		pid  =  wait();
		
		
		printf(1,  "Child [%d] is done executing.\n" , pid );
		
	}
	else if(pid == 0)
	{
		exec(argv[0] , argv);
		
	}
	else
	{
		printf( 1, "error" );
	}
	
	
	exit();
		
	
}
	
	
