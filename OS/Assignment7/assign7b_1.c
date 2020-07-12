#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
  
int main()
{

	int returnValue;
	char arr[80],c;
	int fd,fp,data,fd1,sente[3],i;
	int open_mode=O_WRONLY;
	int res=mkfifo("my_fifo",0777);
	sente[0]=0;sente[1]=0;sente[2]=0;
	if(res==0)
	{
		printf("\nFIFO created");
	}
	int res1=mkfifo("my_fifo1",0777);
	if(res==0)
	{
		printf("\nFIFO created");
	}
	printf("\nEnter the sentences to write\nEnter STOP to finish\n");
	while(1)
	{
	gets(arr);
		
		
		fd=open("my_fifo",O_WRONLY);
		write(fd,arr,strlen(arr)+1);
		close(fd);	
		
		if(strcmp(arr,"stop")==0)
		{
		
			break;
		}
			       
		
	}
	printf("\nData Analysis::\n");
 fd1 = open("my_fifo1", O_RDONLY);	
	while(1)
	{
	   
		int num;
        char s[300];
        while ((num = read(fd, s, sizeof(s))) > 0)
        {
            printf("%s",s);
        }
		
   }
close(fd);		

		
		/*
		printf("\nThe number of letters are  ::\t%d",sente[0]);
		printf("\nThe number of words are    ::\t%d",sente[1]);
		printf("\nThe number of sentences are::\t%d\n\n",sente[2]);
	*/

	
	
	return 0;
	
}		


