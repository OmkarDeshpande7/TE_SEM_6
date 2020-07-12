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
	char arr[80],c,data[80];
	int fd,fd2,i=0;
	int res=mkfifo("my_fifo",0777);
	if(res==0)
	{
		printf("\nFIFO created");
	}
	printf("\nEnter the sentences to write\nEnter \"stop\" to finish\n");
	fd=open("my_fifo",O_WRONLY);
			
	do
    { 
        scanf("%c", &c); 
        arr[i++]=c;
    } 
    while (c != '#'); 
	write(fd,arr,strlen(arr)+1);
	close(fd);
	
	
	
	res=mkfifo("my_fifo2",0777);
	
	fd2=open("my_fifo2",O_RDONLY);
	read(fd2,data,80);
	close(fd2);
	printf("\n%s",data);
	return 0;
}		


