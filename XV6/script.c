/*
 * Supposed to be a script for XV6.
 * 
 * 
 * */

#define NULL 0
#define true 1
#define false 0
#define count 1000


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


int  checkExt(char *filename);


int  main(int argc, char *argv[])
{
	
	
	 initializeQueue();
	
	 int fileDesc = 0;
	 int charsRead = 0;
	 int bufCount = 0;
	 int wordCount = 0;
	 int wordsPerLine = 0;
	
	
	
	 char currentChar = NULL;
	 char buf[1000];
	 char word[64] = {0};
	
	 char *myArgv[10];

	
	if ( argc != 2 )
	{
		printf(1, "Incorrect usage\n"      );
		printf(1, "Correct usage is:"      );
		printf(1, "script [FILENAME.sh] \n");
		exit();
	}
	
		
	if(checkExt(argv[1]))
	{
			fileDesc = open(argv[1], 0x000);
			
	}
	else
	{
		printf(1,"Error, wrong file extension...\n");
		exit();
	}
					
	charsRead = read(fileDesc , buf , count );
	close(fileDesc); 
		
	printf(1,"This is how many chars were read %d\n" , charsRead);
		
	while ( bufCount <= charsRead )
	{
		
		wordCount = 0;
		
		currentChar = buf[bufCount];
		
		
		
		while ( currentChar != ' ' && currentChar != '\n' )
		{
			word[wordCount] = currentChar;
			wordCount++;
			bufCount++;
			currentChar = buf[bufCount];
		}
		
		
		word[wordCount] = '\0';

		enqueue(word , strlen(word));
		bufCount++;
		
		wordsPerLine++;
		
		
		if( currentChar == '\n')
		{
			//printQueue();
			for ( int i = 0 ; i < wordsPerLine ;i++)
			{
				myArgv[i] = dequeue();
			}
		
			
			int pid = fork();
	
			if ( pid > 0 )		// insdie parent process...
			{
				pid = wait();
			}
			else if( pid == 0 )	// inside child process...
			{
				exec(myArgv[0], myArgv);
		
			}
			else{
				printf(1,"ForkError...\n");
			}
			for ( int i = 0 ; i < 10; i++)
			{
				myArgv[i] =  NULL;
			}
			
			
			wordsPerLine = 0;
		}	
			
			
			 
		for ( int i = 0 ; i < 64 ; i++)
		{
			word[i] = NULL;
		}
						
	}
			
		
	
	
	exit();
	
}
int  checkExt(char *filename)
{
	int length = strlen(filename);
	int flag = false;
	
	if((filename[length - 1]) == 'h')
	{
		
		if((filename[length - 2]) == 's')
		{
			if((filename[length - 3]) == '.')
			{
				flag = true;
			}
		}
	}
	
	
	return flag;
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
			
			printf(1,"%s" , (printPtr->string));
			printPtr = printPtr->next;
		}
		
		
	}
	printf(1,"\n");
	
	
}
