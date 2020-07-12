#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
  
int main()
{
	char arr[80],ch,data[50];
	int fd1,l=1,w=1,c=0,i=0,fd2;
	int res=mkfifo("my_fifo",0777);
	
	fd1=open("my_fifo",O_RDONLY);
	read(fd1,arr,80);
	printf("\n%s",arr);
	close(fd1);
	
	
	while(arr[i++]!='#')
	{
		c++;
		if (arr[i]==' ')
			w++;
		if (arr[i] == '\n')
		{
		l++;
		}	
	}
	
	i=0;
	data[i++]=c + '0';
		data[i++]=' ';
	data[i++]=w + '0';
		data[i++]=' ';
	data[i++]=l + '0';
	data[i++]='\0';
	
	printf("%s",data);
	res=mkfifo("my_fifo2",0777);
	
	fd2=open("my_fifo2",O_WRONLY);
	write(fd2,data,80);
	close(fd2);
	printf("\n");
	//printf("%d %d %d",c,w,l);
	
}	
