/*
 * @Author Christopher Lewis
 * 
 * Meant to be a time system call for XV6.
 * 
 * 
 * 
 * 
 * */

#define NULL 0
#define true 1
#define false 0


#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"



typedef struct Node Node;

struct Node
{
	char *string;
	Node *next;
};

struct queue
{
	Node *head;
	Node *tail;
}wordQueue; 


void initializeQueue();
void enqueue(char *word, int size);
void printQueue();

char *dequeue();

Node *makeNode(char *word);


int main(int argc, char* argv[])
{
	
	int beforeTime = 0;
	int afterTime = 0;
	int totalTime = 0;
		
	char *myArgv[2];

	if ( argc != 2 )
	{
		printf(1, "Incorrect usage\n");
		printf(1, "Correct usage is:");
		printf(1, "time [COMMAND]\n");
		exit();
	}
	
	myArgv[0] = argv[1];
	
	beforeTime = uptime();
	
	int pid = fork();
	
	if ( pid > 0 )	// currently parent process...
	{
		pid = wait();
		
		afterTime = uptime();
	}
	else if(pid == 0)	// currently child process...
	{
		exec(myArgv[0] , myArgv);
		
	}
	else
	{
		printf( 1, "fork error\n" );
	}
	
	
	totalTime = afterTime - beforeTime;
	
	printf(1,"The '%s' command took %d ticks...\n", myArgv[0] , totalTime);
	
	exit();
		
	
	
	
	
	
	
}
void initializeQueue()
{
	wordQueue.head = NULL;
	wordQueue.tail = NULL;
}
		
Node *makeNode(char *word)
{
	int size = strlen(word);
	int i = 0;
	
	char *tempWord = (char*) malloc(size*sizeof(char));
	
	for ( i = 0 ;i < size ;i++)
	{
		
		tempWord[i] = word[i];
		
	}
	
	tempWord[i] = '\0';
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	
	
	newNode->string = tempWord;
	newNode->next = NULL;

	return newNode;
}

void enqueue(char *word, int size)
{
	char *tempWord = (char*) malloc(size*sizeof(char));
	int i = 0;
	
	while (word[i] != NULL)
	{
		tempWord[i] = word[i];
		i++;
	}
	
	tempWord[strlen(word)] = NULL;
	
	//printf(1,"Before makeNode(): %s \n" , tempWord);
	
	Node *newNode = makeNode(tempWord);
	
	
	
	 if ( wordQueue.head == NULL )		// Queue is empty...
	 {
		 //printf(1,"adding %s to the Queue\n" , newNode->string);
		 wordQueue.head = newNode;
		 wordQueue.tail = newNode;
	 }
	 else
	 {
		// printf(1,"adding %s to the Queue\n" , newNode->string);
		 wordQueue.tail->next = newNode;
		 wordQueue.tail = newNode;

      }
      
      
     
}
char *dequeue()
{
	char *returnChar = NULL;
	
	
	
	if ( wordQueue.head == NULL && wordQueue.tail == NULL )
	{
		returnChar = "Queue empty...\n";
	}
	
	
	else if ( wordQueue.head == wordQueue.tail )
	{
		//printf(1, "Currently dequeueing: %s \n" , wordQueue.head->string);
		returnChar = wordQueue.head->string;
		free(wordQueue.head);
		
		wordQueue.head = wordQueue.tail = NULL;
	}
	else
	{
		//printf(1, "Currently dequeueing: %s \n" , wordQueue.head->string);
		returnChar = wordQueue.head->string;
		Node *frontPtr = wordQueue.head;
		wordQueue.head = wordQueue.head->next;
		free(frontPtr);
	}
		
	
	
	return returnChar;
}
void printQueue()
{
	
	if ( wordQueue.head != NULL )
	{
		printf(1, "These are the items in the Queue...\n");
		
		Node *printPtr = wordQueue.head;
		
		while(printPtr != NULL)
		{
			
			printf(1,"%s " , (printPtr->string));
			printPtr = printPtr->next;
		}
		
		
	}
	printf(1,"\n");
	
	
}
